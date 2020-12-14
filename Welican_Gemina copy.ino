/**************************************************************************
 * 
 * Collaborative Project for a Next Generation WS LED Control Box
 * 
 * Beta Version
 * 
 * August 2020
 * 
 * Brian Schimke (brs0906@gmail.com)
 * Matt Taylor (maylortaylor@gmail.com)
 * 
 *************************************************************************
*/

// ----------------------------------------------------------------
// INCLUDEs
// ----------------------------------------------------------------

#include <FastLED.h>
#include "images.h"
#include "EEPROM.h"
#include <Wire.h>
#include <U8g2lib.h>
#include <ESP32Encoder.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <DNSServer.h>
#include <Arduino_JSON.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "time.h"
#include "Secrets.h"
#include <arduinoFFT.h>
#include "FirebaseESP32.h"
//#include <rom/rtc.h>

FASTLED_USING_NAMESPACE

// ----------------------------------------------------------------
// DEFINEs
// ----------------------------------------------------------------

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif
#define VERSION_INFO "Build 0.530 - 11/16/20"
#define KNOB_1C 25 //Program
#define KNOB_2C 4  //Brightness 14
#define MAX_MODES 8
#define SAMPLES 512         // Must be a power of 2. FAST 256 (40fps), NORMAL 512 (20fps), ACCURATE 1024 (10fps)
#define SAMPLING_FREQ 40000 // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define AMPLITUDE 3000      // Depending on your audio source level, you may need to alter this value. Can be used as a 'sensitivity' control.
#define AUDIO_IN_PIN 35     // Signal in on this pin
#define NUM_BANDS 4         // To change this, you will need to change the bunch of if statements describing the mapping from bins to bands
#define NOISE 500           // Used as a crude noise filter, values below this are ignored
#define TOP 32
#define FRAMES_PER_SECOND 120
#define SCREEN_WIDTH 127
#define SCREEN_WIDTH_HALF 63
#define SCREEN_HEIGHT 63
#define SCREEN_HEIGHT_HALF 31
#define MAX_STARS 32
#define QSUBD(x, b) ((x > b) ? b : 0)     // Digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define QSUBA(x, b) ((x > b) ? x - b : 0) // Analog Unsigned subtraction macro. if result <0, then => 0
#define DATA_PIN 18
#define DATA_PIN_A 12
#define LED_TYPE WS2811
#define COLOR_ORDER RGB
#define MAX_LEDS 500
int NUM_LEDS = 200;
#define LEDS_FOR_SIMPLEX 6
#define VISUALIZER_X 48
#define VISUALIZER_Y 128
#define STATUS_LED 0
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100
#define COOLING 90
// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 50

// ----------------------------------------------------------------
// GLOBALs
// ----------------------------------------------------------------
FirebaseData firebaseData;
AsyncWebServer server(80);
DNSServer dnsServer; // Used for Captive Portal

class CaptiveRequestHandler : public AsyncWebHandler
{
public:
  CaptiveRequestHandler() {}
  virtual ~CaptiveRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request)
  {
    //request->addInterestingHeader("ANY");
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request)
  {
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    response->print("<!DOCTYPE html><html><head><title>Captive Portal</title></head><body>");
    response->print("<p>This is out captive portal front page.</p>");
    response->printf("<p>You were trying to reach: http://%s%s</p>", request->host().c_str(), request->url().c_str());
    response->printf("<p>Try opening <a href='http://%s'>this link</a> instead</p>", WiFi.softAPIP().toString().c_str());
    response->print("</body></html>");
    request->send(response);
  }
};

TaskHandle_t inputComputeTask = NULL;

//1.3" OLED, small glitch on 2.4"
//U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ 5);

//2.4" OLED, ORIGINAL BOARDS, small glitch on 1.3"
//U8G2_SSD1309_128X64_NONAME0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ 5);

//2.4" OLED, MODERN BOARDS, small glitch on 1.3"
U8G2_SSD1309_128X64_NONAME0_F_HW_I2C u8g2(U8G2_R0, /* reset=*/19);

/*
For EST - UTC -5.00 : -5 * 60 * 60 : -18000
For EDT - UTC -4.00 : -4 * 60 * 60 : -14400
For UTC +0.00 : 0 * 60 * 60 : 0
*/
struct tm timeinfo;
int T[] = {0x15, 0x38, 0x32, 0x2c, 0x0d, 0x13, 0x07, 0x2a};
static float onethird = 0.333333333;
static float onesixth = 0.166666667;

// ----------------------------------------------------------------
// STRUCTs
// ----------------------------------------------------------------
struct Globals
{
  int temp[3];
  int timeZone;
  String timeZoneOffset;
  String timeZoneName;
  int tempValue;
  int currentSpeed;
  unsigned long newTime;
  unsigned int samplingPeriodUs;
  int runMode;
  int mode;
  int modeMax;
  int randomInterval;
  int randomMin;
  int randomMax;
  unsigned long randomTime;
  int randomMode;
  String ipAddress;
  String openWeatherMapApiKey;
  String ssid;
  String password;
  unsigned long networkReconnect;
  int networkTries;
  int networkScan;
  int signalStrength;
  int softAPEnable;
  const char *ntpServer;

  ESP32Encoder encoder;
  ESP32Encoder encoder2;
  CRGB clr1;
  CRGB clr2;
  double vReal[SAMPLES];
  double vImag[SAMPLES];
};
Globals globals = {
    .temp = {},
    .timeZone = -5,
    .timeZoneOffset = "-18000",
    .timeZoneName = "",
    .tempValue = 0,
    .currentSpeed = 10,
    .newTime = 0,
    .samplingPeriodUs = 0,
    .runMode = 0,
    .mode = 0,
    .modeMax = MAX_MODES,
    .randomInterval = 0,
    .randomMin = 60000,
    .randomMax = 240000,
    .randomTime = 0,
    .randomMode = 0,
    .ipAddress = "",
    .openWeatherMapApiKey = OPEN_WEATHER_API_KEY,
    .ssid = WIFI_SSID,
    .password = WIFI_PASSWORD,
    .networkReconnect = 0,
    .networkTries = 0,
    .networkScan = 0,
    .signalStrength = 0,
    .softAPEnable = 0,
    .ntpServer = "pool.ntp.org"};
arduinoFFT FFT = arduinoFFT(globals.vReal, globals.vImag, SAMPLES, SAMPLING_FREQ);

struct DevEnvironment
{
  int fps;   //dev, speed tracking for main loop
  int fftps; //dev, speed tracking for fft task
  int breathing;
};
DevEnvironment devEnv = {
    .fps = 0,
    .fftps = 0,
    .breathing = 1};

struct GlobalStrings
{
  String categoryName;
  String functionName;
  char categoryNameOutString[20];
  char functionNameOutString[20];
};
GlobalStrings globalStrings = {
    .categoryName = "",
    .functionName = "",
    .categoryNameOutString = {},
    .functionNameOutString = {}};

struct GlobalUser
{
  String id;
  String name;
  String wifiName;
  String timezone;
  String zipcode;
  int highscore_snake;
  int highscore_fallios;
  int highscore_brickBreaker;
  int highscore_pong;
  int timerDelay;
  int updateInitial;
  int updateInterval;
};
GlobalUser globalUser = {
    .id = "",
    .name = "",
    .wifiName = "",
    .timezone = "",
    .zipcode = "",
    .highscore_snake = 0,
    .highscore_fallios = 0,
    .highscore_brickBreaker = 0,
    .highscore_pong = 0,
    .timerDelay = 0,
    .updateInitial = 30000, // 30 seconds after boot
    .updateInterval = 15000 // every 15 after that
    };

struct GlobalTime
{
  int currentMinute;
  int currentHour;
  int currentDay;
  int currentDate;
  int currentMonth;
  bool currentPM;
  unsigned long startMillis;
  unsigned long currentMillis;
  const unsigned long period;
  int save;
  int timeOut;
  int currentDisplay;
  unsigned long currentDisplayTime;
  int timeDisplay1;
  int timeDisplay2;
  int timeDisplay3;
  unsigned long touchTime;
};
GlobalTime globalTime = {
    .currentMinute = 0,
    .currentHour = 100,
    .currentDay = 5,
    .currentDate = 1,
    .currentMonth = 0,
    .currentPM = 0,
    .startMillis = 0,
    .currentMillis = 0,
    .period = 1000,
    .save = 0,
    .timeOut = 30000,
    .currentDisplay = 0,
    .currentDisplayTime = 0,
    .timeDisplay1 = 0,
    .timeDisplay2 = 0,
    .timeDisplay3 = 0,
    .touchTime = 0};

struct GlobalUtils
{
  int encoderUnstick;
};
GlobalUtils utils = {
    .encoderUnstick = 0};

struct GlobalLED
{
  int pixelNumber;
  int interfade; //set this to 0 to disable fade in on boot. Set to 25 for fade in.
  int interfadeMax;
  int interfadeSpeed;
  int fadeDirection;      // 1 or 0, positive or negative
  int fadeDirection2;     // 1 or 0, positive or negative
  int fadeDirectionHTemp; // 1 or 0, positive or negative
  byte colorOrder;
  bool clearLEDS;
};
GlobalLED globalLED = {
    .pixelNumber = 0,
    .interfade = 18,
    .interfadeMax = 18,
    .interfadeSpeed = 14,
    .fadeDirection = 0,
    .fadeDirection2 = 0,
    .fadeDirectionHTemp = 0,
    .colorOrder = 0,
    .clearLEDS = false};

struct SimplexNoiseModel
{
  int nodeSpacing;
  int A[3];
  float hTemp;
  float timeInc;
  float spaceInc;
  float yoffset;
  float yoffsetMax;
  float xoffset;
  float ledArrayRed[MAX_LEDS + 1];
  float ledArrayGreen[MAX_LEDS + 1];
  float ledArrayBlue[MAX_LEDS + 1];
  float u;
  float v;
  float w;
  float s;
  float h;
  int g;
  int j;
  int k;
};
SimplexNoiseModel simplexNoise = {
    .nodeSpacing = (MAX_LEDS / LEDS_FOR_SIMPLEX),
    .A = {0, 0, 0},
    .hTemp = .420,
    .timeInc = 0.0025,
    .spaceInc = 0.05,
    .yoffset = 0.0,
    .yoffsetMax = 15000,
    .xoffset = 0.0};

struct PatternSettings
{
  int pattern[MAX_MODES + 1];
  byte patternAdjust[MAX_MODES + 1][100];
  int favoritePattern[50]; //all are used under the hood
  int favoritePatternAdjust[50];
  int favoriteMode[50];  //declare memory for all 50 favorites
  int numberOfFavorites; //Max 50, loads all 50 at program load, dynamically assignable
  int tempPattern;
  int currentPattern;
  int displayPattern;
  int randomPattern;
  uint8_t gHue;           // rotating "base color" used by many of the patterns
  int8_t flowDirection;   // Use either 1 or -1 to set flow direction
  bool gReverseDirection; //false = center outward, true = from ends inward
  bool sizeUpdate;
  bool moving;
  uint8_t speed;
  bool fadingTail;  // Add fading tail?
  uint8_t fadeRate; // How fast to fade out tail. [0-255]
  float valueMax;   // Pulse maximum value (Should be larger then valueMin).
  float valueMin;   // Pulse minimum value (Should be less then valueMax).
  float delta;      // Do Not Edit
  int8_t delta2;    // Sets forward or backwards direction amount. (Can be negative.)
  int palletPosition;
  int colorBarPosition;
  uint8_t loc1;
  int8_t advance;       // Stores the advance amount
  uint8_t colorStorage; // Stores a hue color.
  uint8_t count;
  uint16_t cycleLength; // Lover values = continuous flow, higher values = distinct pulses.
  uint16_t pulseLength; // How long the pulse takes to fade out.  Higher value is longer.
  uint16_t pulseOffset; // Delay before second pulse.  Higher value is more delay.
  float breath;
  uint8_t posR;
  uint8_t posG;
  uint8_t posB; // positions of moving R,G,B dots
  uint8_t pos;  // stores a position for color being blended in
  uint8_t hueA; // Start hue at valueMin.
  uint8_t satA; // Start saturation at valueMin.
  uint8_t hueB; // End hue at valueMax.
  uint8_t hue;  // Do Not Edit
  uint8_t hue2; // Do Not Edit
  uint8_t sat;  // Do Not Edit
  uint8_t satB; // End saturation at valueMax.
  float val;
  CRGB tempPatternCollection[MAX_LEDS];
  CRGB tempHalfLeds[MAX_LEDS / 2]; // half the total number of pixels
  CRGB leds[MAX_LEDS];
  CRGB tempLeds[MAX_LEDS];
  byte colorIndex[MAX_LEDS];
};
PatternSettings patternSettings = {
    .pattern = {},
    .patternAdjust = {},
    .favoritePattern = {},
    .favoritePatternAdjust = {},
    .favoriteMode = {},
    .numberOfFavorites = 25,
    .tempPattern = 0,
    .currentPattern = 0,
    .displayPattern = 0,
    .randomPattern = 0,
    .gHue = 0,
    .flowDirection = -1,
    .gReverseDirection = false,
    .sizeUpdate = 0,
    .moving = true,
    .speed = 0,
    .fadingTail = false,
    .fadeRate = 120,
    .valueMax = 255.0,
    .valueMin = 120.0,
    .delta = ((patternSettings.valueMax - patternSettings.valueMin) / 2.35040238),
    .delta2 = 170,
    .palletPosition = 1,
    .colorBarPosition = 0,
    .loc1 = 1,
    .advance = 0,
    .colorStorage = 0,
    .count = 0,
    .cycleLength = 0,
    .pulseLength = 1500,
    .pulseOffset = 150,
    .breath = 0,
    .posR = 0,
    .posG = 0,
    .posB = 0,
    .pos = 0,
    .hueA = 15,
    .satA = 230,
    .hueB = 95,
    .hue = patternSettings.hueA,
    .hue2 = patternSettings.hueB,
    .sat = patternSettings.satA,
    .satB = 255,
    .val = patternSettings.valueMin};

struct HSV2RGB
{
  int red, green, blue;    // used in hsv2rgb color functions
  int red2, green2, blue2; // used in hsv2rgb color functions
  int red3, green3, blue3; // used in hsv2rgb color functions
};
HSV2RGB globalHSV2RGB;

struct MenuModel
{
  int menu[35];
  int menuMax[35];
  int patternMax[MAX_MODES + 1];
  int currentMenu;
  int currentMenuMultiplier;
  u8g2_uint_t verticalDividePosition;
  u8g2_uint_t firstLineHorizontal;
  u8g2_uint_t secondLineHorizontal;
  u8g2_uint_t selectionBubblePadding;
  u8g2_uint_t selectionBubbleWidth;
  u8g2_uint_t selectionBubbleHeight;
  u8g2_uint_t selectionBubbleRadius;
};
MenuModel globalMenu = {
    .menu = {},
    //Root Menu Items, Game Menu Items, Settings Menu Items
    .menuMax = {
        3,                                 //Main
        5,                                 //Game
        7,                                 //Settings
        3,                                 //LED Settings
        1,                                 //ZIP Code
        3,                                 //Favorites Menu
        50,                                //Max Favorites
        2,                                 //Reset Favorites
        3,                                 //Wifi Menu
        3,                                 //Customize Menu
        patternSettings.numberOfFavorites, //Add Favorite
        99999,                             //Enter ZIP Code
        0,                                 //WiFi Scan Results (dynamically set)
        128,                               // WiFi Password
        3,                                 //WiFi Test
        (MAX_LEDS / 5),                    //# LEDs
        3,                                 //LED Color mode
        50,                                //LED SmoothOperator Fade Rate
        3,                                 //Speed?
        3,                                 //Time Menu
        6,                                 //Time Zone
        3,                                 //Manual Time Entry
        3,                                 //Manual Date Entry
        1,                                 //NTP
        7,                                 //Customize Display
        71,                                //Customize Timeout
        15,                                //Display 1
        15,                                //Display 2
        15,                                //Display 3
        71,                                //Random Timeout
        60,                                //Display 1 Duration
        60,                                //Display 2 Duration
        60,                                //Display 3 Duration
        10,                                //Display Brightness
    },
    .patternMax = {
        13,                                //Basic Category
        20,                                //Music Category
        23,                                //Chill
        66,                                //Moving Colors
        81,                                //Legacy
        patternSettings.numberOfFavorites, //Favorites (dynamic)
        10,                                //Palette Mode
    },
    .currentMenu = 0,
    .currentMenuMultiplier = 1,
    .verticalDividePosition = 64,
    .firstLineHorizontal = 24,
    .secondLineHorizontal = 38,
    .selectionBubblePadding = 12,
    .selectionBubbleWidth = 64,
    .selectionBubbleHeight = 16,
    .selectionBubbleRadius = 7};

struct Brightness
{
  int current;
  int target;
  int rate;
  int temp;
  unsigned long debounce;
  unsigned long debounce2;
  bool useFade;
  int fadeAmount;         // Set the amount to fade -- ex. 5, 10, 15, 20, 25 etc even up to 255.
  uint8_t baseBrightness; // Brightness of LEDs when not pulsing. Set to 0 for off.
};
Brightness brightness = {
    .current = 0,
    .target = 0,
    .rate = 12,
    .temp = 0,
    .debounce = 0,
    .debounce2 = 0,
    .useFade = false,
    .fadeAmount = 5,
    .baseBrightness = 10};

struct BallModel
{
  int x[MAX_STARS];
  int xx[MAX_STARS];
  int y[MAX_STARS];
  int yy[MAX_STARS];
  int z[MAX_STARS];
};
BallModel ball;

struct BounceModel
{
  int x;
  int y;
  int vx;
  int vy;
};
BounceModel bounceModel1 = {
    .x = random(random(0, 64), random(0, 64)),
    .y = random(random(0, 64), random(0, 64)),
    .vx = random(random(0, 64), random(0, 64)),
    .vy = random(random(0, 64), random(0, 64))};
BounceModel bounceModel2 = {
    .x = random(random(0, 64), random(0, 64)),
    .y = random(random(0, 64), random(0, 64)),
    .vx = random(random(0, 64), random(0, 64)),
    .vy = random(random(0, 64), random(0, 64))};
BounceModel bounceModel3 = {
    .x = random(random(0, 64), random(0, 64)),
    .y = random(random(0, 64), random(0, 64)),
    .vx = random(random(0, 64), random(0, 64)),
    .vy = random(random(0, 64), random(0, 64))};
BounceModel bounceModel4 = {
    .x = random(random(0, 64), random(0, 64)),
    .y = random(random(0, 64), random(0, 64)),
    .vx = random(random(0, 64), random(0, 64)),
    .vy = random(random(0, 64), random(0, 64))};
BounceModel bounceModel5 = {
    .x = random(random(0, 64), random(0, 64)),
    .y = random(random(0, 64), random(0, 64)),
    .vx = random(random(0, 64), random(0, 64)),
    .vy = random(random(0, 64), random(0, 64))};
BounceModel bounceModel6 = {
    .x = random(random(0, 64), random(0, 64)),
    .y = random(random(0, 64), random(0, 64)),
    .vx = random(random(0, 64), random(0, 64)),
    .vy = random(random(0, 64), random(0, 64))};
BounceModel bounceModel7 = {
    .x = random(random(0, 64), random(0, 64)),
    .y = random(random(0, 64), random(0, 64)),
    .vx = random(random(0, 64), random(0, 64)),
    .vy = random(random(0, 64), random(0, 64))};
BounceModel bounceModel8 = {
    .x = random(random(0, 64), random(0, 64)),
    .y = random(random(0, 64), random(0, 64)),
    .vx = random(random(0, 64), random(0, 64)),
    .vy = random(random(0, 64), random(0, 64))};
BounceModel bounceModel9 = {
    .x = random(random(0, 64), random(0, 64)),
    .y = random(random(0, 64), random(0, 64)),
    .vx = random(random(0, 64), random(0, 64)),
    .vy = random(random(0, 64), random(0, 64))};
BounceModel bounceModel10 = {
    .x = random(random(0, 64), random(0, 64)),
    .y = random(random(0, 64), random(0, 64)),
    .vx = random(random(0, 64), random(0, 64)),
    .vy = random(random(0, 64), random(0, 64))};

// GAMES
struct Player
{
  int X;
  int Y;
};
Player player = {
    .X = 64,
    .Y = 8};

struct Fallios
{
  unsigned int score;
  unsigned int scoreTop;
  int motion;
  int motionHistory;
  int Y;

  float tunnelGenerator;
  int tunnel1[SCREEN_HEIGHT + 1];
  int tunnel2[SCREEN_HEIGHT + 1];
  int tunnelWidth;
  int tunnelTracker;
  int tunnelWildcard;
};
Fallios fallios = {
    .score = 0,
    .scoreTop = 0,
    .motion = 0,
    .motionHistory = 0,
    .Y = 8,
    .tunnelGenerator = 0,
    .tunnel1 = {},
    .tunnel2 = {},
    .tunnelWidth = (SCREEN_WIDTH / 2),
    .tunnelTracker = 100,
    .tunnelWildcard = 0};

struct snakeSegment
{
  byte x;
  byte y;
};

struct snakeApple
{
  bool active;
  byte x;
  byte y;
  byte size;
};

struct Snake
{
  int num;
  int num2;
  int score;
  int score2;
  int scoreMultiplier;
  int lengthMultiplier;
  byte speed;
  byte tick;
  int oldX;
  int oldY;
  float angle;
  float angle2;
  int Xa;
  int Ya;
  int sensitivity;
  int appleRate;
  int maxApples;
  int maxAppleSize;
  snakeSegment segment[1200];
  snakeSegment segment2[1200];
  snakeApple apple[25];
};

Snake snake = {
    .num = 10, //Set in reset
    .num2 = 10,
    .score = 0,
    .score2 = 0,
    .scoreMultiplier = 1,
    .lengthMultiplier = 1,
    .speed = 5,
    .tick = 0,
    .oldX = 0,
    .oldY = 0,
    .angle = 0.0,
    .angle2 = 0.0,
    .Xa = 0,
    .Ya = 0,
    .sensitivity = 4,
    .appleRate = 100,
    .maxApples = 10,
    .maxAppleSize = 4,
};

struct Ball
{
  bool active;
  float x;
  float y;
  uint8_t size;
  float velX;
  float velY;
};

struct Pong
{
  byte tick;
  byte speed;
  byte recent;
  int bounceCount;
  int bounceMax;
  int score1;
  int score2;
  int scoreToWin;
  int spacing;
  int paddleWidth1;
  int paddleWidth2;
  int paddleHeight1;
  int paddleHeight2;
  Ball ball[20];
};

Pong pong = {
    .tick = 0,
    .speed = 5,
    .recent = 0,
    .bounceCount = 0,
    .bounceMax = 0,
    .score1 = 0,
    .score2 = 0,
    .scoreToWin = 10,
    .spacing = 4,
    .paddleWidth1 = 10,
    .paddleWidth2 = 10,
    .paddleHeight1 = 2,
    .paddleHeight2 = 2};

struct Block
{
  byte X;
  byte Y;
  byte Health;
};

struct BlockBreaker
{
  byte level;
  int score;
  float ballX;
  float ballY;
  float ballXvel;
  float ballYvel;
  int ballWidth;
  int paddleHeight;
  int paddleWidth;
  int message;
  int messageTimer;
  byte running;
  byte blockWidth;
  byte blockHeight;
  Block block[70];
};

BlockBreaker blockBreaker = {
    .level = 0,
    .score = 0,
    .ballX = 0,
    .ballY = 0,
    .ballXvel = 0,
    .ballYvel = 0,
    .ballWidth = 4,
    .paddleHeight = 2,
    .paddleWidth = 16,
    .message = 0,
    .messageTimer = 0,
    .running = 0,
    .blockWidth = 10,
    .blockHeight = 5};

struct MagicWords
{
  String gameName;
  int randomQuestionArrSize;
  int randomQuestionNumber;
  int randomAnswerArrSize;
  int randomAnswerNumber;
  bool answerMode;
};
char MAGIC_ANSWERS[][40] = {
    "Yes",
    "No",
    "Maybe",
    "Not Sure",
    "Check back later",
    "Who cares?",
    "Who knows?",
    "I am not a god",
    "As I See it, yes",
    "Ask again later",
    "Better not tell you now",
    "Cannot predict now",
    "Sorry, I'm busy",
    "Don't count on it",
    "It is certain",
    "It is decidedly so",
    "Most Likely",
    "My reply is no",
    "Outlook not so good",
    "Outlook is good",
    "Reply hazy, try again",
    "Signs point to yes",
    "Very doubtful",
    "Without a doubt",
    "You may rely on it",
    "Yes - definitely",
    "Wake up neo"};
char MAGIC_QUESTION[][40] = {
    "Ask me anything",
    "Ask the 8 ball",
    "What do you want?",
    "What is up?",
    "What do you want to know?",
    "What is your question?",
    "What is going on?",
    "Sup?"};
MagicWords magicWordsGame = {
    .gameName = "Magic Words",
    .randomQuestionArrSize = sizeof(MAGIC_QUESTION) / sizeof(MAGIC_QUESTION[0]),
    .randomQuestionNumber = random(0, magicWordsGame.randomQuestionArrSize),
    .randomAnswerArrSize = sizeof(MAGIC_ANSWERS) / sizeof(MAGIC_ANSWERS[0]),
    .randomAnswerNumber = random(0, magicWordsGame.randomAnswerArrSize),
    .answerMode = false};

// WEATHER
struct OpenWeatherSettings
{
  String zipCode;
  String countryCode;
  String latitude;
  String longitude;
  unsigned long weatherTimerDelay;
  unsigned long weatherUpdateInitial;
  unsigned long weatherUpdateInterval;
  bool gotDailyWeather;
};
OpenWeatherSettings weatherSettings = {
    .zipCode = "33701",
    .countryCode = "US",
    .latitude = "33.441792",
    .longitude = "94.037689",
    .weatherTimerDelay = 0,           //Set by system
    .weatherUpdateInitial = 10000,    //10 seconds after boot
    .weatherUpdateInterval = 1800000, //Every 30 minutes after that
    .gotDailyWeather = false};

struct OpenWeatherObject
{
  JSONVar weatherJson;
  String currentWeatherId;
  String currentWeatherTitle;
  String currentWeatherDescription;
  String currentTemperature;
  String currentTemperatureMax;
  String currentTemperatureMin;
  String currentFeelsLike;
  String currentCloudiness;
  String currentVisibility;
  String currentHumidity;
  String currentWindSpeed;
  String currentWindDegree;
  String currentUvi;
  String sunrise;
  String sunset;
  String jsonBuffer;
};
OpenWeatherObject weather;

struct OpenWeatherDayObject
{
  String sunrise;
  String sunset;
  String tempDay;
  String tempMin;
  String tempMax;
  String tempNight;
  String tempEve;
  String tempMorn;
  String feelsLikeDay;
  String feelsLikeNight;
  String feelsLikeEve;
  String feelsLikeMorn;
  String pressure;
  String humidity;
  String dewPoint;
  String windSpeed;
  String windDegree;
  String weatherId;
  String weatherMain;
  String weatherDescription;
  String cloudiness;
  String pop;
  String rain;
  String uvi;
};
OpenWeatherDayObject weatherCurrentDay;
OpenWeatherDayObject weatherDay1;
OpenWeatherDayObject weatherDay2;
OpenWeatherDayObject weatherDay3;
OpenWeatherDayObject weatherDay4;
OpenWeatherDayObject weatherDay5;
OpenWeatherDayObject weatherDay6;
OpenWeatherDayObject weatherDay7;

struct Knob
{
  bool click;
  int temp;
  int debounce;
  int heldTime;
  bool heldDown;
};
Knob knob1;
Knob knob2;

struct VisualizerTriangle
{
  int x;
  int y;
  int radius;
  float point1;
  float point2;
  float point3;
  int x1;
  int x2;
  int x3;
  int y1;
  int y2;
  int y3;
};

VisualizerTriangle t1 = {
    .x = 64,
    .y = 42,
    .radius = 18,
    .point1 = 0.0,
    .point2 = 2.1,
    .point3 = 4.2,
    .x1 = 0,
    .x2 = 0,
    .x3 = 0,
    .y1 = 0,
    .y2 = 0,
    .y3 = 0};

VisualizerTriangle tA = {
    .x = 62,
    .y = 46,
    .radius = 13,
    .point1 = 0.0,
    .point2 = 2.1,
    .point3 = 4.2,
    .x1 = 0,
    .x2 = 0,
    .x3 = 0,
    .y1 = 0,
    .y2 = 0,
    .y3 = 0};
struct EQModel
{
  volatile int bandValues[15];
  int averageSamples;
  int bandAverages[NUM_BANDS][150];
  int tempBandValues[15];
  volatile int peak[15]; // The length of these arrays must be >= NUM_BANDS
};
EQModel eqBands = {
    .bandValues = {},
    .averageSamples = 100,
    .bandAverages = {},
    .tempBandValues = {},
    .peak = {}};

struct WebsiteModel
{
  String returnText;
};
WebsiteModel website = {
    .returnText = ""};

// ----------------------------------------------------------------
// SETUP
// ----------------------------------------------------------------

void setup()
{
  //For troubleshooting
  Serial.begin(115200);

  Serial.println("Welican Gemina");
  Serial.println(VERSION_INFO);

  //Serial.println(rtc_get_reset_reason(0));

  //Board Status LED Setup

  // setting PWM properties
  const int freq = 5000;
  const int resolution = 13;
  
  // Google Firebase Database setup
  Firebase.begin(FIREBASE_URL, FIREBASE_DATABASE_SECRET_KEY);
  // Optional, set number of error retry
  Firebase.setMaxRetry(firebaseData, 3);
  // Optional, set number of error resumable queues
  Firebase.setMaxErrorQueue(firebaseData, 20);
  // Optional, use classic HTTP GET and POST requests. 
  // This option allows get and delete functions (PUT and DELETE HTTP requests) works for 
  // device connected behind the Firewall that allows only GET and POST requests.   
  Firebase.enableClassicRequest(firebaseData, true);

  //pinMode(ledChannel, OUTPUT); //LED Status Light
  // configure LED PWM functionalitites
  ledcSetup(STATUS_LED, freq, resolution);

  //Set Pin to Output mode to send power to LED
  pinMode(23, OUTPUT);

  //Attach the channel to the GPIO to be controlled
  ledcAttachPin(23, STATUS_LED);

  //Set the status LED to the lowest brightness
  ledcWrite(STATUS_LED, 0);

  // Enabke internal pull up resistors for buttons
  pinMode(KNOB_1C, INPUT_PULLUP); //Knob 1 Click, internal Pull Up (button connects to ground)
  pinMode(KNOB_2C, INPUT_PULLUP); //Knob 2 Click, internal Pull Up (button connects to ground)

  // Enable the weak pull up resistors for encoders
  ESP32Encoder::useInternalWeakPullResistors = UP;

  //Program Selection, encoder WITH Detents
  globals.encoder.attachFullQuad(33, 32);

  //Brightness Adjustment, encoder WITHOUT Detents
  //encoder2.attachFullQuad(27, 26);
  globals.encoder2.attachFullQuad(16, 17); //RX2 and TX2

  // set starting count value after attaching
  globals.encoder.clearCount();

  // clear the encoder's raw count and set the tracked count to zero
  globals.encoder2.clearCount();

  // Initialize SPIFFS
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  //openSpiffFile("/magic.txt");

  //WiFi.enableSTA(true);

  //WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  if (digitalRead(KNOB_1C) == 1)
  {
    WiFi.begin(); //Will connect to last connected to AP, even after power loss
  }
  else
  {
    globals.networkTries = 100;
  }
  //WiFi.status();
  //WiFi.localIP();

  startWebsite(&server);

  seedThings();

  //u8g2.setBusClock(1000000);

  //Few new boards using 2.4 OLED
  pinMode(19, OUTPUT);
  digitalWrite(19, HIGH);

  //Display library initialization
  u8g2.begin();

  u8g2.setBusClock(800000); //800 kHz i2c, default is 400 kHz

  u8g2.setFont(u8g2_font_ncenB08_tr); //Need to select a font or prints will cause panic

  /* Load Save Settings

    Load variables from EEPROM

    We must check for out of range data
    EEPROM may have been used or not at default

  --------------------*/
  EEPROM.begin(2048);

  //EEPROM.write(20, 0);
  //EEPROM.write(21, 0);
  //EEPROM.commit();

  //fallios.scoreTop = EEPROM.read(20) + EEPROM.read(21) * 256;
  EEPROM.get(20, fallios.scoreTop);

  //Screen Time out
  EEPROM.get(40, globalMenu.menu[25]);

  if (globalMenu.menu[25] > globalMenu.menuMax[25])
  {
    globalMenu.menu[25] = 0;
  }

  globalTime.timeOut = timeOutConverter(globalMenu.menu[25]);

  //Display 1
  EEPROM.get(45, globalMenu.menu[26]);

  //Display 2
  EEPROM.get(49, globalMenu.menu[27]);

  //Display 3
  EEPROM.get(53, globalMenu.menu[28]);
  
  //Display 1 Duration
  EEPROM.get(57, globalMenu.menu[30]);
  if (globalMenu.menu[30] > globalMenu.menuMax[30])
  {
    globalMenu.menu[30] = 0;
  }
  //Display 2 Duration
  EEPROM.get(61, globalMenu.menu[31]);
  if (globalMenu.menu[31] > globalMenu.menuMax[31])
  {
    globalMenu.menu[31] = 0;
  }

  //Display 3 Duration
  EEPROM.get(65, globalMenu.menu[32]);
  if (globalMenu.menu[32] > globalMenu.menuMax[32])
  {
    globalMenu.menu[32] = 0;
  }

  //Brightness
  EEPROM.get(69, globalMenu.menu[33]);
  if (globalMenu.menu[33] > globalMenu.menuMax[33])
  {
    globalMenu.menu[33] = 10;
  }  
  u8g2.setContrast(globalMenu.menu[33] * 25.5);

  EEPROM.get(73, globalMenu.menu[20]);
  if (globalMenu.menu[20] > globalMenu.menuMax[20])
  {
    globalMenu.menu[20] = 0;
  }  
  globals.timeZone = globalMenu.menu[20] - 12;

  globals.mode = EEPROM.read(0);
  brightness.target = EEPROM.read(1);
  brightness.current = brightness.target;

  readPatternSettings();

  //Make sure values aren't out of range
  if (globals.mode > globals.modeMax)
  {
    globals.mode = 0;
  }

  //Random Times
  EEPROM.get(90, globalMenu.menu[29]);
  if (globalMenu.menu[29] > globalMenu.menuMax[29])
  {
    globalMenu.menu[29] = 12;
  }

  globals.randomMin = timeOutConverter(globalMenu.menu[29]);
  globals.randomMax = globals.randomMin * 2;

  //Set master brightness control
  FastLED.setBrightness(brightness.current);

  readFavorites();

  getZipCode();

  //Set first Weather check value
  weatherSettings.weatherTimerDelay = weatherSettings.weatherUpdateInitial;
  globalUser.timerDelay = globalUser.updateInitial;

  updateZipCodeString();

  //Set Smooth Operator fade time
  readSmoothOperator();

  //Read # of LEDs to use
  readNumberOfLEDs();

  if (NUM_LEDS > 100)
  {
    Serial.print(NUM_LEDS - 1);
  }
  else
  {
    Serial.print(NUM_LEDS);
  }
  Serial.print(" LEDs - ");

  //FastLED Declation
  if (globalLED.colorOrder == 1)
  {
    //GRB, most common for Strips / Reels
    FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(patternSettings.leds, NUM_LEDS);
    FastLED.addLeds<LED_TYPE, DATA_PIN_A, GRB>(patternSettings.leds, NUM_LEDS);
    Serial.println("GRB");
  }
  else if (globalLED.colorOrder == 2)
  {
    //BGR, rare
    FastLED.addLeds<LED_TYPE, DATA_PIN, BGR>(patternSettings.leds, NUM_LEDS);
    FastLED.addLeds<LED_TYPE, DATA_PIN_A, BGR>(patternSettings.leds, NUM_LEDS);
    Serial.println("BGR");
  }
  else
  {
    //RGB, most common for 12mm Pixel types
    FastLED.addLeds<LED_TYPE, DATA_PIN, RGB>(patternSettings.leds, NUM_LEDS);
    FastLED.addLeds<LED_TYPE, DATA_PIN_A, RGB>(patternSettings.leds, NUM_LEDS);
    Serial.println("RGB");
  }

  for (int i = 0; i < NUM_LEDS; i++)
  {
    patternSettings.colorIndex[i] = random8();
  }

  //Begin a task named 'fftComputeTask' to handle FFT on the other core
  //This task also takes care of reading the button inputs and computing encoder positions
  //https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html
  xTaskCreatePinnedToCore(
      inputCompute,         /* Function to implement the task */
      "Input Compute Task", /* Name of the task */
      15000,                /* Stack size in words */
      NULL,                 /* Task input parameter */
      0,                    /* Priority of the task, lower is lower */
      &inputComputeTask,    /* Task handle. */
      0);                   /* Pin to specific CPU Core, main Loop runs on 1*/
}

// ----------------------------------------------------------------
// LOOP
// ----------------------------------------------------------------
void loop()
{

  EVERY_N_MILLISECONDS(33) //Enforce Max Frame Rate 33 = 30FPS
  {

    globalStrings.functionName.toCharArray(globalStrings.functionNameOutString, 20);
    globalStrings.categoryName.toCharArray(globalStrings.categoryNameOutString, 20);

    //Clear the display buffer so we can draw new stuff
    u8g2.clearBuffer();

    switch (globals.runMode)
    {
    case 0: //Main run mode
      drawBottom();
      drawTop();
      showBrightnessDisplay();
      break;
    case 1: //Menu mode
      drawMenuCommander();
      break;
    case 2: //Game mode
      switch (globalMenu.menu[1])
      {
      case 0:
        fallios_game();
        break;
      case 1:
        blockbreaker_game();
        break;
      case 2:
        magic_game();
        break;
      case 3:
        snake_game();
        break;
      case 4:
        pong_game();
        break;
      case 5:
        snake2_game();
        break;
      }
      break;
    case 3: //Clock/Weather/Info modes
      displayTimer();      
      showBrightnessDisplay();
      break;
    case -1:                           //Reset
      globalTime.touchTime = millis(); //Last touch time back to default
      globals.runMode = 0;             //Back to normal
      break;
    }

    //Show logo instead for first X millis
    showLogo(2500);

    //Clear active button clicks
    knob1.click = 0;
    knob2.click = 0;

    //Write buffer to display
    u8g2.sendBuffer();

    startBreathing();

    //Write current breath value to status LED
    ledcWrite(STATUS_LED, patternSettings.breath);

    patternSettings.displayPattern = patternSettings.pattern[globals.mode];

    if (patternSettings.displayPattern == 0)
    {
      if (((millis() - globals.randomTime) > globals.randomInterval) && globals.randomMin != 0)
      {
        pickRandom();
      }

      patternSettings.displayPattern = patternSettings.randomPattern;
    }

    switch (globals.mode)
    {
    case 0:
      basic_category(patternSettings.displayPattern);
      break;
    case 1:
      music_category(patternSettings.displayPattern);
      break;
    case 2:
      chill_category(patternSettings.displayPattern);
      break;
    case 3:
      moving_colors_category(patternSettings.displayPattern);
      break;
    case 4:
      legacy_category(patternSettings.displayPattern);
      break;
    case 5:
      favorites_category(patternSettings.displayPattern);
      break;
    case 6:
      palette_category(patternSettings.displayPattern);
      break;
    }

    //Detect mode changes and apply interfading
    smoothOperator();

    //Check to see if there are recent knob changes to store in memory
    saveTimeCheck();

    //Output data to LED strip
    FastLED.show();

    if (brightness.useFade == true)
    {
      brightness.current = brightness.current + brightness.fadeAmount;
      // reverse the direction of the fading at the ends of the fade:
      if (brightness.current == 0 || brightness.current == 255)
      {
        brightness.fadeAmount = -brightness.fadeAmount;
      }

      //delay(9); // This delay sets speed of the fade. I usually do from 5-75 but you can always go higher.
    }

    devEnv.fps++; //For tracking frame rate/ debug logging

    /*
  for (int i = 0; i < NUM_BANDS; i++)
  {
    int temp1 = 0;

    for (int ii = 0; ii < eqBands.averageSamples; ii++)
    {
      temp1 += eqBands.bandAverages[i][ii];
    }
    temp1 = temp1 / eqBands.averageSamples;

    //Debug Serial Logging
    Serial.print("Value[");
    Serial.print(i);
    Serial.print("]:");
    Serial.print(eqBands.bandValues[i]);
    Serial.print(", ");
    Serial.print("Average[");
    Serial.print(i);
    Serial.print("]:");
    Serial.print(temp1);
    Serial.print(", ");
  }
  Serial.println("");
  */

    // Serial.print(" ");
    // Serial.println(eqBands.bandValues[4]);
    //Serial.print(" ");

  // Serial.print(" ");
  // Serial.println(eqBands.bandValues[4]);
  //Serial.print(" ");
  
  EVERY_N_MILLISECONDS(10000)
  {
    Serial.print("FPS: ");
    Serial.println(devEnv.fps / 10);
    devEnv.fps = 0;
    Serial.print("IPS: ");
    Serial.println(devEnv.fftps / 10);
    devEnv.fftps = 0;
    //Serial.print("ICT: ");
    //Serial.println(eTaskGetState(inputComputeTask));
    Serial.print("MIN: ");
    Serial.println(((millis() / 1000) / 60));
  }
  
  // slowly cycle the "base color" through the rainbow
  EVERY_N_MILLISECONDS(200) { patternSettings.gHue++; }

    // slowly cycle the "base color" through the rainbow
    EVERY_N_MILLISECONDS(200) { patternSettings.gHue++; }

    autoConnect();
    //vTaskDelay(1);
  }
  //vTaskDelay(1);
}

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
#include <Arduino_JSON.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include "time.h"
#include "WifiCredentials.h"
#include <arduinoFFT.h>

// ----------------------------------------------------------------
// DEFINEs
// ----------------------------------------------------------------

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif
#define VERSION_INFO "Build 0.420 - 09/16/20"
#define KNOB_1C 25 //Program
#define KNOB_2C 4  //Brightness 14
#define MAX_MODES 5
#define SAMPLES 512         // Must be a power of 2. FAST 256 (40fps), NORMAL 512 (20fps), ACCURATE 1024 (10fps)
#define SAMPLING_FREQ 40000 // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define AMPLITUDE 3000      // Depending on your audio source level, you may need to alter this value. Can be used as a 'sensitivity' control.
#define AUDIO_IN_PIN 35     // Signal in on this pin
#define NUM_BANDS 8         // To change this, you will need to change the bunch of if statements describing the mapping from bins to bands
#define NOISE 500           // Used as a crude noise filter, values below this are ignored
#define TOP 32
#define FRAMES_PER_SECOND 120
#define SCREEN_WIDTH 127
#define SCREEN_HEIGHT 63
#define MAX_STARS 32
#define QSUBD(x, b) ((x > b) ? b : 0)     // Digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define QSUBA(x, b) ((x > b) ? x - b : 0) // Analog Unsigned subtraction macro. if result <0, then => 0
#define DATA_PIN 18
#define DATA_PIN_A 12
#define LED_TYPE WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS 200
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
FASTLED_USING_NAMESPACE
AsyncWebServer server(80);
TaskHandle_t inputComputeTask = NULL;
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

struct tm timeinfo;
CRGB temp[NUM_LEDS];
CRGB leds_temp[NUM_LEDS / 2]; // half the total number of pixels
CRGB leds[NUM_LEDS];
CRGB ledsTemp[NUM_LEDS];

String openWeatherMapApiKey = OPEN_WEATHER_API_KEY;
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

/*
For EST - UTC -5.00 : -5 * 60 * 60 : -18000
For EDT - UTC -4.00 : -4 * 60 * 60 : -14400
For UTC +0.00 : 0 * 60 * 60 : 0
*/
const char *ntpServer = "pool.ntp.org";
String returnText;
int NUM_FAVORITES = 25; //Max 50, loads all 50 at program load, dynamically assignable
int encoder_unstick = 0;
int fps = 0;   //dev, speed tracking for main loop
int fftps = 0; //dev, speed tracking for fft task
unsigned int sampling_period_us;
volatile int peak[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // The length of these arrays must be >= NUM_BANDS
int tempBandValues[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int oldBandValues[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
volatile int bandValues[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned long newTime;
byte knobReading = 0;
unsigned long tempTime;
int menu[11];
int menu_max[11] = {3, 3, 3, 3, 3, 3, 50, 2, 3, 3, NUM_FAVORITES}; //Root Menu Items, Game Menu Items, Settings Menu Items
int menu_cur = 0;
int runMode = 0;
int mode = 0;
int mode_max = MAX_MODES;
int pattern[6];
int pattern_temp = 0;
int favorite_mode[50];    //declare memory for all 50 favorites
int favorite_pattern[50]; //all are used under the hood
int favorite_slot;
// basic, music, chill, moving colors, legacy
int pattern_max[6] = {12, 12, 22, 65, 80, NUM_FAVORITES};
int pixelNumber = 0;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;
int saveTime = 0;
//LEDs
float breath = 0;
int breathing = 1;
int interfade = 18; //set this to 0 to disable fade in on boot. Set to 25 for fade in.
int interfade_max = 18;
int interfade_speed = 14;

/***********************************************************
  Simplex Noise Variable Declaration
***********************************************************/
//Define simplex noise node for each LED
const int LEDs_in_strip = NUM_LEDS;
const int LEDs_for_simplex = 6;
long tempTimer;
int ledPosition;
int fadeDirection = 0;      // 1 or 0, positive or negative
int fadeDirection2 = 0;     // 1 or 0, positive or negative
int fadeDirectionHTemp = 0; // 1 or 0, positive or negative
int fadeAmount = 5;         // Set the amount to fade -- ex. 5, 10, 15, 20, 25 etc even up to 255.
bool useFade = false;
boolean fadingTail = 0; // Add fading tail? [1=true, 0=falue]
uint8_t fadeRate = 170; // How fast to fade out tail. [0-255]
int8_t delta2 = 1;      // Sets forward or backwards direction amount. (Can be negative.)
int palletPosition;
int colorBarPosition = 1;
bool clearLEDS = false;
uint8_t hueA = 15;      // Start hue at valueMin.
uint8_t satA = 230;     // Start saturation at valueMin.
float valueMin = 120.0; // Pulse minimum value (Should be less then valueMax).
uint8_t hueB = 95;      // End hue at valueMax.
uint8_t satB = 255;     // End saturation at valueMax.
float valueMax = 255.0; // Pulse maximum value (Should be larger then valueMin).
// used in Blendwave
uint8_t speed;
uint8_t loc1;
uint8_t loc2;
uint8_t ran1;
uint8_t ran2;
int red, green, blue;                                    // used in hsv2rgb color functions
int red2, green2, blue2;                                 // used in hsv2rgb color functions
int red3, green3, blue3;                                 // used in hsv2rgb color functions
uint8_t hue = hueA;                                      // Do Not Edit
uint8_t hue2 = hueB;                                     // Do Not Edit
uint8_t sat = satA;                                      // Do Not Edit
float val = valueMin;                                    // Do Not Edit
uint8_t hueDelta = hueA - hueB;                          // Do Not Edit
static float delta = (valueMax - valueMin) / 2.35040238; // Do Not Edit
boolean moving = 1;
uint8_t pos;                    // stores a position for color being blended in
int8_t advance;                 // Stores the advance amount
uint8_t colorStorage;           // Stores a hue color.
uint8_t posR, posG, posB;       // positions of moving R,G,B dots
bool gReverseDirection = false; //false = center outward, true = from ends inward
uint8_t count;
bool sizeUpdate;
int flowDirection = -1;      // Use either 1 or -1 to set flow direction
uint16_t cycleLength = 1500; // Lover values = continuous flow, higher values = distinct pulses.
uint16_t pulseLength = 150;  // How long the pulse takes to fade out.  Higher value is longer.
uint16_t pulseOffset = 200;  // Delay before second pulse.  Higher value is more delay.
uint8_t baseBrightness = 10; // Brightness of LEDs when not pulsing. Set to 0 for off.
// Extra fake LED at the end, to avoid fencepost problem.
// It is used by simplex node and interpolation code.
float LED_array_red[LEDs_in_strip + 1];
float LED_array_green[LEDs_in_strip + 1];
float LED_array_blue[LEDs_in_strip + 1];
int node_spacing = LEDs_in_strip / LEDs_for_simplex;
// Math variables
int i, j, k, A[] = {0, 0, 0};
float u, v, w, s, h;
float hTemp = .420;
float hOld = .0;
static float onethird = 0.333333333;
static float onesixth = 0.166666667;
int T[] = {0x15, 0x38, 0x32, 0x2c, 0x0d, 0x13, 0x07, 0x2a};
// Simplex noise parameters:
float timeinc = 0.0025;
float spaceinc = 0.05;
int intensity_r = 734;
int intensity_g = 734;
int intensity_b = 734;
float yoffset = 0.0;
float yoffsetMAX = 15000;
float xoffset = 0.0;
int currSpeed = 10;
//TO IMPLEMENT
unsigned long frameRateCounter = 0;
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
String categoryName = "";
String functionName = "";
char category_name_out_str[20];
char function_name_out_str[20];
int testValue = 30;

// ----------------------------------------------------------------
// STRUCTs
// ----------------------------------------------------------------
struct Globals
{
  int temp[3];
  int timeZone;
  int tempValue;

  ESP32Encoder encoder;
  ESP32Encoder encoder2;
  CRGB clr1;
  CRGB clr2;
  double vReal[SAMPLES];
  double vImag[SAMPLES];
};
Globals globals = {{}, -5, 0};
arduinoFFT FFT = arduinoFFT(globals.vReal, globals.vImag, SAMPLES, SAMPLING_FREQ);
struct Brightness
{
  int current;
  int temp;
  unsigned long debounce;
};
Brightness brightness = {0, 0, 0};
struct StarModel
{
  int x[MAX_STARS];
  int xx[MAX_STARS];
  int y[MAX_STARS];
  int yy[MAX_STARS];
  int z[MAX_STARS];
};
StarModel star;
struct DvdModel
{
  int x;
  int y;
  int vx;
  int vy;
};
DvdModel dvd1 = {random(0, 32), random(0, 32), 1, 1};
DvdModel dvd2 = {random(0, 32), random(0, 32), 1, 1};
DvdModel dvd3 = {random(0, 32), random(0, 32), 1, 1};

//GAMES
struct Player
{
  int X;
  int Y;
};
Player player = {64, 8};

//FALLIOS
struct Fallios
{
  unsigned int score;
  unsigned int score_top;
  int motion;
  int motionHistory;
  int Y;
  float tunnelGenerator;
};
Fallios fallios = {0, 0, 0, 0, 8, 0};

byte fallios_wall[64];
byte fallios_wallDistance[64];
int fallios_tunnel_1[SCREEN_HEIGHT + 1];
int fallios_tunnel_2[SCREEN_HEIGHT + 1];
int fallios_tunnelWidth = SCREEN_WIDTH / 2;

//BLOCKBREAKER
struct BlockBreaker
{
  int score;
  int ballX;
  int ballY;
  int ballXvel;
  int ballYvel;
  int ballWidth;
  int paddleHeight;
  int paddleWidth;
  int message;
  int messageTimer;
  int running;
};
BlockBreaker blockBreaker = {0, 0, 0, 0, 0, 4, 2, 16, 0, 0, 0};

struct OpenWeatherSettings
{
  String zipCode;
  String countryCode;
  unsigned long weatherTimerDelay;
};
OpenWeatherSettings weatherSettings = {"33701", "US", 70000};

struct OpenWeatherObject
{
  JSONVar weatherJson;
  String currentWeatherId;
  String currentWeatherTitle;
  String currentWeatherDescription;
  String currentTemperature;
  String currentTemperatureMax;
  String currentTemperatureMin;
  String currentHumidity;
  String currentWindSpeed;
  String sunrise;
  String sunset;
  String jsonBuffer;
};
OpenWeatherObject weather;

struct Time
{
  int currentMinute;
  int currentHour;
  int currentDay;
  int currentDate;
  int currentMonth;
  bool currentPM;
};
Time globalTime = {0, 100, 5, 1, 0, 0};

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

struct visualizer_triangle
{
  int x, y;
  int radius;
  float point1, point2, point3;
  int x1, x2, x3;
  int y1, y2, y3;
};

visualizer_triangle t1 = {64, 42, 18, 0.0, 2.1, 4.2, 0, 0, 0, 0, 0, 0};

// ----------------------------------------------------------------
// SETUP
// ----------------------------------------------------------------

void setup()
{
  //Board Status LED Setup

  // setting PWM properties
  const int freq = 5000;
  const int resolution = 13;

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

  WiFi.enableSTA(true);

  WiFi.begin(ssid, password);
  //WiFi.status();
  //WiFi.localIP();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/main.js", "text/javascript");
  });

  // server.on("/obama_not_bad.jpg", HTTP_GET, [](AsyncWebServerRequest *request) {
  //   request->send(SPIFFS, "/obama_not_bad.jpg", "image/jpg");
  // });
  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    brightness.current = 255;
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    brightness.current = 0;
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Start server
  server.begin();

  //Seed variables
  for (int i = 0; i < MAX_STARS; i++)
  {
    star.x[i] = random(0, VISUALIZER_X);
    star.xx[i] = random(1, 4);
    star.y[i] = random(0, VISUALIZER_Y);
    star.yy[i] = random(1, 4);
    star.z[i] = random(1, 4);
  }

  //For troubleshooting
  Serial.begin(115200);

  //Display library initialization
  u8g2.begin();

  //FastLED Declation
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  //FastLED.addLeds<LED_TYPE, DATA_PIN_A, COLOR_ORDER>(leds, NUM_LEDS);

  /* Load Save Settings

    Load variables from EEPROM

    We must check for out of range data
    EEPROM may have been used or not at default

  --------------------*/
  EEPROM.begin(511);

  //EEPROM.write(20, 0);
  //EEPROM.write(21, 0);
  //EEPROM.commit();

  unsigned int word = EEPROM.read(20) + EEPROM.read(21) * 256;

  fallios.score_top = word;

  mode = EEPROM.read(0);
  brightness.current = EEPROM.read(1);

  //Read the pattern setting for each mode
  for (int i = 0; i <= mode_max; i++)
  {
    pattern[i] = EEPROM.read(2 + i);

    //check for out of range data
    if (pattern[i] > pattern_max[i])
    {
      pattern[i] = 0;
    }
  }

  //Make sure values aren't out of range
  if (mode > mode_max)
  {
    mode = 0;
  }

  //Set master brightness control
  FastLED.setBrightness(brightness.current);

  readFavorites();

  //Begin a task named 'fftComputeTask' to handle FFT on the other core
  //This task also takes care of reading the button inputs and computing encoder positions
  //https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html
  xTaskCreatePinnedToCore(
      inputCompute,         /* Function to implement the task */
      "Input Compute Task", /* Name of the task */
      5000,                 /* Stack size in words */
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
  //fftCompute();   //Only needed if not using task

  functionName.toCharArray(function_name_out_str, 20);
  categoryName.toCharArray(category_name_out_str, 20);

  //Clear the display buffer so we can draw new stuff
  u8g2.clearBuffer();

  switch (runMode)
  {
  case 0: //Main run mode
    drawBottom();
    drawTop();
    showBrightnessDisplay();
    break;
  case 1: //Menu mode
    drawMenu();
    break;
  case 2: //Game mode
    switch (menu[1])
    {
    case 0:
      fallios_game();
      break;
    case 1:
      blockbreaker_game();
      break;
    case 2:
      //tetris();
      break;
    }
    break;
  }

  //Show logo instead for first X millis
  showLogo(2500);

  //Clear active button clicks
  knob1.click = 0;
  knob2.click = 0;

  //Pause the fft task to prevent analogRead contention issues during encoder updates
  //vTaskSuspend(fftComputeTask);

  //int tempTime = micros();
  //Wait a moment for the task to finish up
  //while (micros() < (newTime + 1000)) { /* chill */ }

  //start fft processing again
  //vTaskResume(fftComputeTask);
  //Write buffer to display
  u8g2.sendBuffer();

  //future toggle of breathing indicator vs static
  if (breathing == 1)
  {
    breath = (exp(sin(millis() / 4200.0 * PI)) - 0.36787944) * 108.0;
    breath = breath / 2;
    if (breath <= 4)
    {
      breath = 4;
    }
  }
  else
  {
    breath = 4;
  }
  //Write current breath value to status LED
  ledcWrite(STATUS_LED, breath);

  switch (mode)
  {
  case 0:
    basic_category(pattern[mode]);
    break;
  case 1:
    music_category(pattern[mode]);
    break;
  case 2:
    chill_category(pattern[mode]);
    break;
  case 3:
    moving_colors_category(pattern[mode]);
    break;
  case 4:
    legacy_category(pattern[mode]);
    break;
  case 5:
    favorites_category(pattern[mode]);
    break;
  }

  //Detect mode changes and apply interfading
  smoothOperator();

  //Check to see if there are recent knob changes to store in memory
  saveTimeCheck();

  //Output data to LED strip
  showStrip();

  if (useFade == true)
  {
    brightness.current = brightness.current + fadeAmount;
    // reverse the direction of the fading at the ends of the fade:
    if (brightness.current == 0 || brightness.current == 255)
    {
      fadeAmount = -fadeAmount;
    }

    //delay(9); // This delay sets speed of the fade. I usually do from 5-75 but you can always go higher.
  }
  //FastLED.delay(1000/FRAMES_PER_SECOND);

  fps++; //For tracking frame rate/ debug logging

  //Debug Serial Logging

  EVERY_N_MILLISECONDS(60000)
  {
    Serial.print("FPS: ");
    Serial.println(fps / 60);
    fps = 0;
    Serial.print("IPS: ");
    Serial.println(fftps / 60);
    fftps = 0;
    Serial.print("ICT: ");
    Serial.println(eTaskGetState(inputComputeTask));
    Serial.print("MIN: ");
    Serial.println(((millis() / 1000) / 60));
  }

  EVERY_N_MILLISECONDS(200) { gHue++; } // slowly cycle the "base color" through the rainbow
}

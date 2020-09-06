/**************************************************************************

 * Matt Taylor (maylortaylor@gmail.com)


 **************************************************************************/
#define VERSION_INFO "Build 0.2 - 08/23/20"

#include "images.h"

//SAVE SETTINGS
#include "EEPROM.h"

//SCREEN
#include <Wire.h>
#include <U8g2lib.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

//ENCODER
#include <ESP32Encoder.h>

ESP32Encoder encoder;
ESP32Encoder encoder2;

#define knob1C 25 //Program
#define knob2C 14 //Brightness

int knob1_temp = 0;
int knob2_temp = 0;
int tempValue = 0;

#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Replace with your network credentials
const char *ssid = "";
const char *password = "";
String returnText;

AsyncWebServer server(80);

int menu[3];
int menu_max[3] = {2, 1, 2};
int menu_cur = 0;

int runMode = 0;

#define maxModes 5
int mode = 0;
int mode_max = maxModes;
int pattern[5];
int pattern_temp = 0;
int pattern_max[5] = {12, 12, 22, 53, 11};

#define screen_width 127
#define screen_height 63

int knob1Click = 0;
int knob2Click = 0;
int knobBothClick = 0;

int knob1Click_debounce = 0;
int knob2Click_debounce = 0;
int knobBothClick_debounce = 0;

int encoderValue = 0;

int saveTime = 0;

//LEDs
#define statusLED 0
float breath = 0;
int breathing = 1;
#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN 18
//#define CLK_PIN   4
#define LED_TYPE WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS 150
#define visualizer_x 48
#define visualizer_y 128
CRGB leds[NUM_LEDS];

int dvdBounce_x = random(0, 32);
int dvdBounce_y = random(0, 32);
int dvdBounce_vx = 1;
int dvdBounce_vy = 1;

int dvdBounce2_x = random(0, 32);
int dvdBounce2_y = random(0, 32);
int dvdBounce2_vx = 1;
int dvdBounce2_vy = 1;

int dvdBounce3_x = random(0, 32);
int dvdBounce3_y = random(0, 32);
int dvdBounce3_vx = 1;
int dvdBounce3_vy = 1;

int brightness = 0;
int brightness_temp = 0;
int brightness_debounce = 0;

//GAMES
int playerX = 64;
int playerY = 8;
unsigned int fallios_score = 0;
unsigned int fallios_score_top = 0;
int motion = 0;
int motionHistory = 0;
byte wall[64];
byte wallDistance[64];

int tunnel_1[screen_height + 1];
int tunnel_2[screen_height + 1];
int tunnelWidth = screen_width / 2;
float tunnelGenerator = 0;

/***********************************************************
  Simplex Noise Variable Declaration
***********************************************************/
//Define simplex noise node for each LED
const int LEDs_in_strip = NUM_LEDS;
const int LEDs_for_simplex = 6;
CRGB temp[NUM_LEDS];
CRGB leds_temp[NUM_LEDS / 2]; // half the total number of pixels

int fadeDirection = 0;  // 1 or 0, positive or negative
int fadeDirection2 = 0; // 1 or 0, positive or negative
int fadeAmount = 5;     // Set the amount to fade -- ex. 5, 10, 15, 20, 25 etc even up to 255.
bool useFade = false;
boolean fadingTail = 0; // Add fading tail? [1=true, 0=falue]
uint8_t fadeRate = 170; // How fast to fade out tail. [0-255]

int8_t delta2 = 1; // Sets forward or backwards direction amount. (Can be negative.)

int palletPosition;
int colorBarPosition = 1;
bool clearLEDS = false;

uint8_t hueA = 15;      // Start hue at valueMin.
uint8_t satA = 230;     // Start saturation at valueMin.
float valueMin = 120.0; // Pulse minimum value (Should be less then valueMax).

uint8_t hueB = 95;      // End hue at valueMax.
uint8_t satB = 255;     // End saturation at valueMax.
float valueMax = 255.0; // Pulse maximum value (Should be larger then valueMin).

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

// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100
#define COOLING 90

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
#define SPARKING 50

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
#define FRAMES_PER_SECOND 120
unsigned long frameRateCounter = 0;

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

//MSGEQ7 Input
#include <MD_MSGEQ7.h>
// hardware pin definitions - change to suit circuit
#define INPUT_PIN 35
#define RESET_PIN 13
#define STROBE_PIN 2

MD_MSGEQ7 MSGEQ7(RESET_PIN, STROBE_PIN, INPUT_PIN);

String categoryName = "";
String functionName = "";
char category_name_out_str[20];
char function_name_out_str[20];

int testValue = 30;

#define maxStars 32

int star_x[maxStars];
int star_xx[maxStars];
int star_y[maxStars];
int star_yy[maxStars];
int star_z[maxStars];

void setup()
{
  //Board Status LED Setup

  // setting PWM properties
  const int freq = 5000;
  const int resolution = 13;

  //pinMode(ledChannel, OUTPUT); //LED Status Light
  // configure LED PWM functionalitites
  ledcSetup(statusLED, freq, resolution);

  //Set Pin to Output mode to send power to LED
  pinMode(23, OUTPUT);

  //Attach the channel to the GPIO to be controlled
  ledcAttachPin(23, statusLED);

  //Set the status LED to the lowest brightness
  ledcWrite(statusLED, 100);

  // Enabke internal pull up resistors for buttons
  pinMode(knob1C, INPUT_PULLUP); //Knob 1 Click, internal Pull Up (button connects to ground)
  pinMode(knob2C, INPUT_PULLUP); //Knob 2 Click, internal Pull Up (button connects to ground)

  // Enable the weak pull up resistors for encoders
  ESP32Encoder::useInternalWeakPullResistors = UP;

  //Program Selection, encoder WITH Detents
  encoder.attachFullQuad(33, 32);

  //Brightness Adjustment, encoder WITHOUT Detents
  encoder2.attachFullQuad(27, 26);

  // set starting count value after attaching
  encoder.clearCount();

  // clear the encoder's raw count and set the tracked count to zero
  encoder2.clearCount();

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

  server.on("/obama_not_bad.jpg", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/obama_not_bad.jpg", "image/jpg");
  });
  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    brightness = 255;
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    brightness = 0;
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Start server
  server.begin();

  //Seed variables
  for (int i = 0; i < maxStars; i++)
  {
    star_x[i] = random(0, visualizer_x);
    star_xx[i] = random(1, 4);
    star_y[i] = random(0, visualizer_y);
    star_yy[i] = random(1, 4);
    star_z[i] = random(1, 4);
  }

  //Sound library initialization
  MSGEQ7.begin();

  //For troubleshooting
  Serial.begin(9600);

  //Display library initialization
  u8g2.begin();

  //Show logo
  u8g2.setBitmapMode(true /* transparent*/);
  u8g2.drawXBMP(32, 0, myBitmap_width, myBitmap_height, myBitmap);
  u8g2.sendBuffer();

  //wait 1 second
  delay(1000);

  //FastLED Declation
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  /* Load Save Settings

    Load variables from EEPROM

    We must check for out of range data
    EEPROM may have been used or not at default

  --------------------*/
  EEPROM.begin(100);

  //EEPROM.write(20, 0);
  //EEPROM.write(21, 0);
  //EEPROM.commit();

  unsigned int word = EEPROM.read(20) + EEPROM.read(21) * 256;

  fallios_score_top = word;

  mode = EEPROM.read(0);
  brightness = EEPROM.read(1);

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
  FastLED.setBrightness(brightness);
}

void loop()
{
  MSGEQ7.read();

  functionName.toCharArray(function_name_out_str, 20);
  categoryName.toCharArray(category_name_out_str, 20);

  //Clear the display buffer so we can draw new stuff
  u8g2.clearBuffer();

  switch (runMode)
  {
  case 0:
    drawBottom();
    drawTop();
    break;
  case 1:
    drawMenu();
    break;
  case 2:
    fallios();
    break;
  }

  //Update variables compared to current encoder location
  updateEncoders();

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

  ledcWrite(statusLED, breath);

  testValue += MSGEQ7.get(0) / 16;
  if (testValue > 255)
  {
    testValue = 255;
  }

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
  }
  //WS LED
  FastLED.show();

  if (useFade == true)
  {
    brightness = brightness + fadeAmount;
    // reverse the direction of the fading at the ends of the fade:
    if (brightness == 0 || brightness == 255)
    {
      fadeAmount = -fadeAmount;
    }

    delay(9); // This delay sets speed of the fade. I usually do from 5-75 but you can always go higher.
  }
  //FastLED.delay(1000/FRAMES_PER_SECOND);

  EVERY_N_MILLISECONDS(200) { gHue++; } // slowly cycle the "base color" through the rainbow
}

/*

void showData() {
  display.clearDisplay();

  display.setTextSize(1);             // Draw 2X-scale text
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("#1 #2 #3"));
  display.setCursor(0,20);
  testValue = knob1.read()/4;
  if (testValue < 0) {
    knob1.write(0);
    testValue = 0;
  }
  display.println(testValue);
  testValue += MSGEQ7.get(0)/16;
  if (testValue > 255) {
    testValue = 255;
  }
  FastLED.setBrightness(testValue);
  display.setCursor(40,20);
  testValue = knob2.read()/4;
    if (testValue < 0) {
    knob1.write(0);
    testValue = 0;
  }
  display.println(testValue);
  display.setCursor(80,20);
  testValue = knob3.read()/4;
    if (testValue < 0) {
    knob1.write(0);
    testValue = 0;
  }
  display.println(testValue);

  display.setCursor(20,40);
  display.print(1000/(millis() - frameRateCounter));
  frameRateCounter = millis();

  display.setCursor(60,40);
  display.print(MSGEQ7.get(0));
  display.display();
}
*/

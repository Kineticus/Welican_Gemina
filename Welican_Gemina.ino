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
#include <Encoder.h>

Encoder knob1(33, 32); //Program Selection, encoder WITH Detents
Encoder knob2(27, 26); //Brightness Adjustment, encoder WITHOUT Detents
#define knob1C 25
#define knob2C 14

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

#define maxModes 4
int mode = 0;
int mode_max = 3;

int menu[3];
int menu_max[3] = {2, 1, 2};
int menu_cur = 0;

int runMode = 0;

int pattern[4];
int pattern_temp = 0;
int pattern_max[4] = {12, 12, 22, 17};

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

int fadeDirection = 0; // 1 or 0, positive or negative

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
uint8_t sat = satA;                                      // Do Not Edit
float val = valueMin;                                    // Do Not Edit
uint8_t hueDelta = hueA - hueB;                          // Do Not Edit
static float delta = (valueMax - valueMin) / 2.35040238; // Do Not Edit

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

  //Button input configuration
  pinMode(knob1C, INPUT_PULLUP); //Knob 1 Click, internal Pull Up (button connects to ground)
  pinMode(knob2C, INPUT_PULLUP); //Knob 2 Click, internal Pull Up (button connects to ground)

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

  server.on("/obama_not_bad.jpg", HTTP_GET, [](AsyncWebServerRequest *request){
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

  switch(runMode)
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
  }
  //WS LED
  FastLED.show();

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

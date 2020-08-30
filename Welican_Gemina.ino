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
//Encoder knob3(26, 27); //

#define maxModes 3
int mode = 0;
int mode_max = 2;

int gameMode = 0;

int pattern[3];
int pattern_max[3] = {12, 12, 22};

int screen_width = 128;
int screen_height = 64;

int knob1Click = 0;
int knob2Click = 0;
int knobBothClick = 0;

int knob1Click_debounce = 0;
int knob2Click_debounce = 0;
int knobBothClick_debounce = 0;

int encoderValue = 0;

int saveTime = 0;

//LEDs
#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN 18
//#define CLK_PIN   4
#define LED_TYPE WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS 50
#define visualizer_x 48
#define visualizer_y 128
CRGB leds[NUM_LEDS];

int dvdBounce_x = random(0, 32);
int dvdBounce_y = random(0, 32);
int dvdBounce_vx = 1;
int dvdBounce_vy = 1;

int brightness = 96;
int brightness_debounce = 0;

//GAMES
int playerX = 64;
int playerY = 32;
byte wall[64];
byte wallDistance[64];

/***********************************************************
  Simplex Noise Variable Declaration
***********************************************************/
//Define simplex noise node for each LED
const int LEDs_in_strip = NUM_LEDS;
const int LEDs_for_simplex = 6;

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
#define INPUT_PIN 15
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

  for (int i = 0; i < maxStars; i++)
  {
    star_x[i] = random(0, visualizer_x);
    star_xx[i] = random(1, 4);
    star_y[i] = random(0, visualizer_y);
    star_yy[i] = random(1, 4);
    star_z[i] = random(1, 4);
  }

  EEPROM.begin(100);

  MSGEQ7.begin();

  Serial.begin(9600);

  u8g2.begin();

  // SHOW LOGO
  u8g2.setBitmapMode(true /* transparent*/);
  u8g2.drawXBMP(32, 0, myBitmap_width, myBitmap_height, myBitmap);
  u8g2.sendBuffer();
  delay(1000);

  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(brightness);

  pinMode(25, INPUT_PULLUP); //Knob 1 Click, internal Pull Up (button connects to ground)
  pinMode(14, INPUT_PULLUP); //Knob 2 Click, internal Pull Up (button connects to ground)

  pinMode(23, OUTPUT);

  // setting PWM properties
  const int freq = 4000;
  const int statusLED = 0;
  const int resolution = 8;

  //pinMode(ledChannel, OUTPUT); //LED Status Light
  // configure LED PWM functionalitites
  ledcSetup(statusLED, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(23, statusLED);

  ledcWrite(statusLED, 1);
  //digitalWrite(37, HIGH);
  /* Load Save Settings

    Load variables from EEPROM

    We must check for out of range data
    EEPROM may have been used or not at default

  --------------------*/
  mode = EEPROM.read(0);
  brightness = EEPROM.read(1);

  //brightness = 128;

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
}

void loop()
{
  MSGEQ7.read();

  functionName.toCharArray(function_name_out_str, 20);
  categoryName.toCharArray(category_name_out_str, 20);

  //i2c LCD
  //showData();
  u8g2.clearBuffer();

  if (gameMode == 1)
  {
    fallios();
  }
  else
  {
    drawBottom();
    drawTop();
  }

  updateEncoders();

  u8g2.sendBuffer();

  testValue += MSGEQ7.get(0) / 16;
  if (testValue > 255)
  {
    testValue = 255;
  }

  switch (mode)
  {
  case 0:
    categoryName = "BASIC";
    basic_mode();
    break;
  case 1:
    categoryName = "MUSIC";
    music_mode();
    break;
  case 2:
    categoryName = "CHILL";
    chill_mode();
    break;
  }

  //WS LED
  FastLED.show();

  //FastLED.delay(1000/FRAMES_PER_SECOND);

  EVERY_N_MILLISECONDS(200) { gHue++; } // slowly cycle the "base color" through the rainbow
}

void u8g2_disc_circle(uint8_t a)
{
  //u8g2.drawStr( 0, 0, "drawDisc");
  //u8g2.drawDisc(10,18,9);
  //u8g2.drawDisc(24+a,16,7);
  //u8g2.drawStr( 0, 30, "drawCircle");
  u8g2.drawCircle(10, 18 + 30, 9);
  u8g2.drawCircle(24 + a, 16 + 30, 7);
}
void u8g2_bitmap_overlay(uint8_t a)
{
  uint8_t frame_size = 28;

  //  u8g2.drawStr(0, frame_size + 12, "Solid / transparent");
  //  u8g2.setBitmapMode(false /* solid */);
  //  u8g2.drawFrame(0, 10, frame_size, frame_size);
  //  u8g2.drawXBMP(2, 12, cross_width, cross_height, cross_bits);
  //  if(a & 4)
  //    u8g2.drawXBMP(7, 17, cross_block_width, cross_block_height, cross_block_bits);
  //
  u8g2.setBitmapMode(true /* transparent*/);
  //u8g2.drawFrame(frame_size + 5, 10, frame_size, frame_size);
  //  u8g2.drawXBMP(frame_size + 7, 12, cross_width, cross_height, cross_bits);
  //  if(a & 4)
  //    u8g2.drawXBMP(frame_size + 12, 17, cross_block_width, cross_block_height, cross_block_bits);

  u8g2.drawXBMP(64, 32, myBitmap_width, myBitmap_height, myBitmap);
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

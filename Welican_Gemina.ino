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
 **************************************************************************/
#define VERSION_INFO "Build 0.420 - 09/16/20"

#include "images.h"

//SAVE SETTINGS
#include "EEPROM.h"

//SCREEN
#include <Wire.h>
#include <U8g2lib.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

//ENCODER
#include <ESP32Encoder.h>

#define CONFIG_FILENAME F("/wifi_cred.dat")

ESP32Encoder encoder;
ESP32Encoder encoder2;

#define knob1C 25 //Program
#define knob2C 4  //Brightness 14

int knob1_temp = 0;
int knob2_temp = 0;
int tempValue = 0;
int encoder_unstick = 0;

//AUDIO INPUT
#include <arduinoFFT.h>

#define SAMPLES 512         // Must be a power of 2. FAST 256 (40fps), NORMAL 512 (20fps), ACCURATE 1024 (10fps)
#define SAMPLING_FREQ 40000 // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define AMPLITUDE 3000      // Depending on your audio source level, you may need to alter this value. Can be used as a 'sensitivity' control.
#define AUDIO_IN_PIN 35     // Signal in on this pin
#define NUM_BANDS 8         // To change this, you will need to change the bunch of if statements describing the mapping from bins to bands
#define NOISE 500           // Used as a crude noise filter, values below this are ignored
#define TOP 32

int fps = 0;   //dev, speed tracking for main loop
int fftps = 0; //dev, speed tracking for fft task
unsigned int sampling_period_us;
volatile int peak[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // The length of these arrays must be >= NUM_BANDS
int tempBandValues[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int oldBandValues[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
volatile int bandValues[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long newTime;
byte knobReading = 0;
unsigned long tempTime;
arduinoFFT FFT = arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQ);

TaskHandle_t inputComputeTask = NULL;

//WiFi, Web Server, and storage for web assets
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Replace with your network credentials
const char *ssid = "";
const char *password = "";
String returnText;

AsyncWebServer server(80);

int menu[4];
int menu_max[4] = {2, 2, 2, 2}; //Root Menu Items, Game Menu Items, Settings Menu Items
int menu_cur = 0;

int runMode = 0;

#define maxModes 4
int mode = 0;
int mode_max = maxModes;
int pattern[5];
int pattern_temp = 0;
// basic, music, chill, moving colors, legacy
int pattern_max[5] = {12, 12, 22, 65, 80};
int pixelNumber = 0;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;

#define screen_width 127
#define screen_height 63

#define qsubd(x, b) ((x > b) ? b : 0)     // Digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define qsuba(x, b) ((x > b) ? x - b : 0) // Analog Unsigned subtraction macro. if result <0, then => 0

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
#define DATA_PIN_A 12
//#define CLK_PIN   4
#define LED_TYPE WS2811
#define COLOR_ORDER RGB
#define NUM_LEDS 100
#define visualizer_x 48
#define visualizer_y 128
CRGB leds[NUM_LEDS];

//GAMES
int playerX = 64;
int playerY = 8;

//FALLIOS
unsigned int fallios_score = 0;
unsigned int fallios_score_top = 0;
int fallios_motion = 0;
int fallios_motionHistory = 0;
int fallios_Y = 8;
byte fallios_wall[64];
byte fallios_wallDistance[64];

int fallios_tunnel_1[screen_height + 1];
int fallios_tunnel_2[screen_height + 1];
int fallios_tunnelWidth = screen_width / 2;
float fallios_tunnelGenerator = 0;

//BLOCKBREAKER
int blockbreaker_score;
int blockbreaker_ballX;
int blockbreaker_ballY;
int blockbreaker_ballXvel;
int blockbreaker_ballYvel;
int blockbreaker_ballWidth = 4;
int blockbreaker_paddleHeight = 2;
int blockbreaker_paddleWidth = 16;
int blockbreaker_message = 0;
int blockbreaker_messageTimer = 0;
int blockbreaker_running = 0;

/***********************************************************
  Simplex Noise Variable Declaration
***********************************************************/
//Define simplex noise node for each LED
const int LEDs_in_strip = NUM_LEDS;
const int LEDs_for_simplex = 6;
CRGB temp[NUM_LEDS];
CRGB leds_temp[NUM_LEDS / 2]; // half the total number of pixels

long tempTimer;
int ledPosition;
int fadeDirection = 0;      // 1 or 0, positive or negative
int fadeDirection2 = 0;     // 1 or 0, positive or negative
int fadeDirectionHTemp = 0; // 1 or 0, positive or negative
int fadeAmount = 5;         // Set the amount to fade -- ex. 5, 10, 15, 20, 25 etc even up to 255.
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

// used in Blendwave
CRGB clr1;
CRGB clr2;
uint8_t speed;
uint8_t loc1;
uint8_t loc2;
uint8_t ran1;
uint8_t ran2;
// -------------------

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

String categoryName = "";
String functionName = "";
char category_name_out_str[20];
char function_name_out_str[20];

int testValue = 30;

//VISUALIZERS
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
unsigned long brightness_debounce = 0;

#define maxStars 32

int star_x[maxStars];
int star_xx[maxStars];
int star_y[maxStars];
int star_yy[maxStars];
int star_z[maxStars];

struct visualizer_triangle
{
  int x, y;
  int radius;
  float point1, point2, point3;
  int x1, x2, x3;
  int y1, y2, y3;
<<<<<<< HEAD
};
  
=======
} visualizer_triangle;

>>>>>>> d4af1075484a06f9473cbb24695e33f3d7a46fb3
visualizer_triangle t1 = {64, 42, 18, 0.0, 2.1, 4.2, 0, 0, 0, 0, 0, 0};

int temp1 = 0;
int temp2 = 0;
int temp3 = 0;

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
  //encoder2.attachFullQuad(27, 26);
  encoder2.attachFullQuad(16, 17); //RX2 and TX2

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

  //For troubleshooting
  Serial.begin(115200);

  //Display library initialization
  u8g2.begin();

  //Show logo
  u8g2.setBitmapMode(true /* transparent*/);
  u8g2.drawXBMP(32, 0, myBitmap_width, myBitmap_height, myBitmap);
  u8g2.sendBuffer();

  //wait 1 second
  delay(1000);

  //FastLED Declation
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE, DATA_PIN_A, COLOR_ORDER>(leds, NUM_LEDS);
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

  //Begin a task named 'fftComputeTask' to handle FFT on the other core
  //This task also takes care of reading the button inputs and computing encoder positions
  //https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html
  xTaskCreatePinnedToCore(
      inputCompute,         /* Function to implement the task */
      "Input Compute Task", /* Name of the task */
      2000,                 /* Stack size in words */
      NULL,                 /* Task input parameter */
      0,                    /* Priority of the task, lower is lower */
      &inputComputeTask,    /* Task handle. */
      0);                   /* Pin to specific CPU Core, main Loop runs on 1*/
}

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
    case 1:
      fallios();
      break;
    case 2:
      blockbreaker();
      break;
    }
    break;
  }

  //Clear active button clicks
  knob1Click = 0;
  knob2Click = 0;

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
  ledcWrite(statusLED, breath);

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
  showStrip();

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

  //Debug Serial Logging
  EVERY_N_MILLISECONDS(1000)
  {
    Serial.print("FPS: ");
    Serial.println(fps);
    fps = 0;
    Serial.print("IPS: ");
    Serial.println(fftps);
    fftps = 0;
    Serial.print("State: ");
    Serial.println(eTaskGetState(inputComputeTask));
    Serial.print("newTime: ");
    Serial.println(micros() - newTime);
    Serial.print("Minutes: ");
    Serial.println(((millis() / 1000) / 60));
    Serial.print("Encoder: ");
    Serial.println(int((abs(encoder.getCount())) % 4));
  }

  EVERY_N_MILLISECONDS(200) { gHue++; } // slowly cycle the "base color" through the rainbow
  fps++;                                //For debug logging
}

void inputCompute(void *parameter)
{
  //Create an infinite for loop as this is a task and we want it to keep repeating
  for (;;)
  {
    // Sample the audio pin
    for (int i = 0; i < SAMPLES; i++)
    {
      newTime = micros();
      vReal[i] = analogRead(AUDIO_IN_PIN); // A conversion takes about 9.7uS on an ESP32
      vImag[i] = 0;
      while ((micros() - newTime) < sampling_period_us)
      {
        /* chill */
      }
    }

    //Serial.print("A ");
    //Serial.println(millis());
    //updateEncoders();

    // Compute FFT
    FFT.DCRemoval();
    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();

    // Reset temp variables
    for (int i = 0; i < NUM_BANDS; i++)
    {
      tempBandValues[i] = 0;
    }

    // Analyse FFT results
    for (int i = 2; i < (SAMPLES / 2); i++)
    { // Don't use sample 0 and only first SAMPLES/2 are usable. Each array element represents a frequency bin and its value the amplitude.
      if (vReal[i] > NOISE)
      { // Add a crude noise filter

        //8 bands, 12kHz top band
        if (i <= 3)
          tempBandValues[0] += (int)vReal[i];
        if (i > 3 && i <= 6)
          tempBandValues[1] += (int)vReal[i];
        if (i > 6 && i <= 13)
          tempBandValues[2] += (int)vReal[i];
        if (i > 13 && i <= 27)
          tempBandValues[3] += (int)vReal[i];
        if (i > 27 && i <= 55)
          tempBandValues[4] += (int)vReal[i];
        if (i > 55 && i <= 112)
          tempBandValues[5] += (int)vReal[i];
        if (i > 112 && i <= 229)
          tempBandValues[6] += (int)vReal[i];
        if (i > 229)
          tempBandValues[7] += (int)vReal[i];

        /*16 bands, 12kHz top band 
        if (i<=2 )           tempBandValues[0]  += (int)vReal[i];
        if (i>2   && i<=3  ) tempBandValues[1]  += (int)vReal[i];
        if (i>3   && i<=5  ) tempBandValues[2]  += (int)vReal[i];
        if (i>5   && i<=7  ) tempBandValues[3]  += (int)vReal[i];
        if (i>7   && i<=9  ) tempBandValues[4]  += (int)vReal[i];
        if (i>9   && i<=13 ) tempBandValues[5]  += (int)vReal[i];
        if (i>13  && i<=18 ) tempBandValues[6]  += (int)vReal[i];
        if (i>18  && i<=25 ) tempBandValues[7]  += (int)vReal[i];
        if (i>25  && i<=36 ) tempBandValues[8]  += (int)vReal[i];
        if (i>36  && i<=50 ) tempBandValues[9]  += (int)vReal[i];
        if (i>50  && i<=69 ) tempBandValues[10] += (int)vReal[i];
        if (i>69  && i<=97 ) tempBandValues[11] += (int)vReal[i];
        if (i>97  && i<=135) tempBandValues[12] += (int)vReal[i];
        if (i>135 && i<=189) tempBandValues[13] += (int)vReal[i];
        if (i>189 && i<=264) tempBandValues[14] += (int)vReal[i];
        if (i>264          ) tempBandValues[15] += (int)vReal[i];*/
      }
    }

    //Refresh main variables with temp data
    for (int i = 0; i < NUM_BANDS; i++)
    {
      bandValues[i] = tempBandValues[i];
    }

    //Look for Peaks
    for (byte band = 0; band < NUM_BANDS; band++)
    {

      if (bandValues[band] > peak[band])
      {
        peak[band] = bandValues[band];
      }

      // Decay peak
      for (byte band = 0; band < NUM_BANDS; band++)
        if (peak[band] > 500)
          peak[band] -= 500;
    }

    //Update variables compared to current encoder location
    updateEncoders();
    fftps++;

    //Serial.println(xPortGetFreeHeapSize());
    //vTaskDelay(50);
  }
}
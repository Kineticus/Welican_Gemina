void drawDebug()
{
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(0, 8);
  u8g2.print(VERSION_INFO);
  u8g2.setCursor(0, 24);
  u8g2.print("Knob 1: ");
  //u8g2.print(encoder.getCount());
  u8g2.setCursor(80, 24);
  u8g2.print(pattern[mode]);

  if (knob1Click == true)
  {
    u8g2.setCursor(0, 36);
    u8g2.print("CLICK");
  }
  u8g2.setCursor(0, 48);
  u8g2.print("Knob 2: ");
  //u8g2.print(encoder2.getCount());
  if (knob2Click == true)
  {
    u8g2.setCursor(0, 60);
    u8g2.print("CLICK");
  }

  u8g2.setCursor(80, 48);
  u8g2.print(brightness);

  u8g2.setCursor(80, 64);
  u8g2.print(mode);
}

void updateEncoders()
{
  //--CLICK--

  //Clear active button clicks
  knob1Click = 0;
  knob2Click = 0;

  //Read knob 1 digital pin, button pulls pin low
  tempValue = digitalRead(knob1C);

  //Is the button pulling the pin low and the debounce counter is at 0 (no recent button press) ?
  if ((tempValue == false) && (knob1Click_debounce == 0))
  {
    //if yes we should set a debounce variable
    knob1Click_debounce = 3;

    //And set click for Knob 1 to True!
    knob1Click = 1;

    //Are we running in normal mode? If not we can skip these checks
    if (runMode == 0)
    {
      //Check to see if the Brightness Knob (#2) is also held down
      if (knob2Click_debounce == 0)
      {
        //It's not? Just advance the mode by once
        mode += 1;

        //Since we have changed the mode we should save it in a bit
        saveTime = 100;

        //Check to make sure we haven't gone over the maximum amount of modes
        if (mode > mode_max)
        {
          //if we did go over let's roll mode back to 0
          mode = 0;
        }
      }
      else
      {
        //brightness knob is clicked at the same time as the program knob?
        //setGameMode();
        runMode = 1;
        menu_cur = 0;
        knob1Click = 0;
        knob2Click = 0;
      }
    }
  }
  if ((tempValue == true) && (knob1Click_debounce > 0))
  {
    knob1Click_debounce -= 1;
  }

  //Read knob 2 digital pin, button pulls pin low
  tempValue = digitalRead(knob2C);
  if ((tempValue == false) && (knob2Click_debounce == 0))
  {
    knob2Click_debounce = 3;
    knob2Click = 1;
  }
  if ((tempValue == true) && (knob2Click_debounce > 0))
  {
    knob2Click_debounce -= 1;
  }

  /* BOTH CLICK AT ONCE
  if (knobBothClick_debounce > 0)
  {
    knobBothClick_debounce -= 1;
  }
  if ((knob1Click_debounce > 0) && (knob2Click_debounce > 0))
  {
    knobBothClick_debounce = 3;
    knobBothClick = 1;
  } 
  */

  //--PATTERN ENCODER--

  tempValue = encoder.getCount() - knob1_temp; //Read current knob position vs. last time we checked

  if (runMode == 0)
  {
    while (tempValue >= 4)
    { //Quadrature encoder sends 4 pulses for each physical detent. Anything less than that we ignore
      tempValue -= 4;
      knob1_temp += 4;
      pattern[mode] += 1;
      saveTime = 100;
    }
    while (tempValue <= -4)
    {
      tempValue += 4;
      knob1_temp -= 4;
      pattern[mode] -= 1;
      saveTime = 100;
    }

    //Constrain Mode - add switch to allow 3 options - constrain; rollover back to beginning/end; rollover to next/previous mode
    if (pattern[mode] > pattern_max[mode])
    {
      //Mode 1 - constrain
      pattern[mode] = pattern_max[mode];
    }
    else if (pattern[mode] < 0)
    {
      //Mode 1 - constrain
      pattern[mode] = 0;
    }
  }
  else if (runMode == 1)
  {
    while (tempValue >= 4)
    { //Quadrature encoder sends 4 pulses for each physical detent. Anything less than that we ignore
      tempValue -= 4;
      knob1_temp += 4;
      menu[menu_cur] += 1;
    }
    while (tempValue <= -4)
    {
      tempValue += 4;
      knob1_temp -= 4;
      menu[menu_cur] -= 1;
    }
    if (menu[menu_cur] > menu_max[menu_cur])
    {
      //Mode 1 - constrain
      menu[menu_cur] = menu_max[menu_cur];
    }
    else if (menu[menu_cur] < 0)
    {
      //Mode 1 - constrain
      menu[menu_cur] = 0;
    }
  }
  else if (runMode == 2)
  {
    while (tempValue >= 4)
    { //Quadrature encoder sends 4 pulses for each physical detent. Anything less than that we ignore
      tempValue -= 4;
      knob1_temp += 4;
      playerX += 4;
    }
    while (tempValue <= -4)
    {
      tempValue += 4;
      knob1_temp -= 4;
      playerX -= 4;
    }
  }

  //--BRIGHTNESS ENCODER--

  tempValue = encoder2.getCount() - knob2_temp; //Read current knob position vs. last time we checked
  knob2_temp = encoder2.getCount();             //Store this position to compare next time around

  if (runMode == 0)
  {
    //Determine "acceleration" based on change amount. Large change = fast turn of knob
    //There are 96 pulses per revolution

    if (abs(tempValue) > 10) // 100% acceleration
    {
      tempValue = tempValue * 7;
    }
    else if (abs(tempValue) > 7) // 75%
    {
      tempValue = tempValue * 5;
    }
    else if (abs(tempValue) > 4) // 50%
    {
      tempValue = tempValue * 3;
    }
    else if (abs(tempValue) > 2) // 25%  acceleration
    {
      tempValue = tempValue * 2;
    }
    else //No acceleration applied
    {
      tempValue = tempValue;
    }

    //Add adjusted value to brightness
    brightness += tempValue;

    //Constrain (for some reason constrain function gave me fits)
    if (brightness > 255)
    {
      brightness = 255;
    }
    if (brightness < 0)
    {
      brightness = 0;
    }

    // set master brightness control
    FastLED.setBrightness(brightness);

    showBrightnessDisplay();
  }
  else if (runMode == 2)
  {
    while (tempValue > 0)
    { //Quadrature encoder sends 4 pulses for each physical detent. Anything less than that we ignore
      tempValue -= 1;
      playerX += 1;
    }
    while (tempValue < 0)
    {
      tempValue += 1;
      playerX -= 1;
    }
  }

  if (saveTime > 0)
  {
    saveTime -= 1;
  }

  if (saveTime == 1)
  {
    EEPROM.write(0, mode);
    EEPROM.write(1, brightness);

    for (int i = 0; i <= mode_max; i++)
    {
      EEPROM.write(2 + i, pattern[i]);
    }
    EEPROM.commit();
  }
}

void setGameMode()
{
  runMode = 2;
  fallios_reset();
  brightness_temp = brightness;
  pattern_temp = pattern[mode];
}

void endGameMode()
{
  //Run update encoder to sync encoders
  updateEncoders();

  //Set values to right when game mode started in case they got dorked with
  brightness = brightness_temp;
  pattern[mode] = pattern_temp;

  //Don't want to see brightness indicator when we leave
  brightness_debounce = 0;

  //Set runMode (like Run mode) back to default, 0
  runMode = 0;
}

void showBrightnessDisplay()
{
  int frameX = 44;
  int frameY = 22;
  int frameW = 38;
  int frameH = 39;

  if ((tempValue != 0) || (brightness_debounce > 0))
  {
    u8g2.setDrawColor(0);
    u8g2.drawBox(frameX, frameY - 1, frameW, frameH);
    u8g2.setDrawColor(1);
    u8g2.drawRFrame(frameX, frameY - 1, frameW, frameH, 7);

    if (brightness == 0)
    {
      u8g2.drawXBMP(frameX, frameY, brightness1_width, brightness1_height, brightness1);
    }
    else if (brightness == 255)
    {
      u8g2.drawXBMP(frameX, frameY, brightness8_width, brightness8_height, brightness8);
    }
    else if (brightness > 200)
    {
      u8g2.drawXBMP(frameX, frameY, brightness7_width, brightness7_height, brightness7);
    }
    else if (brightness > 160)
    {
      u8g2.drawXBMP(frameX, frameY, brightness6_width, brightness6_height, brightness6);
    }
    else if (brightness > 120)
    {
      u8g2.drawXBMP(frameX, frameY, brightness5_width, brightness5_height, brightness5);
    }
    else if (brightness > 80)
    {
      u8g2.drawXBMP(frameX, frameY, brightness4_width, brightness4_height, brightness4);
    }
    else if (brightness > 40)
    {
      u8g2.drawXBMP(frameX, frameY, brightness3_width, brightness3_height, brightness3);
    }
    else if (brightness > 0)
    {
      u8g2.drawXBMP(frameX, frameY, brightness2_width, brightness2_height, brightness2);
    }

    if (brightness_debounce > 0)
    {
      brightness_debounce -= 1;
    }
    if (tempValue != 0)
    {
      brightness_debounce = 30;
    }
  }
}

void drawTop()
{
  //Only use top 16 rows!!
  u8g2.setFont(u8g2_font_profont12_mf);

  //Blackout box
  u8g2.setDrawColor(0);
  u8g2.drawBox(0, 0, visualizer_y, 16);
  u8g2.setDrawColor(1);

  switch (mode)
  {
  case 0:
    u8g2.drawXBMP(0, 0, star_width, star_height, star);
    break;
  case 1:
    u8g2.drawXBMP(0, 0, wave_width, wave_height, wave);
    // u8g2.drawXBMP(0,0,musicNote_width, musicNote_height, musicNote);
    break;
  case 2:
    u8g2.drawXBMP(0, 0, hashtag_width, hashtag_height, hashtag);
    break;
  case 3:
    u8g2.drawXBMP(0, 0, donut_width, donut_height, donut);
    break;
  case 4:
    u8g2.drawXBMP(0, 0, heart_width, heart_height, heart);
    break;
  }

  //u8g2.print(mode);
  u8g2.setCursor(12, 8);
  u8g2.print(pattern[mode]);
  u8g2.setCursor(32, 8);
  u8g2.print(function_name_out_str);
  //u8g2.drawXBMP(42,0,donut_width, donut_height, donut);
  //u8g2.drawXBMP(54,0,musicNote_width, musicNote_height, musicNote);
  //u8g2.drawXBMP(68,0,heart_width, heart_height, heart);
  u8g2_horizontal_line(16);
  drawProgressBar();
}

void drawBottom()
{
  switch (mode)
  {
  case 0:
    dvdBounce();
    break;
  case 1:
    drawCircleEQ();
    drawDiscSectionsEQ();
    drawEQ();
    break;
  case 2:
    gravityWell();
    break;
  case 3:
    drawIPAddress();
    //gravityWell();
    break;
  case 4:
    starBounce();
    break;
  }
}

void drawMenu()
{
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(0, 8);
  u8g2.print("This is a Menu!");
  u8g2.setCursor(0, 32);

  switch (menu_cur)
  {
  case 0:
    switch (menu[menu_cur])
    {
    case 0:
      u8g2.print("Games");
      break;
    case 1:
      u8g2.print("Settings");
      break;
    case 2:
      u8g2.print("Exit");
    }
    break;
  case 1: //games menu
    switch (menu[menu_cur])
    {
    case 0:
      u8g2.print("Back");
      break;
    case 1:
      u8g2.print("Fallios");
      break;
    }
    break;
  }

  if (knob2Click == 1)
  {
    runMode = 0;
  }

  if (knob1Click == 1)
  {
    switch (menu_cur)
    {
    case 0: //main menu
      switch (menu[menu_cur])
      {
      case 0:
        menu_cur = 1; //games
        break;
      case 1:
        menu_cur = 2; //settings
        break;
      case 2:
        runMode = 0; //exit
        break;
      }
      break;
    case 1: // games menu click
      switch (menu[menu_cur])
      {
      case 0:
        menu_cur = 0; //back to main menu
        break;
      case 1:
        runMode = 2; //fallios
        setGameMode();
      }
    }
  }
}

void drawProgressBar()
{
  int boxWidth = (screen_width / pattern_max[mode]);
  if (boxWidth < 4)
  {
    boxWidth = 4;
  }
  u8g2.drawBox(((float(screen_width - boxWidth) / pattern_max[mode]) * pattern[mode]), 12, boxWidth, 4);
}

void addGlitter(fract8 chanceOfGlitter)
{
  if (random8() < chanceOfGlitter)
  {
    leds[random16(NUM_LEDS)] += CRGB::White;
  }
}

void customColor(int r, int g, int b)
{
  fill_solid(leds, LEDs_in_strip, CRGB(r, g, b));
}

void plasma(CRGBPalette16 currentPalette, TBlendType currentBlending)
{ // This is the heart of this program. Sure is short. . . and fast.

  int thisPhase = beatsin8(6, -64, 64); // Setting phase change for a couple of waves.
  int thatPhase = beatsin8(7, -64, 64);

  for (int k = 0; k < NUM_LEDS; k++)
  { // For each of the LED's in the strand, set a brightness based on a wave as follows:

    int colorIndex = cubicwave8((k * 23) + thisPhase) / 2 + cos8((k * 15) + thatPhase) / 2; // Create a wave and add a phase change and add another wave with its own phase change.. Hey, you can even change the frequencies if you wish.
    int thisBright = qsuba(colorIndex, beatsin8(7, 0, 96));                                 // qsub gives it a bit of 'black' dead space by setting sets a minimum value. If colorIndex < current value of beatsin8(), then bright = 0. Otherwise, bright = colorIndex..

    leds[k] = ColorFromPalette(currentPalette, colorIndex, thisBright, currentBlending); // Let's now add the foreground colour.
  }
}
void beatwave(CRGBPalette16 currentPalette, TBlendType currentBlending)
{
  // https://github.com/atuline/FastLED-Demos/blob/master/beatwave/beatwave.ino

  uint8_t wave1 = beatsin8(9, 0, 255); // That's the same as beatsin8(9);
  uint8_t wave2 = beatsin8(8, 0, 255);
  uint8_t wave3 = beatsin8(7, 0, 255);
  uint8_t wave4 = beatsin8(6, 0, 255);

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = ColorFromPalette(currentPalette, i + wave1 + wave2 + wave3 + wave4, 255, currentBlending);
  }
}

void setPixel(int pixel, byte red, byte green, byte blue)
{

  // #ifdef ADAFRUIT_NEOPIXEL_H

  //   // NeoPixel

  //   strip.setPixelColor(pixel, strip.Color(red, green, blue));

  // #endif

#ifndef ADAFRUIT_NEOPIXEL_H

  // FastLED

  leds[pixel].r = red;

  leds[pixel].g = green;

  leds[pixel].b = blue;

#endif
}

void fadeLightBy(int pixel, int brightness)
{

#ifndef ADAFRUIT_NEOPIXEL_H

  // FastLED

  leds[pixel].fadeLightBy(brightness);
#endif
}
void DetermineFadeDirection()
{
  if (yoffset > yoffsetMAX)
  {
    fadeDirection2 = 0;
  }
  if (yoffset < 0)
  {
    fadeDirection2 = 1;
  }
}

String processor(const String &var)
{
  if (var == "BRIGHTNESS")
  {
    if (brightness == 0)
    {
      returnText = "Off";
    }
    else if (brightness == 255)
    {
      returnText = "Max";
    }
    else if (brightness > 200)
    {
      returnText = "Bright";
    }
    else if (brightness > 160)
    {
      returnText = "Half";
    }
    else if (brightness > 120)
    {
      returnText = "Third";
    }
    else if (brightness > 80)
    {
      returnText = "Quarter";
    }
    else if (brightness > 40)
    {
      returnText = "Dim";
    }
    else if (brightness > 0)
    {
      returnText = "Moody";
    }

    return returnText;
  }

  if (var == "MODE")
  {

    return returnText;
  }
  return String();
}

void confettiCustom(int saturation, int value, int random)
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy(leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV(gHue + random8(random), saturation, value);
}

void sinelonCustom(int saturation, int value, int speed, int fadeBy)
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy(leds, NUM_LEDS, fadeBy);
  int pos = beatsin16(speed, 0, NUM_LEDS - 1);
  leds[pos] += CHSV(gHue, saturation, value);
}

void u8g2_horizontal_line(uint8_t a)
{
  u8g2.drawHLine(0, a, 128);
}

/***********************************************************
  Simplex Noise Pattern (Rainbow Cloud Generator)
***********************************************************/
void SimplexNoisePatternInterpolated(float spaceinc, float timeinc, float yoffset, float xoffset)
{

  // Simplex noise for whole strip of LEDs.
  // (Well, it's simplex noise for set number of LEDs and cubic interpolation between those nodes.)

  // Calculate simplex noise for LEDs that are nodes:
  // Store raw values from simplex function (-0.347 to 0.347)
  //float xoffset = 0.0;
  float xoffset_holder = xoffset;

  for (int i = 0; i <= LEDs_in_strip; i = i + node_spacing)
  {
    xoffset += spaceinc;
    LED_array_red[i] = SimplexNoise(xoffset, yoffset, 0);
    LED_array_green[i] = SimplexNoise(xoffset, yoffset, 1);
    LED_array_blue[i] = SimplexNoise(xoffset, yoffset, 2);
  }

  xoffset = xoffset_holder;

  // Interpolate values for LEDs between nodes
  for (int i = 0; i < LEDs_in_strip; i++)
  {
    int position_between_nodes = i % node_spacing;
    int last_node, next_node;

    // If at node, skip
    if (position_between_nodes == 0)
    {
      // At node for simplex noise, do nothing but update which nodes we are between
      last_node = i;
      next_node = last_node + node_spacing;
    }
    // Else between two nodes, so identify those nodes
    else
    {
      // And interpolate between the values at those nodes for red, green, and blue
      float t = float(position_between_nodes) / float(node_spacing);
      float t_squaredx3 = 3 * t * t;
      float t_cubedx2 = 2 * t * t * t;
      LED_array_red[i] = LED_array_red[last_node] * (t_cubedx2 - t_squaredx3 + 1.0) + LED_array_red[next_node] * (-t_cubedx2 + t_squaredx3);
      LED_array_green[i] = LED_array_green[last_node] * (t_cubedx2 - t_squaredx3 + 1.0) + LED_array_green[next_node] * (-t_cubedx2 + t_squaredx3);
      LED_array_blue[i] = LED_array_blue[last_node] * (t_cubedx2 - t_squaredx3 + 1.0) + LED_array_blue[next_node] * (-t_cubedx2 + t_squaredx3);
    }
  }

  // Convert values from raw noise to scaled r,g,b and feed to strip
  for (int i = 0; i < LEDs_in_strip; i++)
  {
    int r = LED_array_red[i] * 734 + 16;
    int g = LED_array_green[i] * 734 + 16;
    int b = LED_array_blue[i] * 734 + 16;

    if (r > 255)
    {
      r = 255;
    }
    else if (r < 0)
    {
      r = 0;
    } // Adds no time at all. Conclusion: constrain() sucks.

    if (g > 255)
    {
      g = 255;
    }
    else if (g < 0)
    {
      g = 0;
    }

    if (b > 255)
    {
      b = 255;
    }
    else if (b < 0)
    {
      b = 0;
    }
    //Convert to 24 bit output for WS2811

    leds[i] = CRGB(r, g, b);
  }

  if (yoffset >= 16000)
  {
    yoffset = -26000;
  }

  if (yoffset <= -26000)
  {
    yoffset = 16000;
  }

  if (xoffset >= 16000)
  {
    xoffset = -16000;
  }

  if (xoffset <= -16000)
  {
    xoffset = 16000;
  }
}

/*****************************************************************************/
// Simplex noise code:
// From an original algorythm by Ken Perlin.
// Returns a value in the range of about [-0.347 .. 0.347]
float SimplexNoise(float x, float y, float z)
{
  // Skew input space to relative coordinate in simplex cell
  s = (x + y + z) * onethird;
  i = fastfloor(x + s);
  j = fastfloor(y + s);
  k = fastfloor(z + s);

  // Unskew cell origin back to (x, y , z) space
  s = (i + j + k) * onesixth;
  u = x - i + s;
  v = y - j + s;
  w = z - k + s;
  ;

  A[0] = A[1] = A[2] = 0;

  // For 3D case, the simplex shape is a slightly irregular tetrahedron.
  // Determine which simplex we're in
  int hi = u >= w ? u >= v ? 0 : 1 : v >= w ? 1 : 2;
  int lo = u < w ? u < v ? 0 : 1 : v < w ? 1 : 2;

  return k_fn(hi) + k_fn(3 - hi - lo) + k_fn(lo) + k_fn(0);
}

float k_fn(int a)
{
  s = (A[0] + A[1] + A[2]) * onesixth;
  float x = u - A[0] + s;
  float y = v - A[1] + s;
  float z = w - A[2] + s;
  float t = 0.6f - x * x - y * y - z * z;
  int h = shuffle(i + A[0], j + A[1], k + A[2]);
  A[a]++;
  if (t < 0)
    return 0;
  int b5 = h >> 5 & 1;
  int b4 = h >> 4 & 1;
  int b3 = h >> 3 & 1;
  int b2 = h >> 2 & 1;
  int b = h & 3;
  float p = b == 1 ? x : b == 2 ? y : z;
  float q = b == 1 ? y : b == 2 ? z : x;
  float r = b == 1 ? z : b == 2 ? x : y;
  p = b5 == b3 ? -p : p;
  q = b5 == b4 ? -q : q;
  r = b5 != (b4 ^ b3) ? -r : r;
  t *= t;
  return 8 * t * t * (p + (b == 0 ? q + r : b2 == 0 ? q : r));
}

int shuffle(int i, int j, int k)
{
  return b(i, j, k, 0) + b(j, k, i, 1) + b(k, i, j, 2) + b(i, j, k, 3) + b(j, k, i, 4) + b(k, i, j, 5) + b(i, j, k, 6) + b(j, k, i, 7);
}
int b(int i, int j, int k, int B)
{
  return T[b(i, B) << 2 | b(j, B) << 1 | b(k, B)];
}
int b(int N, int B)
{
  return N >> B & 1;
}

int fastfloor(float n)
{
  return n > 0 ? (int)n : (int)n - 1;
}

/***********************************************************
  hsv2rgb
  Function: Calculate RGB values for colors represented
    in Hue, Saturation, and Value (brightness).
***********************************************************/
void hsv2rgb(float H, float S, float V, int &R, int &G, int &B)
{
  int var_i;
  float var_1, var_2, var_3, var_h, var_r, var_g, var_b;
  if (S == 0) // HSV values = 0 ÷ 1
  {
    R = V * 255;
    G = V * 255;
    B = V * 255;
  }
  else
  {
    var_h = H * 6;
    if (var_h == 6)
      var_h = 0;        // H must be < 1
    var_i = int(var_h); // Or ... var_i = floor( var_h )
    var_1 = V * (1 - S);
    var_2 = V * (1 - S * (var_h - var_i));
    var_3 = V * (1 - S * (1 - (var_h - var_i)));

    if (var_i == 0)
    {
      var_r = V;
      var_g = var_3;
      var_b = var_1;
    }
    else if (var_i == 1)
    {
      var_r = var_2;
      var_g = V;
      var_b = var_1;
    }
    else if (var_i == 2)
    {
      var_r = var_1;
      var_g = V;
      var_b = var_3;
    }
    else if (var_i == 3)
    {
      var_r = var_1;
      var_g = var_2;
      var_b = V;
    }
    else if (var_i == 4)
    {
      var_r = var_3;
      var_g = var_1;
      var_b = V;
    }
    else
    {
      var_r = V;
      var_g = var_1;
      var_b = var_2;
    }

    // RGB results = 0 ÷ 255 (Production)
    R = (var_r)*255;
    G = (var_g)*255;
    B = (var_b)*255;
  }
}

float GetH_BouncingWithLimits(float _speed, float _hHigh, float _hLow)
{
  if (h > _hHigh)
  {
    h = _hHigh;
    fadeDirection = 0;
  }
  if (h < _hLow)
  {
    h = _hLow;
    fadeDirection = 1;
  }

  if (fadeDirection == 1)
  {
    h += _speed; // increment to make faster
  }
  if (fadeDirection == 0)
  {
    h -= _speed; // decrement to make faster
  }

  return h;
}
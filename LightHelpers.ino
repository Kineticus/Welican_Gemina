
void setPixel(int pixel, byte red, byte green, byte blue)
{

  // #ifdef ADAFRUIT_NEOPIXEL_H

  //   // NeoPixel

  //   strip.setPixelColor(pixel, strip.Color(red, green, blue));

  // #endif

#ifndef ADAFRUIT_NEOPIXEL_H

  // FastLED
  patternSettings.leds[pixel] = CRGB(red, green, blue);

  // patternSettings.leds[pixel].setRGB(red, green, blue);

  // patternSettings.leds[pixel].r = red;

  // patternSettings.leds[pixel].g = green;

  // patternSettings.leds[pixel].b = blue;

#endif
}
void setPixel(int pixel, CRGB color)
{

  // #ifdef ADAFRUIT_NEOPIXEL_H

  //   // NeoPixel

  //   strip.setPixelColor(pixel, strip.Color(red, green, blue));

  // #endif

#ifndef ADAFRUIT_NEOPIXEL_H

  // FastLED
  patternSettings.leds[pixel] = CRGB(color);

  // patternSettings.leds[pixel].setRGB(color);

#endif
}

void showStrip()
{
// #ifdef ADAFRUIT_NEOPIXEL_H
//   // NeoPixel
//   strip.show();
// #endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  FastLED.show();
#endif
}

void setAll(byte red, byte green, byte blue)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

void smoothOperator()
{
  //Check for interfade
  if (globalLED.interfade != 0)
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      patternSettings.leds[i] = blend(patternSettings.leds[i], patternSettings.tempLeds[i], globalLED.interfade * globalLED.interfadeSpeed);
    }

    //Only want to interfade for a bit
    globalLED.interfade -= 1;

    if (globalLED.interfade < 1)
    {
      globalLED.interfade = 0;
    }
  }
}

void setSmoothOperator(int fadeTime)
{
  //globalLED.interfadeMax == steps
  //globalLED.interfadeSpeed == change each step
  //globalLED.interfadeMax * globalLED.interfadeSpeed <= 255

  //255 / fadeTime;

  //Set # of Steps
  globalLED.interfadeMax = fadeTime;

  //Set distance of each step
  globalLED.interfadeSpeed = (255 / fadeTime);

  EEPROM.write(52, globalMenu.menu[17]);
  EEPROM.commit();
}

void readSmoothOperator()
{
  //globalLED.interfadeMax == steps
  //globalLED.interfadeSpeed == change each step
  //globalLED.interfadeMax * globalLED.interfadeSpeed <= 255

  //255 / fadeTime;
  globalMenu.menu[17] = EEPROM.read(52);

  if (globalMenu.menu[17] < 1)
  {
    globalMenu.menu[17] = 18;
  }

  if (globalMenu.menu[17] > 50)
  {
    globalMenu.menu[17] = 50;
  }

  //Set # of Steps
  globalLED.interfadeMax = globalMenu.menu[17];

  //Set distance of each step
  globalLED.interfadeSpeed = (255 / globalMenu.menu[17]);

  //Start fading
  globalLED.interfade = globalLED.interfadeMax;
}

//make this an int and calculate variables based on time
void startSmoothOperator()
{
  globalLED.interfade = globalLED.interfadeMax;

  for (int i = 0; i < NUM_LEDS; i++)
  {
    patternSettings.tempLeds[i] = patternSettings.leds[i];
  }
}

void fadeLightBy(int pixel, int brightnes)
{

#ifndef ADAFRUIT_NEOPIXEL_H

  // FastLED

  patternSettings.leds[pixel].fadeLightBy(brightnes);
#endif
}

void fadeToBlack(int ledNo, byte fadeValue)
{
// #ifdef ADAFRUIT_NEOPIXEL_H
//   // NeoPixel
//   uint32_t oldColor;
//   uint8_t r, g, b;
//   int value;

//   oldColor = strip.getPixelColor(ledNo);
//   r = (oldColor & 0x00ff0000UL) >> 16;
//   g = (oldColor & 0x0000ff00UL) >> 8;
//   b = (oldColor & 0x000000ffUL);

//   r = (r <= 10) ? 0 : (int)r - (r * fadeValue / 256);
//   g = (g <= 10) ? 0 : (int)g - (g * fadeValue / 256);
//   b = (b <= 10) ? 0 : (int)b - (b * fadeValue / 256);

//   strip.setPixelColor(ledNo, r, g, b);
// #endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  patternSettings.leds[ledNo].fadeToBlackBy(fadeValue);
#endif
}

void determineFadeDirection()
{
  if (simplexNoise.yoffset > simplexNoise.yoffsetMax)
  {
    globalLED.fadeDirection2 = 0;
  }
  if (simplexNoise.yoffset < 0)
  {
    globalLED.fadeDirection2 = 1;
  }
}

float GetH_BouncingWithLimits(float _speed, float _hHigh, float _hLow)
{
  if (simplexNoise.h > _hHigh)
  {
    simplexNoise.h = _hHigh;
    globalLED.fadeDirection = 0;
  }
  if (simplexNoise.h < _hLow)
  {
    simplexNoise.h = _hLow;
    globalLED.fadeDirection = 1;
  }

  if (globalLED.fadeDirection == 1)
  {
    simplexNoise.h += _speed; // increment to make faster
  }
  if (globalLED.fadeDirection == 0)
  {
    simplexNoise.h -= _speed; // decrement to make faster
  }

  return simplexNoise.h;
}
float GetHTemp_BouncingWithLimits(float _speed, float _hHigh, float _hLow)
{
  if (simplexNoise.hTemp > _hHigh)
  {
    simplexNoise.hTemp = _hHigh;
    globalLED.fadeDirectionHTemp = 0;
  }
  if (simplexNoise.hTemp < _hLow)
  {
    simplexNoise.hTemp = _hLow;
    globalLED.fadeDirectionHTemp = 1;
  }

  if (globalLED.fadeDirectionHTemp == 1)
  {
    simplexNoise.hTemp += _speed; // increment to make faster
  }
  if (globalLED.fadeDirectionHTemp == 0)
  {
    simplexNoise.hTemp -= _speed; // decrement to make faster
  }

  return simplexNoise.hTemp;
}

void SimplexNoisePatternInterpolated(float spaceInc, float timeInc, float yoffset, float xoffset)
{

  // Simplex noise for whole strip of LEDs.
  // (Well, it's simplex noise for set number of LEDs and cubic interpolation between those nodes.)

  // Calculate simplex noise for LEDs that are nodes:
  // Store raw values from simplex function (-0.347 to 0.347)
  //float simplexNoise.xoffset = 0.0;
  float xoffset_holder = simplexNoise.xoffset;

  for (int i = 0; i <= NUM_LEDS; i = i + simplexNoise.nodeSpacing)
  {
    simplexNoise.xoffset += simplexNoise.spaceInc;
    simplexNoise.ledArrayRed[i] = SimplexNoise(simplexNoise.xoffset, simplexNoise.yoffset, 0);
    simplexNoise.ledArrayGreen[i] = SimplexNoise(simplexNoise.xoffset, simplexNoise.yoffset, 1);
    simplexNoise.ledArrayBlue[i] = SimplexNoise(simplexNoise.xoffset, simplexNoise.yoffset, 2);
  }

  simplexNoise.xoffset = xoffset_holder;

  // Interpolate values for LEDs between nodes
  for (int i = 0; i < NUM_LEDS; i++)
  {
    int position_between_nodes = i % simplexNoise.nodeSpacing;
    int last_node, next_node;

    // If at node, skip
    if (position_between_nodes == 0)
    {
      // At node for simplex noise, do nothing but update which nodes we are between
      last_node = i;
      next_node = last_node + simplexNoise.nodeSpacing;
    }
    // Else between two nodes, so identify those nodes
    else
    {
      // And interpolate between the values at those nodes for red, green, and blue
      float t = float(position_between_nodes) / float(simplexNoise.nodeSpacing);
      float t_squaredx3 = 3 * t * t;
      float t_cubedx2 = 2 * t * t * t;
      simplexNoise.ledArrayRed[i] = simplexNoise.ledArrayRed[last_node] * (t_cubedx2 - t_squaredx3 + 1.0) + simplexNoise.ledArrayRed[next_node] * (-t_cubedx2 + t_squaredx3);
      simplexNoise.ledArrayGreen[i] = simplexNoise.ledArrayGreen[last_node] * (t_cubedx2 - t_squaredx3 + 1.0) + simplexNoise.ledArrayGreen[next_node] * (-t_cubedx2 + t_squaredx3);
      simplexNoise.ledArrayBlue[i] = simplexNoise.ledArrayBlue[last_node] * (t_cubedx2 - t_squaredx3 + 1.0) + simplexNoise.ledArrayBlue[next_node] * (-t_cubedx2 + t_squaredx3);
    }
  }

  // Convert values from raw noise to scaled r,g,b and feed to strip
  for (int i = 0; i < NUM_LEDS; i++)
  {
    int r = simplexNoise.ledArrayRed[i] * 734 + 16;
    int g = simplexNoise.ledArrayGreen[i] * 734 + 16;
    int b = simplexNoise.ledArrayBlue[i] * 734 + 16;

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

    patternSettings.leds[i] = CRGB(r, g, b);
  }

  if (simplexNoise.yoffset >= 16000)
  {
    simplexNoise.yoffset = -26000;
  }

  if (simplexNoise.yoffset <= -26000)
  {
    simplexNoise.yoffset = 16000;
  }

  if (simplexNoise.xoffset >= 16000)
  {
    simplexNoise.xoffset = -16000;
  }

  if (simplexNoise.xoffset <= -16000)
  {
    simplexNoise.xoffset = 16000;
  }
}

/*****************************************************************************/
// Simplex noise code:
// From an original algorythm by Ken Perlin.
// Returns a value in the range of about [-0.347 .. 0.347]
float SimplexNoise(float x, float y, float z)
{
  // Skew input space to relative coordinate in simplex cell
  simplexNoise.s = (x + y + z) * onethird;
  simplexNoise.g = fastfloor(x + simplexNoise.s);
  simplexNoise.j = fastfloor(y + simplexNoise.s);
  simplexNoise.k = fastfloor(z + simplexNoise.s);

  // Unskew cell origin back to (x, y , z) space
  simplexNoise.s = (simplexNoise.g + simplexNoise.j + simplexNoise.k) * onesixth;
  simplexNoise.u = x - simplexNoise.g + simplexNoise.s;
  simplexNoise.v = y - simplexNoise.j + simplexNoise.s;
  simplexNoise.w = z - simplexNoise.k + simplexNoise.s;

  simplexNoise.A[0] = simplexNoise.A[1] = simplexNoise.A[2] = 0;

  // For 3D case, the simplex shape is a slightly irregular tetrahedron.
  // Determine which simplex we're in
  int hi = simplexNoise.u >= simplexNoise.w ? simplexNoise.u >= simplexNoise.v ? 0 : 1 : simplexNoise.v >= simplexNoise.w ? 1 : 2;
  int lo = simplexNoise.u < simplexNoise.w ? simplexNoise.u < simplexNoise.v ? 0 : 1 : simplexNoise.v < simplexNoise.w ? 1 : 2;

  return k_fn(hi) + k_fn(3 - hi - lo) + k_fn(lo) + k_fn(0);
}

float k_fn(int a)
{
  simplexNoise.s = (simplexNoise.A[0] + simplexNoise.A[1] + simplexNoise.A[2]) * onesixth;
  float x = simplexNoise.u - simplexNoise.A[0] + simplexNoise.s;
  float y = simplexNoise.v - simplexNoise.A[1] + simplexNoise.s;
  float z = simplexNoise.w - simplexNoise.A[2] + simplexNoise.s;
  float t = 0.6f - x * x - y * y - z * z;
  int h = shuffle(simplexNoise.g + simplexNoise.A[0], simplexNoise.j + simplexNoise.A[1], simplexNoise.k + simplexNoise.A[2]);
  simplexNoise.A[a]++;
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

void confettiCustom(int saturation, int value, int random)
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy(patternSettings.leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  patternSettings.leds[pos] += CHSV(patternSettings.gHue + random8(random), saturation, value);
}

void sinelonCustom(int saturation, int value, int speed, int fadeBy)
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy(patternSettings.leds, NUM_LEDS, fadeBy);
  int pos = beatsin16(speed, 0, NUM_LEDS - 1);
  patternSettings.leds[pos] += CHSV(patternSettings.gHue, saturation, value);
}

void addGlitter(fract8 chanceOfGlitter)
{
  if (random8() < chanceOfGlitter)
  {
    patternSettings.leds[random16(NUM_LEDS)] += CRGB::White;
  }
}

void customColor(int r, int g, int b)
{
  fill_solid(patternSettings.leds, NUM_LEDS, CRGB(r, g, b));
}

void plasma(CRGBPalette16 currentPalette, TBlendType currentBlending)
{ // This is the heart of this program. Sure is short. . . and fast.

  int thisPhase = beatsin8(6, -64, 64); // Setting phase change for a couple of waves.
  int thatPhase = beatsin8(7, -64, 64);

  for (int k = 0; k < NUM_LEDS; k++)
  { // For each of the LED's in the strand, set a brightness based on a wave as follows:

    int colorIndex = cubicwave8((k * 23) + thisPhase) / 2 + cos8((k * 15) + thatPhase) / 2; // Create a wave and add a phase change and add another wave with its own phase change.. Hey, you can even change the frequencies if you wish.
    int thisBright = QSUBA(colorIndex, beatsin8(7, 0, 96));                                 // qsub gives it a bit of 'black' dead space by setting sets a minimum value. If colorIndex < current value of beatsin8(), then bright = 0. Otherwise, bright = colorIndex..

    patternSettings.leds[k] = ColorFromPalette(currentPalette, colorIndex, thisBright, currentBlending); // Let's now add the foreground colour.
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
    patternSettings.leds[i] = ColorFromPalette(currentPalette, i + wave1 + wave2 + wave3 + wave4, 255, currentBlending);
  }
}

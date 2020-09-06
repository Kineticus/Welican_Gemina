void legacy_category(int patternMode)
{
  categoryName = "LEGACY";

  switch (patternMode)
  {
  case 0:
    functionName = "RainbowOneYoffset";
    RainbowOneYoffset();
    break;
  case 1:
    functionName = "RainbowTwoYoffset";
    RainbowTwoYoffset();
    break;
  case 2:
    functionName = "RainbowThreeXoffset";
    RainbowThreeXoffset();
    break;
  case 3:
    functionName = "RainbowFourXoffset";
    RainbowFourXoffset();
    break;
  case 4:
    functionName = "RainbowBigXoffset";
    RainbowBigXoffset();
    break;
  case 5:
    functionName = "RainbowBigYoffset";
    RainbowBigYoffset();
    break;
  case 6:
    functionName = "RbowY 0.000025, 0.3";
    RainbowYoffset(0.000025, 0.3, true);
    break;
  case 7:
    functionName = "RbowY 0.00025, 0.5";
    RainbowYoffset(0.00025, 0.5, true);
    break;
  case 8:
    functionName = "RbowY 0.0025, 0.7";
    RainbowYoffset(0.0025, 0.7, true);
    break;
  case 9:
    functionName = "RbowX 0.000025, 0.1";
    RainbowXoffset(0.000025, 0.1, true);
    break;
  case 10:
    functionName = "RbowX 0.00025, 0.1";
    RainbowXoffset(0.00025, 0.1, true);
    break;
  case 11:
    functionName = "RbowX 0.0025, 0.1";
    RainbowXoffset(0.0025, 0.1, true);
    break;
  case 12:
    functionName = "SteadyRGB 2";
    SteadyRGB(2);
    break;
  case 13:
    functionName = "SteadyRGB 4";
    SteadyRGB(4);
    break;
  case 14:
    functionName = "SteadyAltClrs RG";
    SteadyAlternatingColors(CRGB::Red, CRGB::Green);
    break;
  case 15:
    functionName = "SteadyAltClrs BW";
    SteadyAlternatingColors(CRGB::Blue, CRGB::White);
    break;
  case 16:
    functionName = "SteadyAltClrs PB";
    SteadyAlternatingColors(CRGB::Purple, CRGB::Blue);
    break;
  case 17:
    functionName = "SteadyAltClrs YP";
    SteadyAlternatingColors(CRGB::Yellow, CRGB::Purple);
    break;
  case 18:
    functionName = "SteadyAltClrs RW";
    SteadyAlternatingColors(CRGB::Red, CRGB::White);
    break;
  case 19:
    functionName = "SteadyAltClrs OB";
    SteadyAlternatingColors(CRGB::Orange, CRGB::Blue);
    break;
  case 20:
    functionName = "SteadyAltClrs OP";
    SteadyAlternatingColors(CRGB::Orange, CRGB::Purple);
    break;
  case 21:
    functionName = "MovingHue 85.002";
    MovingHue(85, .002);
    break;
  case 22:
    functionName = "MovingHue 42.008";
    MovingHue(42, .008);
    break;
  case 23:
    functionName = "MovingHue 128.016";
    MovingHue(128, .025);
    break;
  case 24:
    functionName = "MovingHue 85.3";
    MovingHue(85, .3);
    break;
  case 25:
    functionName = "MovingHue 42.5";
    MovingHue(42, .5);
    break;
  case 26:
    functionName = "MovingHue 128.7";
    MovingHue(128, .7);
    break;
  case 27:
    functionName = "MovingHue 85.3.9";
    MovingHue(85, .3, .9);
    break;
  case 28:
    functionName = "MovingHue 42.5.4";
    MovingHue(42, .5, .4);
    break;
  case 29:
    functionName = "MovingHue 128.7.1";
    MovingHue(128, .7, .1);
    break;
  case 30:
    functionName = "MovingHue 128.7 3";
    MovingHue(128, .7, 3);
    break;
  }
}

void RainbowYoffset(float speed, float spacing, bool useFadeDirection)
{
  timeinc = (speed * currSpeed);
  spaceinc = spacing;

  if (useFadeDirection)
  {
    if (fadeDirection2 == 1)
    {
      yoffset += timeinc;
    }
    if (fadeDirection2 == 0)
    {
      yoffset -= timeinc;
    }
  }
  else
  {
    yoffset += timeinc;
  }

  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
}
void RainbowXoffset(float speed, float spacing, bool useFadeDirection)
{
  timeinc = speed;
  spaceinc = spacing;

  if (useFadeDirection)
  {
    if (fadeDirection2 == 1)
    {
      xoffset += timeinc;
    }
    if (fadeDirection2 == 0)
    {
      xoffset -= timeinc;
    }
  }
  else
  {
    xoffset += timeinc;
  }

  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
}

void RainbowOneYoffset()
{
  functionName = "RainbowOneYoffset";
  spaceinc = 0.03;
  timeinc = (0.000025 * currSpeed);
  yoffset += timeinc;
  //xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
}
void RainbowTwoYoffset()
{
  functionName = "RainbowTwoYoffset";
  spaceinc = 0.07;
  timeinc = (0.000025 * currSpeed);
  yoffset += timeinc;
  //xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
}
void RainbowThreeXoffset()
{
  functionName = "RainbowThreeXoffset";
  spaceinc = 0.07;
  timeinc = (0.000025 * currSpeed);
  //yoffset += timeinc;
  xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
}
void RainbowFourXoffset()
{
  functionName = "RainbowFourXoffset";
  spaceinc = 0.03;
  timeinc = (0.000025 * currSpeed);
  //yoffset += timeinc;
  xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
}
void RainbowBigXoffset()
{
  functionName = "RainbowBigXoffset";
  spaceinc = 0.12;
  timeinc = (0.000025 * currSpeed);
  //yoffset += timeinc;
  xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
}
void RainbowBigYoffset()
{
  functionName = "RainbowBigYoffset";
  spaceinc = 0.12;
  timeinc = (0.000025 * currSpeed);
  yoffset += timeinc;
  //xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
}

void MovingHue(uint8_t hStart, float hMod)
{
  h = hStart;

  float hTemp = h;

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {

    hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red, green, blue);
    setPixel(i, red, green, blue);

    // slowly increment 'h' by small increments to make color flow
    hTemp += hMod; // decrease to space out the colors

    if (hTemp > 1)
    {
      hTemp -= 1;
    }
    if (hTemp < 0)
    {
      hTemp += 1;
    }
  }
}
void MovingHue(uint8_t hStart, float hMod, float spacing)
{
  h = hStart;

  float hTemp = h + spacing;

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {

    hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red, green, blue);
    setPixel(i, red, green, blue);

    // slowly increment 'h' by small increments to make color flow
    hTemp += hMod; // decrease to space out the colors

    if (hTemp > 1)
    {
      hTemp -= 1;
    }
    if (hTemp < 0)
    {
      hTemp += 1;
    }
  }
}

void SteadyRGB(int ledSpacing)
{
  for (uint16_t i = 0; i < NUM_LEDS; i = i + 3)
  {
    setPixel(i, 255, 0, 0);
    setPixel(i + 1, 0, 255, 0);
    setPixel(i + 2, 0, 0, 255);
    // setPixel(i + 1, 0, 255, 0);
    // setPixel(i + 2, 0, 0, 255);
    // setPixel(i + 3, 0, 0, 255);
    // setPixel(i + 4, 0, 0, 255);
    // setPixel(i + 5, 0, 0, 255);

    // setPixel(i + 6, 255, 255, 255);
    // setPixel(i + 7, 255, 255, 255);
    // setPixel(i + 8, 255, 255, 255);
    // setPixel(i + 9, 255, 255, 255);
    // setPixel(i + 10, 255, 255, 255);
    // setPixel(i + 11, 255, 255, 255);

    if (useFade == true)
    {
      fadeLightBy(i, brightness);
      fadeLightBy(i + 1, brightness);
      fadeLightBy(i + 2, brightness);
      // fadeLightBy(i + 3, brightness);
      // fadeLightBy(i + 4, brightness);
      // fadeLightBy(i + 5, brightness);

      // fadeLightBy(i + 6, brightness);
      // fadeLightBy(i + 7, brightness);
      // fadeLightBy(i + 8, brightness);
      // fadeLightBy(i + 9, brightness);
      // fadeLightBy(i + 10, brightness);
      // fadeLightBy(i + 11, brightness);
    }
  }
}
void SteadyAlternatingColors(CRGB color1, CRGB color2)
{
  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    if ((i % 2) == 0)
    {
      setPixel(i, color1);
    }
    else
    {
      setPixel(i, color2);
    }
  }
}
void legacy_category(int patternMode)
{
  globalStrings.categoryName = "LEGACY";

  switch (patternMode)
  {
  case 0:
    globalStrings.functionName = "RainbowOneYoffset";
    RainbowOneYoffset();
    break;
  case 1:
    globalStrings.functionName = "RainbowTwoYoffset";
    RainbowTwoYoffset();
    break;
  case 2:
    globalStrings.functionName = "RainbowThreeXoffset";
    RainbowThreeXoffset();
    break;
  case 3:
    globalStrings.functionName = "RainbowFourXoffset";
    RainbowFourXoffset();
    break;
  case 4:
    globalStrings.functionName = "RainbowBigXoffset";
    RainbowBigXoffset();
    break;
  case 5:
    globalStrings.functionName = "RainbowBigYoffset";
    RainbowBigYoffset();
    break;
  case 6:
    globalStrings.functionName = "RbowY 0.000025, 0.3";
    RainbowYoffset(0.000025, 0.3, true);
    break;
  case 7:
    globalStrings.functionName = "RbowY 0.00025, 0.5";
    RainbowYoffset(0.00025, 0.5, true);
    break;
  case 8:
    globalStrings.functionName = "RbowY 0.0025, 0.7";
    RainbowYoffset(0.0025, 0.7, true);
    break;
  case 9:
    globalStrings.functionName = "RbowX 0.000025, 0.1";
    RainbowXoffset(0.000025, 0.1, true);
    break;
  case 10:
    globalStrings.functionName = "RbowX 0.00025, 0.1";
    RainbowXoffset(0.00025, 0.1, true);
    break;
  case 11:
    globalStrings.functionName = "RbowX 0.0025, 0.1";
    RainbowXoffset(0.0025, 0.1, true);
    break;
  case 12:
    globalStrings.functionName = "SteadyRGB 2";
    SteadyRGB(2);
    break;
  case 13:
    globalStrings.functionName = "SteadyRGB 3";
    SteadyRGB(3);
    break;
  case 14:
    globalStrings.functionName = "SteadyAltClrs RG";
    SteadyAlternatingColors(CRGB::Red, CRGB::Green);
    break;
  case 15:
    globalStrings.functionName = "SteadyAltClrs BW";
    SteadyAlternatingColors(CRGB::Blue, CRGB::White);
    break;
  case 16:
    globalStrings.functionName = "SteadyAltClrs PB";
    SteadyAlternatingColors(CRGB::Purple, CRGB::Blue);
    break;
  case 17:
    globalStrings.functionName = "SteadyAltClrs YP";
    SteadyAlternatingColors(CRGB::Yellow, CRGB::Purple);
    break;
  case 18:
    globalStrings.functionName = "SteadyAltClrs RW";
    SteadyAlternatingColors(CRGB::Red, CRGB::White);
    break;
  case 19:
    globalStrings.functionName = "SteadyAltClrs OB";
    SteadyAlternatingColors(CRGB::Orange, CRGB::Blue);
    break;
  case 20:
    globalStrings.functionName = "SteadyAltClrs OP";
    SteadyAlternatingColors(CRGB::Orange, CRGB::Purple);
    break;
  case 21:
    globalStrings.functionName = "MovingHue 85.002";
    MovingHue(85, .002);
    break;
  case 22:
    globalStrings.functionName = "MovingHue 42.008";
    MovingHue(42, .008);
    break;
  case 23:
    globalStrings.functionName = "MovingHue 128.016";
    MovingHue(128, .025);
    break;
  case 24:
    globalStrings.functionName = "MovingHue 85.3";
    MovingHue(85, .3);
    break;
  case 25:
    globalStrings.functionName = "MovingHue 42.5";
    MovingHue(42, .5);
    break;
  case 26:
    globalStrings.functionName = "MovingHue 128.7";
    MovingHue(128, .7);
    break;
  case 27:
    globalStrings.functionName = "MovingHue 85.3.9";
    MovingHue(85, .3, .9);
    break;
  case 28:
    globalStrings.functionName = "MovingHue 42.5.4";
    MovingHue(42, .5, .4);
    break;
  case 29:
    globalStrings.functionName = "MovingHue 128.7.1";
    MovingHue(128, .7, .1);
    break;
  case 30:
    globalStrings.functionName = "MovingHue 128.7 3";
    MovingHue(128, .7, 3);
    break;
  case 31:
    globalStrings.functionName = "DLCLRflo2 .00009.9";
    DualColorFlowTwo(.00009, .9);
    break;
  case 32:
    globalStrings.functionName = "DLCLRflo2 .0009.9";
    DualColorFlowTwo(.0009, .9);
    break;
  case 33:
    globalStrings.functionName = "DLCLRflo2 .0009.4";
    DualColorFlowTwo(.0009, .4);
    break;
  case 34:
    globalStrings.functionName = "DLCLRflo2 .00009.1";
    DualColorFlowTwo(.00009, .1);
    break;
  case 35:
    globalStrings.functionName = "DLCLRflo2 .0007.5";
    DualColorFlowTwo(.0007, .5);
    break;
  case 36:
    globalStrings.functionName = "DLCLRflo2 .0075.7";
    DualColorFlowTwo(.00075, .7);
    break;
  case 37:
    globalStrings.functionName = "DLCLRflo2 .0001.3";
    DualColorFlowTwo(.0001, .3);
    break;
  case 38:
    globalStrings.functionName = "DLCLRflo2 .0009.6";
    DualColorFlowTwo(.0009, .6);
    break;
  case 39:
    globalStrings.functionName = "DLCLRflo2 .0007.1";
    DualColorFlowTwo(.0007, .1);
    break;
  case 40:
    globalStrings.functionName = "DLCLRflo2 .0005.9";
    DualColorFlowTwo(.0005, .9);
    break;
  case 41:
    globalStrings.functionName = "DLCLRflo 1";
    DualColorFlow(.85, .58, .46, .09, .00009, .9);
    break;
  case 42:
    globalStrings.functionName = "DLCLRflo 2";
    DualColorFlow(.45, .20, .24, .03, .0009, .5);
    break;
  case 43:
    globalStrings.functionName = "DLCLRflo 3";
    DualColorFlow(.7, .3, .85, .6, .0005, .1);
    break;
  case 44:
    globalStrings.functionName = "DLCLRflo 4";
    DualColorFlow(.9, .5, .85, .6, .0007, .1);
    break;
  case 45:
    globalStrings.functionName = "DLCLRflo 5";
    DualColorFlow(.15, .05, .4, .059, .0029, .1);
    break;
  case 46:
    globalStrings.functionName = "DLCLRflo 6";
    DualColorFlow(.9, .5, .85, .6, .0007, .7);
    break;
  case 47:
    globalStrings.functionName = "DLCLRflo 7";
    DualColorFlow(.9, .5, .4, .1, .00069, .1);
    break;
  case 48:
    globalStrings.functionName = "DLCLRflo 8";
    DualColorFlow(.9, .6, .85, .6, .000420, .1);
    break;
  case 49:
    globalStrings.functionName = "DLCLRflo 9";
    DualColorFlow(.8, .5, .5, .2, .00042, .5);
    break;
  case 50:
    globalStrings.functionName = "DLCLRflo 10";
    DualColorFlow(.8, .5, .5, .2, .00042, .1);
    break;
  case 51:
    globalStrings.functionName = "DLCLRfloB 1";
    DualColorFlowBounce(.85, .58, .00009, .1, 2);
    break;
  case 52:
    globalStrings.functionName = "DLCLRfloB 2";
    DualColorFlowBounce(.17, .02, .00009, .1, 2);
    break;
  case 53:
    globalStrings.functionName = "DLCLRfloB 3";
    DualColorFlowBounce(.9, .7, .00042, .1, 2);
    break;
  case 54:
    globalStrings.functionName = "DLCLRfloB 4";
    DualColorFlowBounce(.3, .1, .00042, .1, 2);
    break;
  case 55:
    globalStrings.functionName = "DLCLRfloB 5";
    DualColorFlowBounce(.7, .4, .00069, .5, 2);
    break;
  case 56:
    globalStrings.functionName = "DLCLRfloB 6";
    DualColorFlowBounce(.5, .2, .00009, .7, 2);
    break;
  case 57:
    globalStrings.functionName = "DLCLRfloB 7";
    DualColorFlowBounce(.42, .1, .0009, .1, 4);
    break;
  case 58:
    globalStrings.functionName = "DLCLRfloB 8";
    DualColorFlowBounce(.85, .24, .00009, .5, 4);
    break;
  case 59:
    globalStrings.functionName = "DLCLRfloB 9";
    DualColorFlowBounce(.55, .21, .0001, .1, 6);
    break;
  case 60:
    globalStrings.functionName = "DLCLRfloB 10";
    DualColorFlowBounce(.84, .42, .0007, .5, 6);
    break;
  case 61:
    globalStrings.functionName = "LGFloB 1";
    LargeGroupColorFlowBounce(.85, .58, .00009, .1, 2);
    break;
  case 62:
    globalStrings.functionName = "LGFloB 2";
    LargeGroupColorFlowBounce(.17, .02, .00009, .1, 2);
    break;
  case 63:
    globalStrings.functionName = "LGFloB 3";
    LargeGroupColorFlowBounce(.9, .7, .00042, .1, 2);
    break;
  case 64:
    globalStrings.functionName = "LGFloB 4";
    LargeGroupColorFlowBounce(.3, .1, .00042, .1, 4);
    break;
  case 65:
    globalStrings.functionName = "LGFloB 5";
    LargeGroupColorFlowBounce(.7, .4, .00069, .5, 6);
    break;
  case 66:
    globalStrings.functionName = "RainbowFlow 1";
    RainbowFlow(.98, .01, .00025, .01);
    break;
  case 67:
    globalStrings.functionName = "RainbowFlow 2";
    RainbowFlow(.98, .01, .00007, .002);
    break;
  case 68:
    globalStrings.functionName = "RainbowFlow 3";
    RainbowFlow(.98, .01, .00025, .1);
    break;
  case 69:
    globalStrings.functionName = "RainbowFlow 4";
    RainbowFlow(.98, .01, .00042, .25);
    break;
  case 70:
    globalStrings.functionName = "RainbowNoFlow 1";
    RainbowNoFlow(.042);
    break;
  case 71:
    globalStrings.functionName = "RainbowFlowSlow 1";
    RainbowFlowSlow(.0005, .0045);
    break;
  case 72:
    globalStrings.functionName = "RainbowFlowSlow 2";
    RainbowFlowSlow(.0005, .007);
    break;
  case 73:
    globalStrings.functionName = "RainbowFlowSlow 3";
    RainbowFlowSlow(.0001, .0045);
    break;
  case 74:
    globalStrings.functionName = "RainbowHsv 1";
    RainbowHsv(.00009, .98, .75);
    break;
  case 75:
    globalStrings.functionName = "RainbowHsv 2";
    RainbowHsv(.00009, .98, .55);
    break;
  case 76:
    globalStrings.functionName = "RainbowHsv 3";
    RainbowHsv(.000009, .75, .55);
    break;
  case 77:
    globalStrings.functionName = "RainbowHsv 3";
    RainbowHsv(.000009, .98, .01);
    break;
  case 78:
    globalStrings.functionName = "RainbowHsv 4";
    RainbowHsv(.0001, .98, .01);
    break;
  case 79:
    globalStrings.functionName = "RainbowHsv 5";
    RainbowHsv(.00042, .98, .01);
    break;
  case 80:
    globalStrings.functionName = "RainbowHsv 6";
    RainbowHsv(.00001, .55, .25);
    break;
  }
}

void LargeGroupColorFlowBounce(float hHigh, float hLow, float speed, float colorSpacing, int ledSpacing)
{
  simplexNoise.h = GetH_BouncingWithLimits(speed, hHigh, hLow);

  float hTemp = simplexNoise.h;
  hTemp = simplexNoise.h + colorSpacing; // space between colors
  if (hTemp > .93)
  {
    hTemp -= 1;
  }
  if (hTemp < 0)
  {
    hTemp += 1;
  }

  hsv2rgb(float(simplexNoise.h), 1, (float(brightness.current) / 255.0), globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);
  hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), globalHSV2RGB.red2, globalHSV2RGB.green2, globalHSV2RGB.blue2);

  for (uint16_t i = 0; i < NUM_LEDS; i = i + ledSpacing)
  {
    switch (ledSpacing)
    {
    default:
      setPixel(i, globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);
      setPixel(i + 1, globalHSV2RGB.red2, globalHSV2RGB.green2, globalHSV2RGB.blue2);
      break;
    }
  }
}
void DualColorFlow(float hHigh, float hLow, float hHigh2, float hLow2, float hSpeed, float spacing)
{
  if (simplexNoise.h > hHigh)
  {
    simplexNoise.h = hHigh;
    globalLED.fadeDirection = 0;
  }
  if (simplexNoise.h < hLow)
  {
    simplexNoise.h = hLow;
    globalLED.fadeDirection = 1;
  }

  if (globalLED.fadeDirection == 1)
  {
    simplexNoise.h += hSpeed; // increment to make faster
  }
  if (globalLED.fadeDirection == 0)
  {
    simplexNoise.h -= hSpeed; // decrement to make faster
  }

  float hTemp = simplexNoise.h;

  hTemp = simplexNoise.h - spacing; // space between colors

  hsv2rgb(float(simplexNoise.h), 1, (float(brightness.current) / 255.0), globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);

  hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), globalHSV2RGB.red2, globalHSV2RGB.green2, globalHSV2RGB.blue2);

  for (uint16_t i = 0; i < NUM_LEDS; i = i + 2)
  {
    setPixel(i, globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);
    setPixel(i + 1, globalHSV2RGB.red2, globalHSV2RGB.green2, globalHSV2RGB.blue2);
  }
}
void DualColorFlowTwo(float hStart, float spacing)
{
  simplexNoise.h += hStart; // increment to make faster
  if (simplexNoise.h > 1)
  {
    simplexNoise.h -= 1;
  }
  if (simplexNoise.h < 0)
  {
    simplexNoise.h += 1;
  }

  float hTemp = simplexNoise.h;

  hTemp = simplexNoise.h + spacing; // space between colors

  if (hTemp > 1)
  {
    hTemp -= 1;
  }
  if (hTemp < 0)
  {
    hTemp += 1;
  }

  hsv2rgb(float(simplexNoise.h), 1, (float(brightness.current) / 255.0), globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);

  hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), globalHSV2RGB.red2, globalHSV2RGB.green2, globalHSV2RGB.blue2);

  for (uint16_t i = 0; i < NUM_LEDS; i = i + 2)
  {
    setPixel(i, globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);
    setPixel(i + 1, globalHSV2RGB.red2, globalHSV2RGB.green2, globalHSV2RGB.blue2);
  }
}
void DualColorFlowBounce(float hHigh, float hLow, float speed, float colorSpacing, int ledSpacing)
{
  simplexNoise.h = GetH_BouncingWithLimits(speed, hHigh, hLow);

  float hTemp = simplexNoise.h;
  hTemp = simplexNoise.h - colorSpacing; // space between colors
  if (hTemp > 1)
  {
    hTemp -= 1;
  }
  if (hTemp < 0)
  {
    hTemp += 1;
  }

  hsv2rgb(float(simplexNoise.h), 1, (float(brightness.current) / 255.0), globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);
  hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), globalHSV2RGB.red2, globalHSV2RGB.green2, globalHSV2RGB.blue2);

  for (uint16_t i = 0; i < NUM_LEDS; i = i + ledSpacing)
  {
    switch (ledSpacing)
    {
    default:
      setPixel(i, globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);
      setPixel(i + 1, globalHSV2RGB.red2, globalHSV2RGB.green2, globalHSV2RGB.blue2);
      break;
    }
  }
}

void RainbowNoFlow(float colorSpacing)
{
  simplexNoise.h = 0;

  float hTemp = simplexNoise.h;

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);
    setPixel(i, globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);

    // slowly increment 'h' by small increments to make color flow
    hTemp += colorSpacing; // decrease to space out the colors

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
void RainbowFlow(float hHigh, float hLow, float speed, float colorSpacing)
{
  // increment 'h' to make transitions faster
  simplexNoise.h = GetH_BouncingWithLimits(speed, hHigh, hLow);

  float hTemp = simplexNoise.h;

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);
    setPixel(i, globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);

    // slowly increment 'h' by small increments to make color flow
    hTemp += colorSpacing; // decrease to space out the colors

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
void RainbowFlowSlow(float hSpeed, float colorSpacing)
{
  simplexNoise.h += hSpeed; // increment to make faster
  if (simplexNoise.h > 1)
  {
    simplexNoise.h -= 1;
  }
  if (simplexNoise.h < 0)
  {
    simplexNoise.h += 1;
  }

  float hTemp = simplexNoise.h;

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);
    setPixel(i, globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);

    // slowly increment 'h' by small increments to make color flow
    hTemp += colorSpacing; // decrease to space out the colors

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

void RainbowYoffset(float speed, float spacing, bool useFadeDirection)
{
  simplexNoise.timeInc = (speed * globals.currentSpeed);
  simplexNoise.spaceInc = spacing;

  if (useFadeDirection)
  {
    if (globalLED.fadeDirection2 == 1)
    {
      simplexNoise.yoffset += simplexNoise.timeInc;
    }
    if (globalLED.fadeDirection2 == 0)
    {
      simplexNoise.yoffset -= simplexNoise.timeInc;
    }
  }
  else
  {
    simplexNoise.yoffset += simplexNoise.timeInc;
  }

  SimplexNoisePatternInterpolated(simplexNoise.spaceInc, simplexNoise.timeInc, simplexNoise.yoffset, simplexNoise.xoffset);
}
void RainbowXoffset(float speed, float spacing, bool useFadeDirection)
{
  simplexNoise.timeInc = speed;
  simplexNoise.spaceInc = spacing;

  if (useFadeDirection)
  {
    if (globalLED.fadeDirection2 == 1)
    {
      simplexNoise.xoffset += simplexNoise.timeInc;
    }
    if (globalLED.fadeDirection2 == 0)
    {
      simplexNoise.xoffset -= simplexNoise.timeInc;
    }
  }
  else
  {
    simplexNoise.xoffset += simplexNoise.timeInc;
  }

  SimplexNoisePatternInterpolated(simplexNoise.spaceInc, simplexNoise.timeInc, simplexNoise.yoffset, simplexNoise.xoffset);
}

void RainbowHsv(float hHigh, float hLow, float speed)
{
  simplexNoise.h = GetH_BouncingWithLimits(speed, hHigh, hLow);

  hsv2rgb(float(simplexNoise.h), 1, (float(brightness.current) / 255.0), globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    setPixel(i, globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);
  }
}

void RainbowOneYoffset()
{
  globalStrings.functionName = "RainbowOneYoffset";
  simplexNoise.spaceInc = 0.03;
  simplexNoise.timeInc = (0.000025 * globals.currentSpeed);
  simplexNoise.yoffset += simplexNoise.timeInc;
  //simplexNoise.xoffset += simplexNoise.timeInc;
  SimplexNoisePatternInterpolated(simplexNoise.spaceInc, simplexNoise.timeInc, simplexNoise.yoffset, simplexNoise.xoffset);
}
void RainbowTwoYoffset()
{
  globalStrings.functionName = "RainbowTwoYoffset";
  simplexNoise.spaceInc = 0.07;
  simplexNoise.timeInc = (0.000025 * globals.currentSpeed);
  simplexNoise.yoffset += simplexNoise.timeInc;
  //simplexNoise.xoffset += simplexNoise.timeInc;
  SimplexNoisePatternInterpolated(simplexNoise.spaceInc, simplexNoise.timeInc, simplexNoise.yoffset, simplexNoise.xoffset);
}
void RainbowThreeXoffset()
{
  globalStrings.functionName = "RainbowThreeXoffset";
  simplexNoise.spaceInc = 0.07;
  simplexNoise.timeInc = (0.000025 * globals.currentSpeed);
  //simplexNoise.yoffset += simplexNoise.timeInc;
  simplexNoise.xoffset += simplexNoise.timeInc;
  SimplexNoisePatternInterpolated(simplexNoise.spaceInc, simplexNoise.timeInc, simplexNoise.yoffset, simplexNoise.xoffset);
}
void RainbowFourXoffset()
{
  globalStrings.functionName = "RainbowFourXoffset";
  simplexNoise.spaceInc = 0.03;
  simplexNoise.timeInc = (0.000025 * globals.currentSpeed);
  //simplexNoise.yoffset += simplexNoise.timeInc;
  simplexNoise.xoffset += simplexNoise.timeInc;
  SimplexNoisePatternInterpolated(simplexNoise.spaceInc, simplexNoise.timeInc, simplexNoise.yoffset, simplexNoise.xoffset);
}
void RainbowBigXoffset()
{
  globalStrings.functionName = "RainbowBigXoffset";
  simplexNoise.spaceInc = 0.12;
  simplexNoise.timeInc = (0.000025 * globals.currentSpeed);
  //simplexNoise.yoffset += simplexNoise.timeInc;
  simplexNoise.xoffset += simplexNoise.timeInc;
  SimplexNoisePatternInterpolated(simplexNoise.spaceInc, simplexNoise.timeInc, simplexNoise.yoffset, simplexNoise.xoffset);
}
void RainbowBigYoffset()
{
  globalStrings.functionName = "RainbowBigYoffset";
  simplexNoise.spaceInc = 0.12;
  simplexNoise.timeInc = (0.000025 * globals.currentSpeed);
  simplexNoise.yoffset += simplexNoise.timeInc;
  //simplexNoise.xoffset += simplexNoise.timeInc;
  SimplexNoisePatternInterpolated(simplexNoise.spaceInc, simplexNoise.timeInc, simplexNoise.yoffset, simplexNoise.xoffset);
}

void Glowing(CRGB color1, CRGB color2)
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

void MovingHue(uint8_t hStart, float hMod)
{
  simplexNoise.h = hStart;

  float hTemp = simplexNoise.h;

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {

    hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);
    setPixel(i, globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);

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
  simplexNoise.h = hStart;

  float hTemp = simplexNoise.h + spacing;

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {

    hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);
    setPixel(i, globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);

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
  for (int i = 0; i < NUM_LEDS; i = i + ledSpacing)
  {
    switch (ledSpacing)
    {
    case 3:
      setPixel(i, 255, 0, 0);
      setPixel(i + 1, 0, 255, 0);
      setPixel(i + 2, 0, 0, 255);
      break;
    default:
      setPixel(i, globalHSV2RGB.red, globalHSV2RGB.green, globalHSV2RGB.blue);
      setPixel(i + 1, globalHSV2RGB.red2, globalHSV2RGB.green2, globalHSV2RGB.blue2);
      break;
    }
    if (brightness.useFade == true)
    {
      fadeLightBy(i, brightness.current);
      fadeLightBy(i + 1, brightness.current);
      fadeLightBy(i + 2, brightness.current);
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
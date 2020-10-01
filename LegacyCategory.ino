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
  h = GetH_BouncingWithLimits(speed, hHigh, hLow);

  float hTemp = h;
  hTemp = h + colorSpacing; // space between colors
  if (hTemp > .93)
  {
    hTemp -= 1;
  }
  if (hTemp < 0)
  {
    hTemp += 1;
  }

  hsv2rgb(float(h), 1, (float(brightness.current) / 255.0), red, green, blue);
  hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), red2, green2, blue2);

  for (uint16_t i = 0; i < NUM_LEDS; i = i + ledSpacing)
  {
    switch (ledSpacing)
    {
    // case 6:
    //   setPixel(i, red, green, blue);
    //   setPixel(i + 1, red2, green2, blue2);
    //   break;
    // case 4:
    //   setPixel(i, red, green, blue);
    //   setPixel(i + 1, red2, green2, blue2);
    //   break;
    default:
      setPixel(i, red, green, blue);
      setPixel(i + 1, red2, green2, blue2);
      break;
    }
  }
}
void DualColorFlow(float hHigh, float hLow, float hHigh2, float hLow2, float hSpeed, float spacing)
{
  if (h > hHigh)
  {
    h = hHigh;
    globalLED.fadeDirection = 0;
  }
  if (h < hLow)
  {
    h = hLow;
    globalLED.fadeDirection = 1;
  }

  if (globalLED.fadeDirection == 1)
  {
    h += hSpeed; // increment to make faster
  }
  if (globalLED.fadeDirection == 0)
  {
    h -= hSpeed; // decrement to make faster
  }

  float hTemp = h;

  hTemp = h - spacing; // space between colors

  hsv2rgb(float(h), 1, (float(brightness.current) / 255.0), red, green, blue);

  hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), red2, green2, blue2);

  for (uint16_t i = 0; i < NUM_LEDS; i = i + 2)
  {
    setPixel(i, red, green, blue);
    setPixel(i + 1, red2, green2, blue2);
  }
}
void DualColorFlowTwo(float hStart, float spacing)
{
  h += hStart; // increment to make faster
  if (h > 1)
  {
    h -= 1;
  }
  if (h < 0)
  {
    h += 1;
  }

  float hTemp = h;

  hTemp = h + spacing; // space between colors

  if (hTemp > 1)
  {
    hTemp -= 1;
  }
  if (hTemp < 0)
  {
    hTemp += 1;
  }

  hsv2rgb(float(h), 1, (float(brightness.current) / 255.0), red, green, blue);

  hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), red2, green2, blue2);

  for (uint16_t i = 0; i < NUM_LEDS; i = i + 2)
  {
    setPixel(i, red, green, blue);
    setPixel(i + 1, red2, green2, blue2);
  }
}
void DualColorFlowBounce(float hHigh, float hLow, float speed, float colorSpacing, int ledSpacing)
{
  h = GetH_BouncingWithLimits(speed, hHigh, hLow);

  float hTemp = h;
  hTemp = h - colorSpacing; // space between colors
  if (hTemp > 1)
  {
    hTemp -= 1;
  }
  if (hTemp < 0)
  {
    hTemp += 1;
  }

  hsv2rgb(float(h), 1, (float(brightness.current) / 255.0), red, green, blue);
  hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), red2, green2, blue2);

  for (uint16_t i = 0; i < NUM_LEDS; i = i + ledSpacing)
  {
    switch (ledSpacing)
    {
    // case 6:
    //   setPixel(i, CRGB(red, green, blue));
    //   setPixel(i + 1, CRGB(red, green, blue));
    //   setPixel(i + 2, CRGB(red, green, blue));
    //   setPixel(i + 3, CRGB(red2, green2, blue2));
    //   setPixel(i + 4, CRGB(red2, green2, blue2));
    //   setPixel(i + 5, CRGB(red2, green2, blue2));
    //   break;
    // case 4:
    //   setPixel(i, CRGB(red, green, blue));
    //   setPixel(i + 1, CRGB(red, green, blue));
    //   setPixel(i + 2, CRGB(red2, green2, blue2));
    //   setPixel(i + 3, CRGB(red2, green2, blue2));
    //   break;
    default:
      setPixel(i, red, green, blue);
      setPixel(i + 1, red2, green2, blue2);
      break;
    }
  }
}

void RainbowNoFlow(float colorSpacing)
{
  h = 0;

  float hTemp = h;

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), red, green, blue);
    setPixel(i, red, green, blue);

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
  h = GetH_BouncingWithLimits(speed, hHigh, hLow);

  float hTemp = h;

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), red, green, blue);
    setPixel(i, red, green, blue);

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
  h += hSpeed; // increment to make faster
  if (h > 1)
  {
    h -= 1;
  }
  if (h < 0)
  {
    h += 1;
  }

  float hTemp = h;

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), red, green, blue);
    setPixel(i, red, green, blue);

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
  timeinc = (speed * globals.currentSpeed);
  spaceinc = spacing;

  if (useFadeDirection)
  {
    if (globalLED.fadeDirection2 == 1)
    {
      yoffset += timeinc;
    }
    if (globalLED.fadeDirection2 == 0)
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
    if (globalLED.fadeDirection2 == 1)
    {
      xoffset += timeinc;
    }
    if (globalLED.fadeDirection2 == 0)
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

void RainbowHsv(float hHigh, float hLow, float speed)
{
  h = GetH_BouncingWithLimits(speed, hHigh, hLow);

  hsv2rgb(float(h), 1, (float(brightness.current) / 255.0), red, green, blue);

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {
    setPixel(i, red, green, blue);
  }
}

void RainbowOneYoffset()
{
  globalStrings.functionName = "RainbowOneYoffset";
  spaceinc = 0.03;
  timeinc = (0.000025 * globals.currentSpeed);
  yoffset += timeinc;
  //xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
}
void RainbowTwoYoffset()
{
  globalStrings.functionName = "RainbowTwoYoffset";
  spaceinc = 0.07;
  timeinc = (0.000025 * globals.currentSpeed);
  yoffset += timeinc;
  //xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
}
void RainbowThreeXoffset()
{
  globalStrings.functionName = "RainbowThreeXoffset";
  spaceinc = 0.07;
  timeinc = (0.000025 * globals.currentSpeed);
  //yoffset += timeinc;
  xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
}
void RainbowFourXoffset()
{
  globalStrings.functionName = "RainbowFourXoffset";
  spaceinc = 0.03;
  timeinc = (0.000025 * globals.currentSpeed);
  //yoffset += timeinc;
  xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
}
void RainbowBigXoffset()
{
  globalStrings.functionName = "RainbowBigXoffset";
  spaceinc = 0.12;
  timeinc = (0.000025 * globals.currentSpeed);
  //yoffset += timeinc;
  xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
}
void RainbowBigYoffset()
{
  globalStrings.functionName = "RainbowBigYoffset";
  spaceinc = 0.12;
  timeinc = (0.000025 * globals.currentSpeed);
  yoffset += timeinc;
  //xoffset += timeinc;
  SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
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
  h = hStart;

  float hTemp = h;

  for (uint16_t i = 0; i < NUM_LEDS; i++)
  {

    hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), red, green, blue);
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

    hsv2rgb(float(hTemp), 1, (float(brightness.current) / 255.0), red, green, blue);
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
  for (uint16_t i = 0; i < NUM_LEDS; i = i + ledSpacing)
  {
    switch (ledSpacing)
    {
    // case 6:
    //   setPixel(i, red, green, blue);
    //   setPixel(i + 1, red, green, blue);
    //   setPixel(i + 2, red, green, blue);

    //   setPixel(i + 3, red2, green2, blue2);
    //   setPixel(i + 4, red2, green2, blue2);
    //   setPixel(i + 5, red2, green2, blue2);
    //   break;
    // case 4:
    //   setPixel(i, red, green, blue);
    //   setPixel(i + 1, red, green, blue);

    //   setPixel(i + 2, red2, green2, blue2);
    //   setPixel(i + 3, red2, green2, blue2);
    //   break;
    case 3:
      setPixel(i, 255, 0, 0);
      setPixel(i + 1, 0, 255, 0);
      setPixel(i + 2, 0, 0, 255);
      break;
    default:
      setPixel(i, red, green, blue);
      setPixel(i + 1, red2, green2, blue2);
      break;
    }
  }

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

  if (brightness.useFade == true)
  {
    fadeLightBy(i, brightness.current);
    fadeLightBy(i + 1, brightness.current);
    fadeLightBy(i + 2, brightness.current);
    // fadeLightBy(i + 3, brightness.current);
    // fadeLightBy(i + 4, brightness.current);
    // fadeLightBy(i + 5, brightness.current);

    // fadeLightBy(i + 6, brightness.current);
    // fadeLightBy(i + 7, brightness.current);
    // fadeLightBy(i + 8, brightness.current);
    // fadeLightBy(i + 9, brightness.current);
    // fadeLightBy(i + 10, brightness.current);
    // fadeLightBy(i + 11, brightness.current);
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
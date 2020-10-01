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
    functionName = "SteadyRGB 3";
    SteadyRGB(3);
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
  case 31:
    functionName = "DLCLRflo2 .00009.9";
    DualColorFlowTwo(.00009, .9);
    break;
  case 32:
    functionName = "DLCLRflo2 .0009.9";
    DualColorFlowTwo(.0009, .9);
    break;
  case 33:
    functionName = "DLCLRflo2 .0009.4";
    DualColorFlowTwo(.0009, .4);
    break;
  case 34:
    functionName = "DLCLRflo2 .00009.1";
    DualColorFlowTwo(.00009, .1);
    break;
  case 35:
    functionName = "DLCLRflo2 .0007.5";
    DualColorFlowTwo(.0007, .5);
    break;
  case 36:
    functionName = "DLCLRflo2 .0075.7";
    DualColorFlowTwo(.00075, .7);
    break;
  case 37:
    functionName = "DLCLRflo2 .0001.3";
    DualColorFlowTwo(.0001, .3);
    break;
  case 38:
    functionName = "DLCLRflo2 .0009.6";
    DualColorFlowTwo(.0009, .6);
    break;
  case 39:
    functionName = "DLCLRflo2 .0007.1";
    DualColorFlowTwo(.0007, .1);
    break;
  case 40:
    functionName = "DLCLRflo2 .0005.9";
    DualColorFlowTwo(.0005, .9);
    break;
  case 41:
    functionName = "DLCLRflo 1";
    DualColorFlow(.85, .58, .46, .09, .00009, .9);
    break;
  case 42:
    functionName = "DLCLRflo 2";
    DualColorFlow(.45, .20, .24, .03, .0009, .5);
    break;
  case 43:
    functionName = "DLCLRflo 3";
    DualColorFlow(.7, .3, .85, .6, .0005, .1);
    break;
  case 44:
    functionName = "DLCLRflo 4";
    DualColorFlow(.9, .5, .85, .6, .0007, .1);
    break;
  case 45:
    functionName = "DLCLRflo 5";
    DualColorFlow(.15, .05, .4, .059, .0029, .1);
    break;
  case 46:
    functionName = "DLCLRflo 6";
    DualColorFlow(.9, .5, .85, .6, .0007, .7);
    break;
  case 47:
    functionName = "DLCLRflo 7";
    DualColorFlow(.9, .5, .4, .1, .00069, .1);
    break;
  case 48:
    functionName = "DLCLRflo 8";
    DualColorFlow(.9, .6, .85, .6, .000420, .1);
    break;
  case 49:
    functionName = "DLCLRflo 9";
    DualColorFlow(.8, .5, .5, .2, .00042, .5);
    break;
  case 50:
    functionName = "DLCLRflo 10";
    DualColorFlow(.8, .5, .5, .2, .00042, .1);
    break;
  case 51:
    functionName = "DLCLRfloB 1";
    DualColorFlowBounce(.85, .58, .00009, .1, 2);
    break;
  case 52:
    functionName = "DLCLRfloB 2";
    DualColorFlowBounce(.17, .02, .00009, .1, 2);
    break;
  case 53:
    functionName = "DLCLRfloB 3";
    DualColorFlowBounce(.9, .7, .00042, .1, 2);
    break;
  case 54:
    functionName = "DLCLRfloB 4";
    DualColorFlowBounce(.3, .1, .00042, .1, 2);
    break;
  case 55:
    functionName = "DLCLRfloB 5";
    DualColorFlowBounce(.7, .4, .00069, .5, 2);
    break;
  case 56:
    functionName = "DLCLRfloB 6";
    DualColorFlowBounce(.5, .2, .00009, .7, 2);
    break;
  case 57:
    functionName = "DLCLRfloB 7";
    DualColorFlowBounce(.42, .1, .0009, .1, 4);
    break;
  case 58:
    functionName = "DLCLRfloB 8";
    DualColorFlowBounce(.85, .24, .00009, .5, 4);
    break;
  case 59:
    functionName = "DLCLRfloB 9";
    DualColorFlowBounce(.55, .21, .0001, .1, 6);
    break;
  case 60:
    functionName = "DLCLRfloB 10";
    DualColorFlowBounce(.84, .42, .0007, .5, 6);
    break;
  case 61:
    functionName = "LGFloB 1";
    LargeGroupColorFlowBounce(.85, .58, .00009, .1, 2);
    break;
  case 62:
    functionName = "LGFloB 2";
    LargeGroupColorFlowBounce(.17, .02, .00009, .1, 2);
    break;
  case 63:
    functionName = "LGFloB 3";
    LargeGroupColorFlowBounce(.9, .7, .00042, .1, 2);
    break;
  case 64:
    functionName = "LGFloB 4";
    LargeGroupColorFlowBounce(.3, .1, .00042, .1, 4);
    break;
  case 65:
    functionName = "LGFloB 5";
    LargeGroupColorFlowBounce(.7, .4, .00069, .5, 6);
    break;
  case 66:
    functionName = "RainbowFlow 1";
    RainbowFlow(.98, .01, .00025, .01);
    break;
  case 67:
    functionName = "RainbowFlow 2";
    RainbowFlow(.98, .01, .00007, .002);
    break;
  case 68:
    functionName = "RainbowFlow 3";
    RainbowFlow(.98, .01, .00025, .1);
    break;
  case 69:
    functionName = "RainbowFlow 4";
    RainbowFlow(.98, .01, .00042, .25);
    break;
  case 70:
    functionName = "RainbowNoFlow 1";
    RainbowNoFlow(.042);
    break;
  case 71:
    functionName = "RainbowFlowSlow 1";
    RainbowFlowSlow(.0005, .0045);
    break;
  case 72:
    functionName = "RainbowFlowSlow 2";
    RainbowFlowSlow(.0005, .007);
    break;
  case 73:
    functionName = "RainbowFlowSlow 3";
    RainbowFlowSlow(.0001, .0045);
    break;
  case 74:
    functionName = "RainbowHsv 1";
    RainbowHsv(.00009, .98, .75);
    break;
  case 75:
    functionName = "RainbowHsv 2";
    RainbowHsv(.00009, .98, .55);
    break;
  case 76:
    functionName = "RainbowHsv 3";
    RainbowHsv(.000009, .75, .55);
    break;
  case 77:
    functionName = "RainbowHsv 3";
    RainbowHsv(.000009, .98, .01);
    break;
  case 78:
    functionName = "RainbowHsv 4";
    RainbowHsv(.0001, .98, .01);
    break;
  case 79:
    functionName = "RainbowHsv 5";
    RainbowHsv(.00042, .98, .01);
    break;
  case 80:
    functionName = "RainbowHsv 6";
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
    fadeDirection = 0;
  }
  if (h < hLow)
  {
    h = hLow;
    fadeDirection = 1;
  }

  if (fadeDirection == 1)
  {
    h += hSpeed; // increment to make faster
  }
  if (fadeDirection == 0)
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

  if (useFade == true)
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
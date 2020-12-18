// MATT TAYLOR
// BROKE THIS
// SOME HOW AROUND THE CATEGORY REFACTOR
// -- WOULD FREEZE BOX WHEN SELECTED
// void legacy_category(int patternMode)
// {
//   globalStrings.categoryName = "LEGACY";

void legacy_category(int patternMode)
{
  globalStrings.categoryName = "LEGACY";
  
  switch (patternMode)
  {
  case 0:
    globalStrings.functionName = "Random";
    break;
  case 1:
    RainbowBigXoffset();
    break;
  case 2:
    RainbowBigXoffset();
    AmberSmatter(4);
    break;
  case 3:
    RainbowBigXoffset(); 
    AmberSmatter(6);
    break;
  case 4:
    RainbowBigXoffset();
    AmberSmatter(10);
    break;
  case 5:
    RainbowBigYoffset(); 
    break;
  case 6:
    RainbowBigYoffset();	
    AmberSmatter(3);
    break;
  case 7:
    RainbowBigYoffset(); 
    AmberSmatter(10);
    break;
  case 8:
    RainbowTwoYoffset();
    break;
  case 9:
    RainbowTwoYoffset();
    AmberSmatter(5);
    break;
  case 10:
    RainbowTwoYoffset();
    AmberSmatter(7);
    break;	
  case 11:
    RainbowFourXoffset();
    break;
  case 12:
    RainbowFourXoffset();
    AmberSmatter(2);
    break;
  case 13:
    RainbowFourXoffset();
    AmberSmatter(5);
    break;	
  case 14:
    RainbowOneYoffset();
    break;
  case 15:
    RainbowOneYoffset();
    AmberSmatter(4);
    break;
  case 16:
    RainbowOneYoffset();
    AmberSmatter(6);
    break;	
  case 17:
    RainbowThreeXoffset();
    break;
  case 18:
    RainbowThreeXoffset();
    AmberSmatter(3);
    break;
  case 19:
    RainbowThreeXoffset();
    AmberSmatter(6);
    break;
  /*
  case 20:
    globalStrings.functionName = "RbowY 0.000025, 0.3";
    RainbowYoffset(0.000025, 0.3, true);
    break;
  case 21:
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
  */
  case 20:
    globalStrings.functionName = "Red Green";
    SteadyAlternatingColors(CRGB::Red, CRGB::Green, patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);
    break;
  case 21:
    globalStrings.functionName = "Blue White";
    SteadyAlternatingColors(CRGB::Blue, CRGB::White, patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);
    break;
  case 22:
    globalStrings.functionName = "Purple Blue";
    SteadyAlternatingColors(CRGB::Purple, CRGB::Blue, patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);
    break;
  case 23:
    globalStrings.functionName = "Yellow Purple";
    SteadyAlternatingColors(CRGB::Yellow, CRGB::Purple, patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);
    break;
  case 24:
    globalStrings.functionName = "Red White";
    SteadyAlternatingColors(CRGB::Red, CRGB::White, patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);
    break;
  case 25:
    globalStrings.functionName = "Orange Blue";
    SteadyAlternatingColors(CRGB::Orange, CRGB::Blue, patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);
    break;
  case 26:
    globalStrings.functionName = "Orange Purple";
    SteadyAlternatingColors(CRGB::Orange, CRGB::Purple, patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);
    break;
  case 27:
    globalStrings.functionName = "MovingHue 85.002";
    MovingHue(patternSettings.gHue, .0001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);
    break;
  case 28:
    globalStrings.functionName = "MovingHue 42.008";
    MovingHue(42, .008);
    break;
  case 29:
    globalStrings.functionName = "MovingHue 128.016";
    MovingHue(128, .025);
    break;
  case 30:
    globalStrings.functionName = "MovingHue 85.3";
    MovingHue(85, .3);
    break;
  case 31:
    globalStrings.functionName = "MovingHue 42.5";
    MovingHue(42, .5);
    break;
  case 32:
    globalStrings.functionName = "MovingHue 128.7";
    MovingHue(128, .7);
    break;
  case 33:
    globalStrings.functionName = "MovingHue 85.3.9";
    MovingHue(85, .3, .9);
    break;
  case 34:
    globalStrings.functionName = "MovingHue 42.5.4";
    MovingHue(42, .5, .4);
    break;
  case 35:
    globalStrings.functionName = "MovingHue 128.7.1";
    MovingHue(128, .7, .1);
    break;
  case 36:
    globalStrings.functionName = "MovingHue 128.7 3";
    MovingHue(patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .7, 3);
    break;
  case 37:
    globalStrings.functionName = "Color Flow A 1";
    DualColorFlowTwo(.000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .9);
    break;
  case 38:
    globalStrings.functionName = "Color Flow A 2";
    DualColorFlowTwo(.00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .4);
    break;
  case 39:
    globalStrings.functionName = "Color Flow A 3";
    DualColorFlowTwo(.00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1);
    break;
  case 40:
    globalStrings.functionName = "Color Flow A 4";
    DualColorFlowTwo(.00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .5);
    break;
  case 41:
    globalStrings.functionName = "Color Flow A 5";
    DualColorFlowTwo(.00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .7);
    break;
  case 42:
    globalStrings.functionName = "Color Flow A 6";
    DualColorFlowTwo(.00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .3);
    break;
  case 43:
    globalStrings.functionName = "Color Flow A 7";
    DualColorFlowTwo(.00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .6);
    break;
  case 44:
    globalStrings.functionName = "Color Flow A 8";
    DualColorFlowTwo(.00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1);
    break;
  case 45:
    globalStrings.functionName = "Color Flow A 9";
    DualColorFlowTwo(.00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .9);
    break;
  case 46:
    globalStrings.functionName = "Color Flow B 1";
    DualColorFlow(.85, .58, .46, .09, .000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .9);
    break;
  case 47:
    globalStrings.functionName = "Color Flow B 2";
    DualColorFlow(.45, .20, .24, .03, .000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .5);
    break;
  case 48:
    globalStrings.functionName = "Color Flow B 3";
    DualColorFlow(.7, .3, .85, .6, .000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1);
    break;
  case 49:
    globalStrings.functionName = "Color Flow B 4";
    DualColorFlow(.9, .5, .85, .6, .000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1);
    break;
  case 50:
    globalStrings.functionName = "Color Flow B 5";
    DualColorFlow(.15, .05, .4, .059, .000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1);
    break;
  case 51:
    globalStrings.functionName = "Color Flow B 6";
    DualColorFlow(.9, .5, .85, .6, .000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .7);
    break;
  case 52:
    globalStrings.functionName = "Color Flow B 7";
    DualColorFlow(.9, .5, .4, .1, .000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1);
    break;
  case 53:
    globalStrings.functionName = "Color Flow B 8";
    DualColorFlow(.9, .6, .85, .6, .000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1);
    break;
  case 54:
    globalStrings.functionName = "Color Flow B 9";
    DualColorFlow(.8, .5, .5, .2, .000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .5);
    break;
  case 55:
    globalStrings.functionName = "Color Flow B 10";
    DualColorFlow(.8, .5, .5, .2, .000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1);
    break;
  case 56:
    globalStrings.functionName = "Color Bounce 1";
    DualColorFlowBounce(.85, .58, .000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1, 2);
    break;
  case 57:
    globalStrings.functionName = "Color Bounce 2";
    DualColorFlowBounce(.17, .02, .000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1, 2);
    break;
  case 58:
    globalStrings.functionName = "Color Bounce 3";
    DualColorFlowBounce(.9, .7, .000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1, 2);
    break;
  case 59:
    globalStrings.functionName = "Color Bounce 4";
    DualColorFlowBounce(.3, .1, .000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1, 2);
    break;
  case 60:
    globalStrings.functionName = "Color Bounce 5";
    DualColorFlowBounce(.7, .4, .00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .5, 2);
    break;
  case 61:
    globalStrings.functionName = "Color Bounce 6";
    DualColorFlowBounce(.5, .2, .00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .7, 2);
    break;
  case 62:
    globalStrings.functionName = "Color Bounce 7";
    DualColorFlowBounce(.42, .1, .00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1, 4);
    break;
  case 63:
    globalStrings.functionName = "Color Bounce 8";
    DualColorFlowBounce(.85, .24, .00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .5, 4);
    break;
  case 64:
    globalStrings.functionName = "Color Bounce 9";
    DualColorFlowBounce(.55, .21, .00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1, 6);
    break;
  case 65:
    globalStrings.functionName = "Color Bounce 10";
    DualColorFlowBounce(.84, .42, .00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .5, 6);
    break;
  case 66:
    globalStrings.functionName = "Color Bounce B 1";
    LargeGroupColorFlowBounce(.85, .58, .00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1, 2);
    break;
  case 67:
    globalStrings.functionName = "Color Bounce B 2";
    LargeGroupColorFlowBounce(.17, .02, .00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1, 2);
    break;
  case 68:
    globalStrings.functionName = "Color Bounce B 3";
    LargeGroupColorFlowBounce(.9, .7, .00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1, 2);
    break;
  case 69:
    globalStrings.functionName = "Color Bounce B 4";
    LargeGroupColorFlowBounce(.3, .1, .00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1, 4);
    break;
  case 70:
    globalStrings.functionName = "Color Bounce B 5";
    LargeGroupColorFlowBounce(.7, .4, .00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .5, 6);
    break;
  case 71:
    globalStrings.functionName = "Rainbow Flow 1";
    RainbowFlow(.98, .01, .00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .01);
    break;
  case 72:
    globalStrings.functionName = "Rainbow Flow 2";
    RainbowFlow(.98, .01, .00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .002);
    break;
  case 73:
    globalStrings.functionName = "Rainbow Flow 3";
    RainbowFlow(.98, .01, .00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .1);
    break;
  case 74:
    globalStrings.functionName = "Rainbow Flow 4";
    RainbowFlow(.98, .01, .00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .25);
    break;
  case 75:
    globalStrings.functionName = "Rainbow NoFlow 1";
    RainbowNoFlow(float(patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]] / 255));
    break;
  case 76:
    globalStrings.functionName = "Rainbow Flow B 1";
    RainbowFlowSlow(.00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .0045);
    break;
  case 77:
    globalStrings.functionName = "Rainbow Flow B 2";
    RainbowFlowSlow(.00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .007);
    break;
  case 78:
    globalStrings.functionName = "Rainbow Flow B 3";
    RainbowFlowSlow(.00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .0045);
    break;
  case 79:
    globalStrings.functionName = "Rainbow 1";
    RainbowHsv(.00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .98, .75);
    break;
  case 80:
    globalStrings.functionName = "Rainbow 2";
    RainbowHsv(.000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .98, .55);
    break;
  case 81:
    globalStrings.functionName = "Rainbow 3";
    RainbowHsv(.000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .75, .55);
    break;
  case 82:
    globalStrings.functionName = "Rainbow 3";
    RainbowHsv(.000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .98, .01);
    break;
  case 83:
    globalStrings.functionName = "Rainbow 4";
    RainbowHsv(.000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .98, .01);
    break;
  case 84:
    globalStrings.functionName = "Rainbow 5";
    RainbowHsv(.00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .98, .01);
    break;
  case 85:
    globalStrings.functionName = "Rainbow 6";
    RainbowHsv(.00001 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]], .55, .25);
    break;
  }
}

void AmberSmatter(int Spacing){
  for(uint16_t i = 0; i < NUM_LEDS; i = i + Spacing) {
    setPixel(i, 255, 32,0); //Amber 
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
  globalStrings.functionName = "FlowY 1";
  simplexNoise.spaceInc = 0.03;
  simplexNoise.timeInc = (0.000025 *  patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);
  simplexNoise.yoffset += simplexNoise.timeInc;
  //simplexNoise.xoffset += simplexNoise.timeInc;
  SimplexNoisePatternInterpolated(simplexNoise.spaceInc, simplexNoise.timeInc, simplexNoise.yoffset, simplexNoise.xoffset);
}
void RainbowTwoYoffset()
{
  globalStrings.functionName = "FlowY 2";
  simplexNoise.spaceInc = 0.07;
  simplexNoise.timeInc = (0.000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);
  simplexNoise.yoffset += simplexNoise.timeInc;
  //simplexNoise.xoffset += simplexNoise.timeInc;
  SimplexNoisePatternInterpolated(simplexNoise.spaceInc, simplexNoise.timeInc, simplexNoise.yoffset, simplexNoise.xoffset);
}
void RainbowThreeXoffset()
{
  globalStrings.functionName = "FlowX 1";
  simplexNoise.spaceInc = 0.07;
  simplexNoise.timeInc = (0.000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);
  //simplexNoise.yoffset += simplexNoise.timeInc;
  simplexNoise.xoffset += simplexNoise.timeInc;
  SimplexNoisePatternInterpolated(simplexNoise.spaceInc, simplexNoise.timeInc, simplexNoise.yoffset, simplexNoise.xoffset);
}
void RainbowFourXoffset()
{
  globalStrings.functionName = "FlowX 2";
  simplexNoise.spaceInc = 0.03;
  simplexNoise.timeInc = (0.000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);
  //simplexNoise.yoffset += simplexNoise.timeInc;
  simplexNoise.xoffset += simplexNoise.timeInc;
  SimplexNoisePatternInterpolated(simplexNoise.spaceInc, simplexNoise.timeInc, simplexNoise.yoffset, simplexNoise.xoffset);
}
void RainbowBigXoffset()
{
  globalStrings.functionName = "FlowX 3";
  simplexNoise.spaceInc = 0.12;
  simplexNoise.timeInc = (0.000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);
  //simplexNoise.yoffset += simplexNoise.timeInc;
  simplexNoise.xoffset += simplexNoise.timeInc;
  SimplexNoisePatternInterpolated(simplexNoise.spaceInc, simplexNoise.timeInc, simplexNoise.yoffset, simplexNoise.xoffset);
}
void RainbowBigYoffset()
{
  globalStrings.functionName = "FlowY 3";
  simplexNoise.spaceInc = 0.12;
  simplexNoise.timeInc = (0.000025 * patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);
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
void SteadyAlternatingColors(CRGB color1, CRGB color2, int Spacing)
{
  if (Spacing == 0)
  {
    Spacing = 1;
  }
  
  for (uint16_t i = 0; i < NUM_LEDS; i = i + Spacing * 2)
  {
    for (uint16_t ii = 0; i < Spacing; i++)
    {
      setPixel(i + ii, color1);
    }

    for (uint16_t ii = 0; i < Spacing; i++)
    {
      setPixel((i * 2) + ii, color2);
    }
  }
}
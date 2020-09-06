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
    // case 12:
    //   functionName = "LGBlueWhite 2";
    //   LargeGroupBlueWhite(2);
    //   break;
    // case 13:
    //   functionName = "LGBlueWhite 5";
    //   LargeGroupBlueWhite(5);
    //   break;
    // case 14:
    //   functionName = "LGRedGreen 2";
    //   LargeGroupRedGreen(2);
    //   break;
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

void LargeGroupBlueWhite(int ledSpacing)
{
  for (uint16_t i = 0; i < NUM_LEDS; i = i + ledSpacing)
  {
    setPixel(i, 0, 0, 255);
    setPixel(i + 1, 0, 0, 255);
    setPixel(i + 2, 0, 0, 255);
    setPixel(i + 3, 0, 0, 255);
    setPixel(i + 4, 0, 0, 255);
    setPixel(i + 5, 0, 0, 255);

    setPixel(i + 6, 0, 0, 255);
    setPixel(i + 7, 0, 0, 255);
    setPixel(i + 8, 0, 0, 255);
    setPixel(i + 9, 0, 0, 255);
    setPixel(i + 10, 0, 0, 255);
    setPixel(i + 11, 0, 0, 255);

    // if (useFade == true)
    // {
    //   fadeLightBy(i, brightness);
    //   fadeLightBy(i + 1, brightness);
    //   fadeLightBy(i + 2, brightness);
    //   fadeLightBy(i + 3, brightness);
    //   fadeLightBy(i + 4, brightness);
    //   fadeLightBy(i + 5, brightness);

    //   fadeLightBy(i + 6, brightness);
    //   fadeLightBy(i + 7, brightness);
    //   fadeLightBy(i + 8, brightness);
    //   fadeLightBy(i + 9, brightness);
    //   fadeLightBy(i + 10, brightness);
    //   fadeLightBy(i + 11, brightness);
    // }
  }
}
void LargeGroupRedGreen(int ledSpacing)
{
  for (uint16_t i = 0; i < NUM_LEDS; i = i + ledSpacing)
  {
    leds[i].setRGB(255, 0, 0);
    leds[i + 1].setRGB(255, 0, 0);
    leds[i + 2].setRGB(255, 0, 0);
    leds[i + 3].setRGB(255, 0, 0);
    leds[i + 4].setRGB(255, 0, 0);
    leds[i + 5].setRGB(255, 0, 0);

    leds[i + 6].setRGB(0, 255, 0);
    leds[i + 7].setRGB(0, 255, 0);
    leds[i + 8].setRGB(0, 255, 0);
    leds[i + 9].setRGB(0, 255, 0);
    leds[i + 10].setRGB(0, 255, 0);
    leds[i + 11].setRGB(0, 255, 0);

    // if (useFade == true)
    // {

    //   leds[i].fadeLightBy(brightness);
    //   leds[i + 1].fadeLightBy(brightness);
    //   leds[i + 2].fadeLightBy(brightness);
    //   leds[i + 3].fadeLightBy(brightness);
    //   leds[i + 4].fadeLightBy(brightness);
    //   leds[i + 5].fadeLightBy(brightness);

    //   leds[i + 6].fadeLightBy(brightness);
    //   leds[i + 7].fadeLightBy(brightness);
    //   leds[i + 8].fadeLightBy(brightness);
    //   leds[i + 9].fadeLightBy(brightness);
    //   leds[i + 10].fadeLightBy(brightness);
    //   leds[i + 11].fadeLightBy(brightness);
    // }
  }
}
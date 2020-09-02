void moving_colors_category(int patternMode)
{
  categoryName = "MOVING COLORS";

  switch (patternMode)
  {
  case 0:
  {
    functionName = "MC 0";
    long pattern[] = {CRGB::Green, CRGB::Grey, CRGB::Red, CRGB::Grey, CRGB::Red, CRGB::Grey, CRGB::Red, CRGB::Green, CRGB::Green, CRGB::Green};
    const int numberOfColors = sizeof(pattern) / sizeof(int); //Auto calculate your specified number of color bars
    MovingColoredBars(NUM_LEDS - 1, pattern, numberOfColors);
  }
  break;
  case 1:
  {
    functionName = "MC 1";
    long pattern[] = {CRGB::Red, CRGB::Green, CRGB::Red};
    const int numberOfColors = sizeof(pattern) / sizeof(int);
    MovingColoredBars(NUM_LEDS / 2, pattern, numberOfColors);
  }
  break;
  case 2:
  {
    functionName = "MC 2";
    long pattern[] = {CRGB::Blue, CRGB::Blue, CRGB::Yellow, CRGB::Purple};
    const int numberOfColors = sizeof(pattern) / sizeof(int);
    MovingColoredBars(NUM_LEDS / numberOfColors, pattern, numberOfColors);
  }
  break;
  case 3:
  {
    functionName = "MC 2";
    long pattern[] = {CRGB::Purple, CRGB::Blue, CRGB::Teal, CRGB::Purple};
    const int numberOfColors = sizeof(pattern) / sizeof(int);
    MovingColoredBars(NUM_LEDS / numberOfColors, pattern, numberOfColors);
  }
  break;
  case 4:
    functionName = "Breathing 1";
    BreathingEffect(0.5, true, true, true);
    break;
  case 5:
    functionName = "Breathing 2";
    BreathingEffect(0.5, true, false, true);
    break;
  case 6:
    functionName = "Breathing 3";
    BreathingEffect(0.5, true, true, false);
    break;
  case 7:
    functionName = "Breathing 4";
    BreathingEffect(0.5, false, false, true);
    break;
  case 8:
    functionName = "Breathing 5";
    BreathingEffect(0.5, true, false, false);
    break;
  case 9:
    functionName = "Breathing 6";
    BreathingEffect(0.5, false, false, false);
    break;
  case 10:
    functionName = "Breathing 7";
    BreathingEffect(0.1, true, true, true);
    break;
  case 11:
    functionName = "Breathing 8";
    BreathingEffect(0.7, true, true, true);
    break;
  case 12:
    functionName = "Breathing 9";
    BreathingEffect(1, true, true, true);
    break;
  }
}

// FUNCTIONS

void MovingColoredBars(int colorBarLength, long colorPallete[], int numberOfColors)
{

  EVERY_N_MILLISECONDS(FRAMES_PER_SECOND)
  {

    for (int x = 0; x < NUM_LEDS - 1; x++)
    {
      leds[x] = leds[x + 1];
    }
    if (clearLEDS)
    {
      leds[NUM_LEDS - 1] = colorPallete[palletPosition];
    }
    if ((colorBarPosition <= colorBarLength) && !clearLEDS)
    {
      leds[NUM_LEDS - 1] = colorPallete[palletPosition];
      colorBarPosition++;
    }
    if ((palletPosition == numberOfColors - 1) && (colorBarPosition > colorBarLength) && !clearLEDS)
    {
      leds[NUM_LEDS - 1] = colorPallete[palletPosition];
      palletPosition = 0;
      colorBarPosition = 1;
      clearLEDS = true;
    }
    if ((colorBarPosition > colorBarLength) && !clearLEDS)
    {
      colorBarPosition = 1;
      palletPosition = palletPosition + 1;
    }
    //if (clearLEDS && !leds(0,NUM_LEDS-1))  //Not using this for of test any more
    if (clearLEDS && leds[0] == (CRGB)(colorPallete[numberOfColors - 1])) //restarts as soon as last color makes it past the end
    {
      //Serial.print( leds[0].r );  Serial.print("\t"), Serial.print( leds[0].g ); Serial.print("\t"), Serial.println( leds[0].b );  //Print out RGB colors it's triggering on
      clearLEDS = false;
    }

  } //end_EVERY_N
}

void BreathingEffect(float pulseSpeed, bool red, bool green, bool blue)
{
  float dV = ((exp(sin(pulseSpeed * millis() / 2000.0 * PI)) - 0.36787944) * delta);
  val = valueMin + dV;
  hue = map(val, valueMin, valueMax, hueA, hueB); // Map hue based on current val
  sat = map(val, valueMin, valueMax, satA, satB); // Map sat based on current val

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CHSV(hue, sat, val);

    // You can experiment with commenting out these dim8_video lines
    // to get a different sort of look.
    if (red)
    {
      leds[i].r = dim8_video(leds[i].r);
    }
    if (green)
    {

      leds[i].g = dim8_video(leds[i].g);
    }
    if (blue)
    {

      leds[i].b = dim8_video(leds[i].b);
    }
  }
}

// void DualColorFlow(float _speed, float _spacing)
// {
//   h = GetH_BouncingWithLimits(_speed, .97, 0);

//   float hTemp = h;

//   hTemp = h + _spacing; // space between colors
//   if (hTemp > 1)
//   {
//     hTemp -= 1;
//   }
//   if (hTemp < 0)
//   {
//     hTemp += 1;
//   }

//   hsv2rgb(float(h), 1, (float(brightness) / 255.0), red, green, blue);
//   hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red2, green2, blue2);

//   for (uint16_t i = 0; i < NUM_LEDS; i = i + 2)
//   {
//     fill_solid(leds, NUM_LEDS, CRGB(red, green, blue));
//     fill_solid(leds + 1, NUM_LEDS, CRGB(red2, green2, blue2));
//   }
// }
// void DualColorFlowBounce(int _ledSpacing, float _speed, float _spacing, float _hHigh, float _hLow)
// {
//   h = GetH_BouncingWithLimits(_speed, _hHigh, _hLow);

//   float hTemp = h;
//   hTemp = h - _spacing; // space between colors
//   if (hTemp > 1)
//   {
//     hTemp -= 1;
//   }
//   if (hTemp < 0)
//   {
//     hTemp += 1;
//   }
//   hsv2rgb(float(h), 1, (float(brightness) / 255.0), red, green, blue);
//   hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red2, green2, blue2);

//   for (uint16_t i = 0; i < NUM_LEDS; i = i + _ledSpacing)
//   {
//     fill_solid(leds, NUM_LEDS, CRGB(red, green, blue));
//     fill_solid(leds + 1, NUM_LEDS, CRGB(red2, green2, blue2));
//   }
// }
// void DualColorFlowOne()
// {
//   h += .00007; // increment to make faster
//   if (h > 1)
//   {
//     h -= 1;
//   }
//   if (h < 0)
//   {
//     h += 1;
//   }

//   float hTemp = h;

//   hTemp = h + .5; // space between colors

//   if (hTemp > 1)
//   {
//     hTemp -= 1;
//   }
//   if (hTemp < 0)
//   {
//     hTemp += 1;
//   }

//   hsv2rgb(float(h), 1, (float(brightness) / 255.0), red, green, blue);

//   hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red2, green2, blue2);

//   for (uint16_t i = 0; i < NUM_LEDS; i = i + 2)
//   {

//     fill_solid(leds, NUM_LEDS, CRGB(red, green, blue));
//     fill_solid(leds + 1, NUM_LEDS, CRGB(red2, green2, blue2));
//   }
// }

// void DualColorFlowFour()
// {
//   float hHigh = .9;
//   float hLow = .5;
//   float hHigh2 = .85;
//   float hLow2 = .6;

//   if (h > hHigh)
//   {
//     h = hHigh;
//     fadeDirection = 0;
//   }
//   if (h < hLow)
//   {
//     h = hLow;
//     fadeDirection = 1;
//   }

//   if (fadeDirection == 1)
//   {
//     h += .00009; // increment to make faster
//   }
//   if (fadeDirection == 0)
//   {
//     h -= .00009; // decrement to make faster
//   }

//   float hTemp = h;

//   hTemp = h - .1; // space between colors

//   hsv2rgb(float(h), 1, (float(brightness) / 255.0), red, green, blue);

//   hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red2, green2, blue2);

//   for (uint16_t i = 0; i < NUM_LEDS; i = i + 6)
//   {

//     strip.setPixelColor(i, strip.Color(red, green, blue));
//     strip.setPixelColor(i + 1, strip.Color(red2, green2, blue2));
//   }
//   strip.show();
// }
// void DualColorFlowPurpleFast()
// {
//   float hHigh = .9;
//   float hLow = .5;
//   float hHigh2 = .85;
//   float hLow2 = .6;

//   if (h > hHigh)
//   {
//     h = hHigh;
//     fadeDirection = 0;
//   }
//   if (h < hLow)
//   {
//     h = hLow;
//     fadeDirection = 1;
//   }

//   if (fadeDirection == 1)
//   {
//     h += .0009; // increment to make faster
//   }
//   if (fadeDirection == 0)
//   {
//     h -= .0009; // decrement to make faster
//   }

//   float hTemp = h;

//   hTemp = h - .1; // space between colors

//   hsv2rgb(float(h), 1, (float(brightness) / 255.0), red, green, blue);

//   hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red2, green2, blue2);

//   for (uint16_t i = 0; i < NUM_LEDS; i = i + 2)
//   {

//     strip.setPixelColor(i, strip.Color(red, green, blue));
//     strip.setPixelColor(i + 1, strip.Color(red2, green2, blue2));
//   }
//   strip.show();
// }
// void DualColorFlowRedFast()
// {
//   float hHigh = .15;
//   float hLow = .05;

//   if (h > hHigh)
//   {
//     h = hHigh;
//     fadeDirection = 0;
//   }
//   if (h < hLow)
//   {
//     h = hLow;
//     fadeDirection = 1;
//   }

//   if (fadeDirection == 1)
//   {
//     h += .001; // increment to make faster
//   }
//   if (fadeDirection == 0)
//   {
//     h -= .001; // decrement to make faster
//   }

//   float hTemp = h;

//   hTemp = h - .1; // space between colors

//   if (h > 1)
//   {
//     h -= 1;
//   }
//   if (h < 0)
//   {
//     h += 1;
//   }

//   if (hTemp > 1)
//   {
//     hTemp -= 1;
//   }
//   if (hTemp < 0)
//   {
//     hTemp += 1;
//   }
//   hsv2rgb(float(h), 1, (float(brightness) / 255.0), red, green, blue);

//   hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red2, green2, blue2);

//   for (uint16_t i = 0; i < NUM_LEDS; i = i + 2)
//   {

//     strip.setPixelColor(i, strip.Color(red, green, blue));
//     strip.setPixelColor(i + 1, strip.Color(red2, green2, blue2));
//   }
//   strip.show();
// }
// void DualColorFlowGreenFast()
// {
//   float hHigh = .7;
//   float hLow = .3;
//   float hHigh2 = .85;
//   float hLow2 = .6;

//   if (h > hHigh)
//   {
//     h = hHigh;
//     fadeDirection = 0;
//   }
//   if (h < hLow)
//   {
//     h = hLow;
//     fadeDirection = 1;
//   }

//   if (fadeDirection == 1)
//   {
//     h += .0009; // increment to make faster
//   }
//   if (fadeDirection == 0)
//   {
//     h -= .0009; // decrement to make faster
//   }

//   float hTemp = h;

//   hTemp = h - .1; // space between colors

//   hsv2rgb(float(h), 1, (float(brightness) / 255.0), red, green, blue);

//   hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red2, green2, blue2);

//   for (uint16_t i = 0; i < NUM_LEDS; i = i + 2)
//   {

//     strip.setPixelColor(i, strip.Color(red, green, blue));
//     strip.setPixelColor(i + 1, strip.Color(red2, green2, blue2));
//   }
//   strip.show();
// }
// void DualColorFlowPurpleSlow()
// {
//   float hHigh = .85;
//   float hLow = .58;
//   float hHigh2 = .46;
//   float hLow2 = .09;

//   if (h > hHigh)
//   {
//     h = hHigh;
//     fadeDirection = 0;
//   }
//   if (h < hLow)
//   {
//     h = hLow;
//     fadeDirection = 1;
//   }

//   if (fadeDirection == 1)
//   {
//     h += .00009; // increment to make faster
//   }
//   if (fadeDirection == 0)
//   {
//     h -= .00009; // decrement to make faster
//   }

//   float hTemp = h;

//   hTemp = h - .1; // space between colors

//   hsv2rgb(float(h), 1, (float(brightness) / 255.0), red, green, blue);

//   hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red2, green2, blue2);

//   for (uint16_t i = 0; i < NUM_LEDS; i = i + 2)
//   {

//     strip.setPixelColor(i, strip.Color(red, green, blue));
//     strip.setPixelColor(i + 1, strip.Color(red2, green2, blue2));
//   }
//   strip.show();
// }
// void DualColorFlowPurple()
// {
//   float hHigh = .9;
//   float hLow = .5;
//   float hHigh2 = .85;
//   float hLow2 = .6;

//   if (h > hHigh)
//   {
//     h = hHigh;
//     fadeDirection = 0;
//   }
//   if (h < hLow)
//   {
//     h = hLow;
//     fadeDirection = 1;
//   }

//   if (fadeDirection == 1)
//   {
//     h += .00009; // increment to make faster
//   }
//   if (fadeDirection == 0)
//   {
//     h -= .00009; // decrement to make faster
//   }

//   float hTemp = h;

//   hTemp = h - .1; // space between colors

//   hsv2rgb(float(h), 1, (float(brightness) / 255.0), red, green, blue);

//   hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red2, green2, blue2);

//   for (uint16_t i = 0; i < NUM_LEDS; i = i + 2)
//   {

//     strip.setPixelColor(i, strip.Color(red, green, blue));
//     strip.setPixelColor(i + 1, strip.Color(red2, green2, blue2));
//   }
//   strip.show();
// }
// void DualColorFlowTwo()
// {
//   h += .00009; // increment to make faster
//   if (h > 1)
//   {
//     h -= 1;
//   }
//   if (h < 0)
//   {
//     h += 1;
//   }

//   float hTemp = h;

//   hTemp = h + .9; // space between colors

//   if (hTemp > 1)
//   {
//     hTemp -= 1;
//   }
//   if (hTemp < 0)
//   {
//     hTemp += 1;
//   }

//   hsv2rgb(float(h), 1, (float(brightness) / 255.0), red, green, blue);

//   hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red2, green2, blue2);

//   for (uint16_t i = 0; i < NUM_LEDS; i = i + 2)
//   {

//     strip.setPixelColor(i, strip.Color(red, green, blue));
//     strip.setPixelColor(i + 1, strip.Color(red2, green2, blue2));
//   }
//   strip.show();
// }
// void TealPurple()
// {
//   h += .0003; // increment to make faster
//   if (h > 1)
//   {
//     h -= 1;
//   }
//   if (h < 0)
//   {
//     h += 1;
//   }

//   float hTemp = h;

//   hTemp = h + .3; // space between colors

//   if (hTemp > 1)
//   {
//     hTemp -= 1;
//   }
//   if (hTemp < 0)
//   {
//     hTemp += 1;
//   }

//   hsv2rgb(float(h), 1, (float(brightness) / 255.0), red, green, blue);

//   hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red2, green2, blue2);

//   for (uint16_t i = 0; i < NUM_LEDS; i = i + 2)
//   {
//     int high = 80;
//     int low = 0;
//     if (red > high)
//     {
//       red = low;
//     }
//     if (red2 > high)
//     {
//       red2 = low;
//     }
//     strip.setPixelColor(i, strip.Color(red, green, blue));
//     strip.setPixelColor(i + 1, strip.Color(red2, green2, blue2));
//   }
//   strip.show();
// }
// void DualColorFlowThree()
// {
//   h += .0003; // increment to make faster
//   if (h > 1)
//   {
//     h -= 1;
//   }
//   if (h < 0)
//   {
//     h += 1;
//   }

//   float hTemp = h;

//   hTemp = h + .3; // space between colors

//   if (hTemp > 1)
//   {
//     hTemp -= 1;
//   }
//   if (hTemp < 0)
//   {
//     hTemp += 1;
//   }

//   hsv2rgb(float(h), 1, (float(brightness) / 255.0), red, green, blue);

//   hsv2rgb(float(hTemp), 1, (float(brightness) / 255.0), red2, green2, blue2);

//   for (uint16_t i = 0; i < NUM_LEDS; i = i + 2)
//   {

//     strip.setPixelColor(i, strip.Color(red, green, blue));
//     strip.setPixelColor(i + 1, strip.Color(red2, green2, blue2));
//   }
//   strip.show();
// }

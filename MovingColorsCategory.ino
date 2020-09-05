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
  case 13:
    functionName = "Candy Cane 1";
    CandyCane(20, 3, 5, CRGB::White, CRGB::Red, CRGB::Blue);
    break;
  case 14:
    functionName = "Candy Cane 2";
    CandyCane(250, 3, 5, CRGB::Black, CRGB::Orange, CRGB::Green);
    break;
  case 15:
    functionName = "Candy Cane 3";
    CandyCane(200, 3, 5, CRGB::Yellow, CRGB::Green, CRGB::Purple);
    break;
  case 16:
    functionName = "Candy Cane 4";
    CandyCane(250, 3, 5, CRGB::Green, CRGB::Blue, CRGB::Teal);
    break;
  case 17:
    functionName = "Candy Cane 5";
    CandyCane(400, 3, 5, CRGB::Purple, CRGB::Blue, CRGB::White);
    break;
  case 18:
    functionName = "Blend Rainbow 1";
    BlendIntoRainbow(CRGB::Purple, CRGB::Blue, CRGB::Green);
    break;
  case 19:
    functionName = "Blend Rainbow 2";
    BlendIntoRainbow(CRGB::Red, CRGB::Blue, CRGB::White);
    break;
  case 20:
    functionName = "Blend Rainbow 3";
    BlendIntoRainbow(CRGB::Purple, CRGB::Orange, CRGB::White);
    break;
  case 21:
    functionName = "Blend Rainbow 4";
    BlendIntoRainbow(CRGB::Green, CRGB::Blue, CRGB::Yellow);
    break;
  case 22:
    functionName = "Blend Rainbow 5";
    BlendIntoRainbow(CRGB::Orange, CRGB::Purple, CRGB::Green);
    break;
  case 23:
    functionName = "HeartBeat 1";
    HeartBeat(100, 255);
    break;
  case 24:
    functionName = "HeartBeat 2";
    HeartBeat(20, 255);
    break;
  case 25:
    functionName = "HeartBeat 3";
    HeartBeat(155, 255);
    break;
  case 26:
    functionName = "HeartBeat 4";
    HeartBeat(75, 255);
    break;
  case 27:
    functionName = "HeartBeat 5";
    HeartBeat(225, 255);
    break;
  case 28:
    functionName = "Fire 1";
    FireHalfStrip(); // draw fire data to leds_temp

    mirror2ndHalf(); // copy and mirror data from leds_temp to leds
    break;
  case 29:
    functionName = "Fire 2";
    FireFullStrip(); // draw fire data to leds_temp

    mirror2ndHalf(); // copy and mirror data from leds_temp to leds
    break;
  case 30:
    functionName = "Fire 3";
    gReverseDirection = true;
    FireHalfStrip(); // draw fire data to leds_temp

    mirror2ndHalf(); // copy and mirror data from leds_temp to leds
    break;
  }
}

// FUNCTIONS

//===============================================================
// Modified helper function that blends one uint8_t toward another,
// based on function from Mark Kriegsman's fadeTowardColor example:
// https://gist.github.com/kriegsman/d0a5ed3c8f38c64adcb4837dafb6e690
void nblendU8TowardU8(uint8_t &current, const uint8_t target)
{
  if (current == target)
  {
    return;
  }

  if (current < target)
  {
    uint8_t delta = target - current;
    delta = scale8_video(delta, 1);
    current += delta;
  }
  else
  {
    uint8_t delta = current - target;
    delta = scale8_video(delta, 1);
    current -= delta;
  }
}

void MovingColoredBars(int colorBarLength, long colorPallete[], int numberOfColors)
{
  //https://github.com/marmilicious/FastLED_examples/blob/master/moving_colored_bars.ino
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
  //https://github.com/marmilicious/FastLED_examples/blob/master/breath_effect_v2.ino
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

//Draw alternating bands of color, 2 or 3 colors.
//When using three colors, color1 is used between the other two colors.
void CandyCane(uint16_t ts, uint8_t numColors, uint8_t stripeLength, CRGB color1, CRGB color2, CRGB color3)
{
  //https://github.com/marmilicious/FastLED_examples/blob/master/candy_cane_stripes.ino

  // static uint8_t numColors = 3;    // Can be either 2 or 3
  // static uint8_t stripeLength = 5; //number of pixels per color
  int shiftBy = 1; //shiftBy can be positive or negative (to change direction)
  static int offset;
  const uint16_t travelSpeed = 150;

  EVERY_N_SECONDS(5)
  {
    numColors = 3;
    stripeLength = 4;
    // numColors = random8(2, 4);    //picks either 2 or 3
    // stripeLength = random8(3, 6); //picks random length
  }

  EVERY_N_MILLISECONDS(ts)
  {
    if (numColors == 2)
    {
      for (uint8_t i = 0; i < NUM_LEDS; i++)
      {
        if ((i + offset) % ((numColors)*stripeLength) < stripeLength)
        {
          leds[i] = color2;
        }
        else
        {
          leds[i] = color1;
        }
      }
    }

    if (numColors == 3)
    {
      for (uint8_t i = 0; i < NUM_LEDS; i++)
      {
        if ((i + offset) % ((numColors + 1) * stripeLength) < stripeLength)
        {
          leds[i] = color2;
        }
        else if ((i + offset + (2 * stripeLength)) % ((numColors + 1) * stripeLength) < stripeLength)
        {
          leds[i] = color3;
        }
        else
        {
          leds[i] = color1;
        }
      }
    }

    // FastLED.show();

    offset = offset + shiftBy;
    if (shiftBy > 0)
    { //for positive shiftBy
      if (offset >= NUM_LEDS)
        offset = 0;
    }
    else
    { //for negitive shiftBy
      if (offset < 0)
        offset = NUM_LEDS;
    }

  } //end EVERY_N
}

void BlendIntoRainbow(CRGB color1, CRGB color2, CRGB color3)
{
  //https://github.com/marmilicious/FastLED_examples/blob/master/blend_into_rainbow_v2.ino
  EVERY_N_MILLISECONDS(60)
  {
    hue++;
  }

  fill_rainbow(leds, NUM_LEDS, hue, 255 / NUM_LEDS / 4); // draw part of the rainbow into the strip
  fadeToBlackBy(leds, NUM_LEDS, 128);                    // fade the whole rainbow down some

  EVERY_N_MILLISECONDS(150)
  {
    if (moving)
    {
      pos++;
      if (pos == NUM_LEDS)
      {
        pos = 0;
      } // reset to begining
    }
  }

  EVERY_N_MILLISECONDS(5)
  {
    if (!moving)
    {
      hue2 = hue2 - 1;
    }
  }

  // colors to blend into background
  CRGB blendThisIn = CHSV(hue2, 140, 255);
  CRGB blendThisIn2 = CHSV(hue2, 170, 255);
  CRGB blendThisIn3 = CHSV(hue2, 210, 255);
  CRGB blendThisIn4 = CHSV(hue2, 255, 255);

  static uint8_t blendAmount = 128; // amount of blend  [range: 0-255]

  // https://www.reddit.com/r/FastLED/comments/dhoce6/nblend_function_explanation/
  // nblend (CRGB &existing, const CRGB &overlay, fract8 amountOfOverlay)
  nblend(leds[pos], blendThisIn4, blendAmount / 3);
  nblend(leds[mod8(pos + 1, NUM_LEDS)], blendThisIn3, blendAmount / 2);
  nblend(leds[mod8(pos + 2, NUM_LEDS)], blendThisIn2, blendAmount);
  nblend(leds[mod8(pos + 3, NUM_LEDS)], blendThisIn, blendAmount);
  nblend(leds[mod8(pos + 4, NUM_LEDS)], blendThisIn2, blendAmount);
  nblend(leds[mod8(pos + 5, NUM_LEDS)], blendThisIn3, blendAmount / 2);
  nblend(leds[mod8(pos + 6, NUM_LEDS)], blendThisIn4, blendAmount / 3);

  posR = beatsin8(5, 0, (NUM_LEDS - 1));
  posG = beatsin8(7, 0, (NUM_LEDS - 1));
  posB = beatsin8(9, 0, (NUM_LEDS - 1));

  CRGB tempColor = color1;
  temp[posR] = tempColor;
  tempColor = color2;
  nblend(temp[posG], tempColor, 128);
  tempColor = color3;
  nblend(temp[posB], tempColor, 128);

  EVERY_N_MILLISECONDS(2)
  {
    fadeToBlackBy(temp, NUM_LEDS, 1); // create fading tail effect
  }

  for (uint8_t i = 0; i < NUM_LEDS; i++)
  {
    nblend(leds[i], temp[i], 128);
  }

  nblend(leds[mod8(posR, NUM_LEDS)], color1, 90);
  nblend(leds[mod8(posR + 1, NUM_LEDS)], color1, 128);
  nblend(leds[mod8(posR + 2, NUM_LEDS)], color1, 90);

  nblend(leds[mod8(posG, NUM_LEDS)], color2, 90);
  nblend(leds[mod8(posG + 1, NUM_LEDS)], color2, 128);
  nblend(leds[mod8(posG + 2, NUM_LEDS)], color2, 90);

  nblend(leds[mod8(posB, NUM_LEDS)], color3, 90);
  nblend(leds[mod8(posB + 1, NUM_LEDS)], color3, 128);
  nblend(leds[mod8(posB + 2, NUM_LEDS)], color3, 90);
}

//===============================================================
// Heart Beat Functions
// https://github.com/marmilicious/FastLED_examples/blob/master/heart_pulse_blood_flowing.ino
void HeartBeat(uint8_t bloodHue, uint8_t bloodSat)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    uint8_t bloodVal = sumPulse((5 / NUM_LEDS / 2) + (NUM_LEDS / 2) * i * flowDirection);
    leds[i] = CHSV(bloodHue, bloodSat, bloodVal);
  }
}

int sumPulse(int time_shift)
{
  //time_shift = 0;  //Uncomment to heart beat/pulse all LEDs together
  int pulse1 = pulseWave8(millis() + time_shift, cycleLength, pulseLength);
  int pulse2 = pulseWave8(millis() + time_shift + pulseOffset, cycleLength, pulseLength);
  return qadd8(pulse1, pulse2); // Add pulses together without overflow
}

uint8_t pulseWave8(uint32_t ms, uint16_t cycleLength, uint16_t pulseLength)
{
  uint16_t T = ms % cycleLength;
  if (T > pulseLength)
    return baseBrightness;
  uint16_t halfPulse = pulseLength / 2;
  if (T <= halfPulse)
  {
    return (T * 255) / halfPulse; //first half = going up
  }
  else
  {
    return ((pulseLength - T) * 255) / halfPulse; //second half = going down
  }
}
//End_heart_beat_functions
//---------------------------------------------------------------

//---------------------------------------------------------------
// Fire Effect
// https://github.com/marmilicious/FastLED_examples/blob/master/mirrored_Fire2012.ino
void FireFullStrip()
{
  // Fuction only operates on half the number of pixels (NUM_LEDS/2)

  // Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
  for (int i = 0; i < NUM_LEDS; i++)
  {
    heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / (NUM_LEDS)) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for (int k = (NUM_LEDS)-1; k >= 2; k--)
  {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if (random8() < SPARKING)
  {
    int y = random8(7);
    heat[y] = qadd8(heat[y], random8(160, 255));
  }

  // Step 4.  Map from heat cells to LED colors
  for (int j = 0; j < NUM_LEDS; j++)
  {
    CRGB color = HeatColor(heat[j]);
    leds_temp[j] = color;
  }
}

void FireHalfStrip()
{
  // Fuction only operates on half the number of pixels (NUM_LEDS/2)

  // Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS / 2];

  // Step 1.  Cool down every cell a little
  for (int i = 0; i < NUM_LEDS / 2; i++)
  {
    heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / (NUM_LEDS / 2)) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for (int k = (NUM_LEDS / 2) - 1; k >= 2; k--)
  {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if (random8() < SPARKING)
  {
    int y = random8(7);
    heat[y] = qadd8(heat[y], random8(160, 255));
  }

  // Step 4.  Map from heat cells to LED colors
  for (int j = 0; j < NUM_LEDS / 2; j++)
  {
    CRGB color = HeatColor(heat[j]);
    leds_temp[j] = color;
  }
}

void mirror2ndHalf()
{
  //copy and mirror pixel data from leds_temp to leds array.

  if (gReverseDirection == false)
  { //false is center outward
    for (uint8_t i = 0; i < NUM_LEDS / 2; i++)
    {
      leds[(NUM_LEDS / 2) - 1 - i] = leds_temp[i];
      leds[(NUM_LEDS / 2) + i] = leds_temp[i];
    }
  }
  else
  { //true is from ends inward
    for (uint8_t i = 0; i < NUM_LEDS / 2; i++)
    {
      leds[i] = leds_temp[i];
      leds[(NUM_LEDS - 1) - i] = leds_temp[i];
    }
  }
}
// End Fire Effect
//---------------------------------------------------------------

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

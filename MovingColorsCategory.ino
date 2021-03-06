void moving_colors_category(int patternMode)
{
  globalStrings.categoryName = "MOVING COLORS";

  switch (patternMode)
  {
  case 0:
  {
    globalStrings.functionName = "Random";
  }
  break;
  case 1:
  {
    globalStrings.functionName = "MC 1";
    long pattern[] = {CRGB::Red, CRGB::Green, CRGB::Red};
    const int numberOfColors = sizeof(pattern) / sizeof(int);
    MovingColoredBars(NUM_LEDS / 2, pattern, numberOfColors);
  }
  break;
  case 2:
  {
    globalStrings.functionName = "MC 2";
    long pattern[] = {CRGB::Blue, CRGB::Blue, CRGB::Yellow, CRGB::Purple};
    const int numberOfColors = sizeof(pattern) / sizeof(int);
    MovingColoredBars(NUM_LEDS / numberOfColors, pattern, numberOfColors);
  }
  break;
  case 3:
  {
    globalStrings.functionName = "MC 2";
    long pattern[] = {CRGB::Purple, CRGB::Blue, CRGB::Teal, CRGB::Purple};
    const int numberOfColors = sizeof(pattern) / sizeof(int);
    MovingColoredBars(NUM_LEDS / numberOfColors, pattern, numberOfColors);
  }
  break;
  case 4:
    globalStrings.functionName = "Breathing 1";
    BreathingEffect(0.5, true, true, true);
    break;
  case 5:
    globalStrings.functionName = "Breathing 2";
    BreathingEffect(0.5, true, false, true);
    break;
  case 6:
    globalStrings.functionName = "Breathing 3";
    BreathingEffect(0.5, true, true, false);
    break;
  case 7:
    globalStrings.functionName = "Breathing 4";
    BreathingEffect(0.5, false, false, true);
    break;
  case 8:
    globalStrings.functionName = "Breathing 5";
    BreathingEffect(0.5, true, false, false);
    break;
  case 9:
    globalStrings.functionName = "Breathing 6";
    BreathingEffect(0.5, false, false, false);
    break;
  case 10:
    globalStrings.functionName = "Breathing 7";
    BreathingEffect(0.1, true, true, true);
    break;
  case 11:
    globalStrings.functionName = "Breathing 8";
    BreathingEffect(0.7, true, true, true);
    break;
  case 12:
    globalStrings.functionName = "Breathing 9";
    BreathingEffect(1, true, true, true);
    break;
  case 13:
    globalStrings.functionName = "Candy Cane 1";
    CandyCane(20, 3, 5, CRGB::White, CRGB::Red, CRGB::Blue);
    break;
  case 14:
    globalStrings.functionName = "Candy Cane 2";
    CandyCane(250, 3, 5, CRGB::Black, CRGB::Orange, CRGB::Green);
    break;
  case 15:
    globalStrings.functionName = "Candy Cane 3";
    CandyCane(200, 3, 5, CRGB::Yellow, CRGB::Green, CRGB::Purple);
    break;
  case 16:
    globalStrings.functionName = "Candy Cane 4";
    CandyCane(250, 3, 5, CRGB::Green, CRGB::Blue, CRGB::Teal);
    break;
  case 17:
    globalStrings.functionName = "Candy Cane 5";
    CandyCane(400, 3, 5, CRGB::Purple, CRGB::Blue, CRGB::White);
    break;
  case 18:
    globalStrings.functionName = "Blend 1";
    BlendIntoRainbow(CRGB::Purple, CRGB::Blue, CRGB::Green);
    break;
  case 19:
    globalStrings.functionName = "Blend 2";
    BlendIntoRainbow(CRGB::Red, CRGB::Blue, CRGB::White);
    break;
  case 20:
    globalStrings.functionName = "Blend 3";
    BlendIntoRainbow(CRGB::Purple, CRGB::Orange, CRGB::White);
    break;
  case 21:
    globalStrings.functionName = "Blend 4";
    BlendIntoRainbow(CRGB::Green, CRGB::Blue, CRGB::Yellow);
    break;
  case 22:
    globalStrings.functionName = "Blend 5";
    BlendIntoRainbow(CRGB::Orange, CRGB::Purple, CRGB::Blue);
    break;
  case 23:
    globalStrings.functionName = "Blend 6";
    BlendIntoRainbow(CRGB::Orange, CRGB::Purple, CRGB::Green);
    break;
  case 24:
    globalStrings.functionName = "Blend 7";
    BlendIntoRainbow(CRGB::Red, CRGB::Blue, CRGB::Green);
    break;
  case 25:
    globalStrings.functionName = "Blend 8";
    BlendIntoRainbow(CRGB::Blue, CRGB::Purple, CRGB::Yellow);
    break;
  case 26:
    globalStrings.functionName = "Blend 9";
    BlendIntoRainbow(CRGB::Purple, CRGB::Red, CRGB::Pink);
    break;
  case 27:
    globalStrings.functionName = "Blend 10";
    BlendIntoRainbow(CRGB::Red, CRGB::Orange, CRGB::Yellow);
    break;
  case 28:
    globalStrings.functionName = "Fire 1";
    FireHalfStrip(); // draw fire data to leds_temp

    mirror2ndHalf(); // copy and mirror data from leds_temp to leds
    break;
  case 29:
    globalStrings.functionName = "Fire 2";
    FireFullStrip(); // draw fire data to leds_temp

    mirror2ndHalf(); // copy and mirror data from leds_temp to leds
    break;
  case 30:
    globalStrings.functionName = "Fire 3";
    patternSettings.gReverseDirection = true;
    FireHalfStrip(); // draw fire data to leds_temp

    mirror2ndHalf(); // copy and mirror data from leds_temp to leds
    break;
  case 31:
    globalStrings.functionName = "RepeatingPattern 1";
    RepeatingPattern(100, 80, 5, 1000);
    break;
  case 32:
    globalStrings.functionName = "RepeatingPattern 2";
    RepeatingPattern(10, 120, 10, FRAMES_PER_SECOND);
    break;
  case 33:
    globalStrings.functionName = "RepeatingPattern 3";
    RepeatingPattern(200, 155, 20, 500);
    break;
  case 34:
    globalStrings.functionName = "BlockPattern 1";
    RepeatingBlockPattern(100, 80, 5, 0, 5);
    break;
  case 35:
    globalStrings.functionName = "BlockPattern 2";
    RepeatingBlockPattern(10, 120, 10, 20, 10);
    break;
  case 36:
    globalStrings.functionName = "BlockPattern 3";
    RepeatingBlockPattern(200, 155, 20, 40, 20);
    break;
  case 37:
    globalStrings.functionName = "Twinkle 1";
    Twinkle(8, 100, 50, 100, brightness.current, false);
    break;
  case 38:
    globalStrings.functionName = "Twinkle 2";
    Twinkle(8, 20, 125, 100, brightness.current, true);
    break;
  case 39:
    globalStrings.functionName = "Twinkle 3";
    Twinkle(16, 200, 200, 100, brightness.current, false);
    break;
  case 40:
    globalStrings.functionName = "Twinkle 4";
    Twinkle(32, 500, 70, 100, brightness.current, true);
    break;
  case 41:
    globalStrings.functionName = "Mover 1";
    Mover(10, 200);
    break;
  case 42:
    globalStrings.functionName = "Meteor 1";
    Meteor(255, 0, 255);
    break;
  case 43:
    globalStrings.functionName = "Marqueev2 2";
    Marqueev2(2, 250);
    break;
  case 44:
    globalStrings.functionName = "Marqueev2 4";
    Marqueev2(4, 250);
    break;
  case 45:
    globalStrings.functionName = "Marqueev2 7";
    Marqueev2(7, 250);
    break;
  case 46:
    globalStrings.functionName = "Marqueev2 10";
    Marqueev2(10, 250);
    break;
  case 47:
    globalStrings.functionName = "Marqueev3 2";
    Marqueev3(2, 250, 2, 20);
    break;
  case 48:
    globalStrings.functionName = "Marqueev3 4";
    Marqueev3(4, 250, 3, 40);
    break;
  case 49:
    globalStrings.functionName = "Marqueev3 7";
    Marqueev3(7, 250, 5, 80);
    break;
  case 50:
    globalStrings.functionName = "Marqueev3 10";
    Marqueev3(10, 250, 7, 100);
    break;
  case 51:
    globalStrings.functionName = "Sawtooth 60";
    Sawtooth(60, OceanColors_p, LINEARBLEND);
    break;
  case 52:
    globalStrings.functionName = "Sawtooth 92";
    Sawtooth(92, LavaColors_p, LINEARBLEND);
    break;
  case 53:
    globalStrings.functionName = "Sawtooth 110";
    Sawtooth(128, ForestColors_p, LINEARBLEND);
    break;
  case 54:
    globalStrings.functionName = "Plasma 1";
    Plasma(OceanColors_p, LavaColors_p, LINEARBLEND);
    break;
  case 55:
    globalStrings.functionName = "Plasma 2";
    Plasma(ForestColors_p, CloudColors_p, LINEARBLEND);
    break;
  case 56:
    globalStrings.functionName = "Plasma 3";
    Plasma(RainbowColors_p, PartyColors_p, LINEARBLEND);
    break;
  case 57:
    globalStrings.functionName = "Plasma 4";
    Plasma(PartyColors_p, LavaColors_p, LINEARBLEND);
    break;
  case 58:
    globalStrings.functionName = "Plasma 5";
    Plasma(HeatColors_p, LavaColors_p, LINEARBLEND);
    break;
  case 59:
    globalStrings.functionName = "Plasma 6";
    Plasma(CloudColors_p, PartyColors_p, LINEARBLEND);
    break;
  case 60:
    globalStrings.functionName = "Plasma 7";
    Plasma(ForestColors_p, pal_rasta_flag, LINEARBLEND);
    break;
  case 61:
    globalStrings.functionName = "Plasma 8";
    Plasma(ForestColors_p, pal_GreenYellowBlue, LINEARBLEND);
    break;
  case 62:
    globalStrings.functionName = "Plasma 9";
    Plasma(pal_Outrun, CloudColors_p, LINEARBLEND);
    break;
  case 63:
    globalStrings.functionName = "RainbowMarch 1";
    RainbowMarch(200, 10);
    break;
  case 64:
    globalStrings.functionName = "RainbowMarch 2";
    RainbowMarch(100, 10);
    break;
  case 65:
    globalStrings.functionName = "RainbowMarch 3";
    RainbowMarch(50, 100);
    break;
  case 66:
    globalStrings.functionName = "BlendWave 1";
    BlendWave(60, 10);
    break;
  case 67:
    globalStrings.functionName = "BlendWave 2";
    BlendWave(40, 20);
    break;
  case 68:
    globalStrings.functionName = "BlendWave 3";
    BlendWave(20, 20);
    break;
  case 69:
    globalStrings.functionName = "BeatWave 1";
    BeatWave(RainbowColors_p, PartyColors_p, LINEARBLEND);
    break;
  case 70:
    globalStrings.functionName = "BeatWave 2";
    BeatWave(OceanColors_p, LavaColors_p, LINEARBLEND);
    break;
  case 71:
    globalStrings.functionName = "BeatWave 3";
    BeatWave(ForestColors_p, CloudColors_p, LINEARBLEND);
    break;
  case 72:
    {
    globalStrings.functionName = "MC 0";
    long pattern[] = {CRGB::Green, CRGB::Grey, CRGB::Red, CRGB::Grey, CRGB::Red, CRGB::Grey, CRGB::Red, CRGB::Green, CRGB::Green, CRGB::Green};
    const int numberOfColors = sizeof(pattern) / sizeof(int); //Auto calculate your specified number of color bars
    MovingColoredBars(NUM_LEDS - 1, pattern, numberOfColors);
    }
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
      patternSettings.leds[x] = patternSettings.leds[x + 1];
    }
    if (globalLED.clearLEDS)
    {
      patternSettings.leds[NUM_LEDS - 1] = colorPallete[patternSettings.palletPosition];
    }
    if ((patternSettings.colorBarPosition <= colorBarLength) && !globalLED.clearLEDS)
    {
      patternSettings.leds[NUM_LEDS - 1] = colorPallete[patternSettings.palletPosition];
      patternSettings.colorBarPosition++;
    }
    if ((patternSettings.palletPosition == numberOfColors - 1) && (patternSettings.colorBarPosition > colorBarLength) && !globalLED.clearLEDS)
    {
      patternSettings.leds[NUM_LEDS - 1] = colorPallete[patternSettings.palletPosition];
      patternSettings.palletPosition = 0;
      patternSettings.colorBarPosition = 1;
      globalLED.clearLEDS = true;
    }
    if ((patternSettings.colorBarPosition > colorBarLength) && !globalLED.clearLEDS)
    {
      patternSettings.colorBarPosition = 1;
      patternSettings.palletPosition = patternSettings.palletPosition + 1;
    }
    //if (globalLED.clearLEDS && !leds(0,NUM_LEDS-1))  //Not using this for of test any more
    if (globalLED.clearLEDS && patternSettings.leds[0] == (CRGB)(colorPallete[numberOfColors - 1])) //restarts as soon as last color makes it past the end
    {
      //Serial.print( patternSettings.leds[0].r );  Serial.print("\t"), Serial.print( patternSettings.leds[0].g ); Serial.print("\t"), Serial.println( patternSettings.leds[0].b );  //Print out RGB colors it's triggering on
      globalLED.clearLEDS = false;
    }

  } //end_EVERY_N
}

void BreathingEffect(float pulseSpeed, bool red, bool green, bool blue)
{
  //https://github.com/marmilicious/FastLED_examples/blob/master/breath_effect_v2.ino
  float dV = ((exp(sin(pulseSpeed * millis() / 2000.0 * PI)) - 0.36787944) * patternSettings.delta);
  patternSettings.val = patternSettings.valueMin + dV;
  patternSettings.hue = map(patternSettings.val, patternSettings.valueMin, patternSettings.valueMax, patternSettings.hueA, patternSettings.hueB); // Map hue based on current val
  patternSettings.sat = map(patternSettings.val, patternSettings.valueMin, patternSettings.valueMax, patternSettings.satA, patternSettings.satB); // Map sat based on current val

  for (int i = 0; i < NUM_LEDS; i++)
  {
    patternSettings.leds[i] = CHSV(patternSettings.hue, patternSettings.sat, patternSettings.val);

    // You can experiment with commenting out these dim8_video lines
    // to get a different sort of look.
    if (red)
    {
      patternSettings.leds[i].r = dim8_video(patternSettings.leds[i].r);
    }
    if (green)
    {

      patternSettings.leds[i].g = dim8_video(patternSettings.leds[i].g);
    }
    if (blue)
    {

      patternSettings.leds[i].b = dim8_video(patternSettings.leds[i].b);
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
      for (int i = 0; i < NUM_LEDS; i++)
      {
        if ((i + offset) % ((numColors)*stripeLength) < stripeLength)
        {
          patternSettings.leds[i] = color2;
        }
        else
        {
          patternSettings.leds[i] = color1;
        }
      }
    }

    if (numColors == 3)
    {
      for (int i = 0; i < NUM_LEDS; i++)
      {
        if ((i + offset) % ((numColors + 1) * stripeLength) < stripeLength)
        {
          patternSettings.leds[i] = color2;
        }
        else if ((i + offset + (2 * stripeLength)) % ((numColors + 1) * stripeLength) < stripeLength)
        {
          patternSettings.leds[i] = color3;
        }
        else
        {
          patternSettings.leds[i] = color1;
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
    patternSettings.hue++;
  }

  fill_rainbow(patternSettings.leds, NUM_LEDS, patternSettings.hue, 255 / NUM_LEDS / 4); // draw part of the rainbow into the strip
  fadeToBlackBy(patternSettings.leds, NUM_LEDS, 128);                                    // fade the whole rainbow down some

  EVERY_N_MILLISECONDS(150)
  {
    if (patternSettings.moving)
    {
      patternSettings.pos++;
      if (patternSettings.pos == NUM_LEDS)
      {
        patternSettings.pos = 0;
      } // reset to begining
    }
  }

  EVERY_N_MILLISECONDS(5)
  {
    if (!patternSettings.moving)
    {
      patternSettings.hue2 = patternSettings.hue2 - 1;
    }
  }

  // colors to blend into background
  CRGB blendThisIn = CHSV(patternSettings.hue2, 140, 255);
  CRGB blendThisIn2 = CHSV(patternSettings.hue2, 170, 255);
  CRGB blendThisIn3 = CHSV(patternSettings.hue2, 210, 255);
  CRGB blendThisIn4 = CHSV(patternSettings.hue2, 255, 255);

  static uint8_t blendAmount = 128; // amount of blend  [range: 0-255]

  // https://www.reddit.com/r/FastLED/comments/dhoce6/nblend_function_explanation/
  // nblend (CRGB &existing, const CRGB &overlay, fract8 amountOfOverlay)
  nblend(patternSettings.leds[patternSettings.pos], blendThisIn4, blendAmount / 3);
  nblend(patternSettings.leds[mod8(patternSettings.pos + 1, NUM_LEDS)], blendThisIn3, blendAmount / 2);
  nblend(patternSettings.leds[mod8(patternSettings.pos + 2, NUM_LEDS)], blendThisIn2, blendAmount);
  nblend(patternSettings.leds[mod8(patternSettings.pos + 3, NUM_LEDS)], blendThisIn, blendAmount);
  nblend(patternSettings.leds[mod8(patternSettings.pos + 4, NUM_LEDS)], blendThisIn2, blendAmount);
  nblend(patternSettings.leds[mod8(patternSettings.pos + 5, NUM_LEDS)], blendThisIn3, blendAmount / 2);
  nblend(patternSettings.leds[mod8(patternSettings.pos + 6, NUM_LEDS)], blendThisIn4, blendAmount / 3);

  patternSettings.posR = beatsin8(5, 0, (NUM_LEDS - 1));
  patternSettings.posG = beatsin8(7, 0, (NUM_LEDS - 1));
  patternSettings.posB = beatsin8(9, 0, (NUM_LEDS - 1));

  CRGB tempColor = color1;
  patternSettings.tempPatternCollection[patternSettings.posR] = tempColor;
  tempColor = color2;
  nblend(patternSettings.tempPatternCollection[patternSettings.posG], tempColor, 128);
  tempColor = color3;
  nblend(patternSettings.tempPatternCollection[patternSettings.posB], tempColor, 128);

  EVERY_N_MILLISECONDS(2)
  {
    fadeToBlackBy(patternSettings.tempPatternCollection, NUM_LEDS, 1); // create fading tail effect
  }

  for (int i = 0; i < NUM_LEDS; i++)
  {
    nblend(patternSettings.leds[i], patternSettings.tempPatternCollection[i], 128);
  }

  nblend(patternSettings.leds[mod8(patternSettings.posR, NUM_LEDS)], color1, 90);
  nblend(patternSettings.leds[mod8(patternSettings.posR + 1, NUM_LEDS)], color1, 128);
  nblend(patternSettings.leds[mod8(patternSettings.posR + 2, NUM_LEDS)], color1, 90);

  nblend(patternSettings.leds[mod8(patternSettings.posG, NUM_LEDS)], color2, 90);
  nblend(patternSettings.leds[mod8(patternSettings.posG + 1, NUM_LEDS)], color2, 128);
  nblend(patternSettings.leds[mod8(patternSettings.posG + 2, NUM_LEDS)], color2, 90);

  nblend(patternSettings.leds[mod8(patternSettings.posB, NUM_LEDS)], color3, 90);
  nblend(patternSettings.leds[mod8(patternSettings.posB + 1, NUM_LEDS)], color3, 128);
  nblend(patternSettings.leds[mod8(patternSettings.posB + 2, NUM_LEDS)], color3, 90);
}

//===============================================================
// Heart Beat Functions
// https://github.com/marmilicious/FastLED_examples/blob/master/heart_pulse_blood_flowing.ino
void HeartBeat(uint8_t bloodHue, uint8_t bloodSat)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    uint8_t bloodVal = sumPulse((5 / NUM_LEDS / 2) + (NUM_LEDS / 2) * i * patternSettings.flowDirection);
    //uint8_t bloodVal = sumPulse(1);
    patternSettings.leds[i] = CHSV(bloodHue, bloodSat, bloodVal);
  }
}

int sumPulse(uint8_t time_shift)
{
  //time_shift = 0;  //Uncomment to heart beat/pulse all LEDs together
  uint8_t pulse1 = 1; //pulseWave8(millis() + time_shift, patternSettings.cycleLength, patternSettings.pulseLength);
  uint8_t pulse2 = 1; //pulseWave8(millis() + time_shift + patternSettings.pulseOffset, patternSettings.cycleLength, patternSettings.pulseLength);
  return qadd8(pulse1, pulse2); // Add pulses together without overflow
}

//This function is having some trouble now. Getting divide by 0 error, commenting out this for now. 
uint8_t pulseWave8(uint32_t ms, uint16_t cycleLength, uint16_t pulseLength)
{
  uint16_t T = ms % cycleLength;
  if (T > pulseLength)
    return brightness.baseBrightness;
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
  static byte heat[MAX_LEDS];

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
    patternSettings.tempLeds[j] = color;
  }
}

void FireHalfStrip()
{
  // Fuction only operates on half the number of pixels (NUM_LEDS/2)

  // Array of temperature readings at each simulation cell
  static byte heat[MAX_LEDS / 2];

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
    patternSettings.tempLeds[j] = color;
  }
}

void mirror2ndHalf()
{
  //copy and mirror pixel data from patternSettings.leds_temp to leds array.

  if (patternSettings.gReverseDirection == false)
  { //false is center outward
    for (int i = 0; i < NUM_LEDS / 2; i++)
    {
      patternSettings.leds[(NUM_LEDS / 2) - 1 - i] = patternSettings.tempLeds[i];
      patternSettings.leds[(NUM_LEDS / 2) + i] = patternSettings.tempLeds[i];
    }
  }
  else
  { //true is from ends inward
    for (int i = 0; i < NUM_LEDS / 2; i++)
    {
      patternSettings.leds[i] = patternSettings.tempLeds[i];
      patternSettings.leds[(NUM_LEDS - 1) - i] = patternSettings.tempLeds[i];
    }
  }
}
// End Fire Effect
//---------------------------------------------------------------

void RepeatingPattern(uint8_t hue, uint8_t saturation, uint16_t repeatEvery, uint8_t interval)
{
  // https://github.com/marmilicious/FastLED_examples/blob/master/repeating_pattern.ino
  static uint16_t numberOfRepeats = NUM_LEDS / repeatEvery;

  EVERY_N_MILLISECONDS(50)
  {
    fadeToBlackBy(patternSettings.leds, NUM_LEDS, 1); // slowly fade out pixels
  }

  EVERY_N_MILLISECONDS(interval)
  {
    static uint8_t offset;
    static uint8_t shift;

    patternSettings.hue = ((255 / repeatEvery) * offset) + shift; // Change the hue for each pixel set.
    // patternSettings.hue = (20 * offset) + shift; // Change the hue for each pixel set.

    for (uint16_t x = 0; x < numberOfRepeats + 1; x++)
    {
      static uint16_t i;
      i = (repeatEvery * (x - 1)) + repeatEvery + offset; // The pixel number to draw
      if (i < NUM_LEDS)
      { // Only draw pixel numbers within NUM_LEDS
        patternSettings.leds[i] = CHSV(patternSettings.hue, saturation, 255);
      }
    }

    offset++;
    if (offset == repeatEvery)
    {
      offset = 0;
      shift = shift + random8(55, 77);
    }

  } //end_every_n
}

void RepeatingBlockPattern(uint8_t hue, uint8_t saturation, uint8_t blockSize, uint16_t loopStart, uint16_t loopEnd)
{
  // https://github.com/marmilicious/FastLED_examples/blob/master/repeating_block_pattern.ino
  loopStart = patternSettings.count * blockSize;
  loopEnd = blockSize + patternSettings.count * blockSize;

  // Trying to write data to pixels that don't exit is bad.
  // Check to make sure we are still within our NUM_LEDS range
  // and clamp to NUM_LEDS if needed.
  if (loopEnd > NUM_LEDS)
  {
    loopEnd = NUM_LEDS; // limit maximum to NUM_LEDS
  }

  patternSettings.hue = patternSettings.hue + random8(8, 17); // for fun, pick a new color for each block

  EVERY_N_MILLISECONDS(250)
  {
    for (uint16_t i = loopStart; i < loopEnd; i++)
    {
      patternSettings.leds[i] = CHSV(patternSettings.hue, saturation, 255);
    }

    //FastLED.show();

    for (uint16_t i = loopStart; i < loopEnd; i++)
    {
      patternSettings.leds[i].fadeToBlackBy(220); // fade down
    }

    patternSettings.count++; // increase count by one

    // reset count if we have come to the end of the strip
    if ((patternSettings.count * blockSize) >= NUM_LEDS)
    {
      patternSettings.count = 0;
      // Only change the block size when starting over on the strip
      // and after the minimum time has passed (from timer below).
      if (patternSettings.sizeUpdate)
      {
        blockSize = random8(2, 9); // for fun, pick a new random block size
        patternSettings.sizeUpdate = false;
      }
    }

  } //end_every_n

  EVERY_N_SECONDS(5)
  {
    patternSettings.sizeUpdate = true; // trigger size update
  }
}

void Twinkle(uint8_t thisfade, int twinkrate, uint8_t thishue, uint8_t thissat, uint8_t thisbri, bool randhue)
{
  // https://forum.makerforums.info/t/still-a-newbie-with-newbie-questions/64143/2
  if (twinkrate < NUM_LEDS)
  {
    twinkrate = NUM_LEDS; // Makes sure the twinkrate will cover ALL of the LED’s as it’s used as the maximum LED index value.
  }
  int i = random16(twinkrate); // A random number based on twinkrate. Higher number => fewer twinkles.
  if (randhue)
  {
    patternSettings.hue = random16(0, 255); // Randomize every LED if TRUE
  }
  if (i < NUM_LEDS)
  {
    patternSettings.leds[i] = CHSV(thishue, thissat, thisbri); // Only the lowest probability twinkles will do. You could even randomize the hue/saturation.
  }
  for (int j = 0; j < NUM_LEDS; j++)
  {
    patternSettings.leds[j].fadeToBlackBy(thisfade); // Use the FastLED fade method.
  }
}

void BouncingBalls(byte red, byte green, byte blue, int BallCount)
{
  // https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/#LEDStripEffectBouncingBalls
  float Gravity = -9.81;
  int StartHeight = 1;

  float Height[BallCount];
  float ImpactVelocityStart = sqrt(-2 * Gravity * StartHeight);
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int Position[BallCount];
  long ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];

  for (int i = 0; i < BallCount; i++)
  {
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i) / pow(BallCount, 2);
  }

  while (true)
  {
    for (int i = 0; i < BallCount; i++)
    {
      TimeSinceLastBounce[i] = millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow(TimeSinceLastBounce[i] / 1000, 2.0) + ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;

      if (Height[i] < 0)
      {
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();

        if (ImpactVelocity[i] < 0.01)
        {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round(Height[i] * (NUM_LEDS - 1) / StartHeight);
    }

    for (int i = 0; i < BallCount; i++)
    {
      setPixel(Position[i], red, green, blue);
    }

    showStrip();
    setAll(0, 0, 0);
  }
}

void BouncingColoredBalls(int BallCount, byte colors[][3])
{
  // https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/#LEDStripEffectBouncingBalls
  float Gravity = -9.81;
  int StartHeight = 1;

  float Height[BallCount];
  float ImpactVelocityStart = sqrt(-2 * Gravity * StartHeight);
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int Position[BallCount];
  long ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];

  for (int i = 0; i < BallCount; i++)
  {
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i) / pow(BallCount, 2);
  }

  while (true)
  {
    for (int i = 0; i < BallCount; i++)
    {
      TimeSinceLastBounce[i] = millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow(TimeSinceLastBounce[i] / 1000, 2.0) + ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;

      if (Height[i] < 0)
      {
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();

        if (ImpactVelocity[i] < 0.01)
        {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round(Height[i] * (NUM_LEDS - 1) / StartHeight);
    }

    for (int i = 0; i < BallCount; i++)
    {
      setPixel(Position[i], colors[i][0], colors[i][1], colors[i][2]);
    }

    showStrip();
    setAll(0, 0, 0);
  }
}

void Mover(uint8_t thisfade, uint8_t hue)
{
  // https://forum.makerforums.info/t/still-a-newbie-with-newbie-questions/64143/2

  globalTime.currentMillis = millis();
  // if (globalTime.currentMillis - globalTime.startMillis >= globalTime.period)
  if (globalTime.currentMillis - globalTime.startMillis >= beatsin8(15, 25, 100))
  {
    globalTime.startMillis = globalTime.currentMillis;
    patternSettings.leds[globalLED.pixelNumber] += CHSV(patternSettings.hue, 255, 255);
    patternSettings.leds[(globalLED.pixelNumber + 5) % NUM_LEDS] += CHSV(patternSettings.hue + 85, 255, 255);   // We use modulus so that the location is between 0 and NUM_LEDS
    patternSettings.leds[(globalLED.pixelNumber + 10) % NUM_LEDS] += CHSV(patternSettings.hue + 170, 255, 255); // Same here.
    fadeToBlackBy(patternSettings.leds, NUM_LEDS, thisfade);                                                    // Low values = slower fade.

    if (++globalLED.pixelNumber >= NUM_LEDS)
    {
      globalLED.pixelNumber = 0;
    }
  }
}

void RunningLights(uint8_t red, uint8_t green, uint8_t blue, int WaveDelay)
{
  int Position = 0;

  for (int j = 0; j < NUM_LEDS * 2; j++)
  {
    Position++; // = 0; //Position + Rate;
    for (int i = 0; i < NUM_LEDS; i++)
    {
      // sine wave, 3 offset waves make a rainbow!
      //float level = sin(i+Position) * 127 + 128;
      //setPixel(i,level,0,0);
      //float level = sin(i+Position) * 127 + 128;
      setPixel(i, ((sin(i + Position) * 127 + 128) / 255) * red,
               ((sin(i + Position) * 127 + 128) / 255) * green,
               ((sin(i + Position) * 127 + 128) / 255) * blue);
    }

    showStrip();
    delay(WaveDelay);
  }
}

void RunningLights2Colors(byte red1, byte green1, byte blue1, byte red2, byte green2, byte blue2, int WaveDelay)
{
  int Position = 0;

  for (int j = 0; j < NUM_LEDS * 2; j = j + 2)
  {
    Position++; // = 0; //Position + Rate;
    for (int i = 0; i < NUM_LEDS; i++)
    {
      setPixel(i, ((sin(i + Position) * 127 + 128) / 255) * red1,
               ((sin(i + Position) * 127 + 128) / 255) * green1,
               ((sin(i + Position) * 127 + 128) / 255) * blue1);
      setPixel(i + 1, ((sin(i + Position) * 127 + 128) / 255) * red2,
               ((sin(i + Position) * 127 + 128) / 255) * green2,
               ((sin(i + Position) * 127 + 128) / 255) * blue2);
    }

    showStrip();
    delay(WaveDelay);
  }
}

void MeteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay)
{

  setAll(0, 0, 0);
  for (int i = 0; i < NUM_LEDS + NUM_LEDS; i++)
  {

    // fade brightness.current all LEDs one step
    for (int j = 0; j < NUM_LEDS; j++)
    {
      if ((!meteorRandomDecay) || (random(10) > 5))
      {
        fadeToBlack(j, meteorTrailDecay);
      }
    }

    // draw meteor
    for (int j = 0; j < meteorSize; j++)
    {
      if ((globalLED.pixelNumber - j < NUM_LEDS) && (globalLED.pixelNumber - j >= 0))
      {
        setPixel(globalLED.pixelNumber - j, red, green, blue);
      }
    }

    showStrip();
    delay(SpeedDelay);
  }
}

void Meteor(uint8_t red, uint8_t green, uint8_t blue)
{
  // https://www.reddit.com/r/FastLED/comments/gbhpcq/meteor_sketches_with_millis/
  globalTime.currentMillis = millis();
  if (globalTime.currentMillis - globalTime.startMillis >= beatsin8(15, 25, 100))
  {
    globalTime.startMillis = globalTime.currentMillis;

    patternSettings.leds[globalLED.pixelNumber] = CRGB(red, green, blue);
    blur1d(patternSettings.leds, NUM_LEDS, beatsin8(7, 20, 80));

    FastLED.show();
    patternSettings.leds[globalLED.pixelNumber] = CRGB::Black;
    if (++globalLED.pixelNumber >= NUM_LEDS)
    {
      globalLED.pixelNumber = 0;
    }
  }
}

void Marqueev2(uint8_t spacing, uint16_t holdTime)
{
  // https://github.com/marmilicious/FastLED_examples/blob/master/marquee_v2.ino
  EVERY_N_SECONDS(40)
  { // Change direction every N seconds.
    patternSettings.delta2 = -1 * patternSettings.delta2;
  }
  EVERY_N_SECONDS(40)
  { // Change direction every N seconds.
    patternSettings.delta2 = -1 * patternSettings.delta2;
  }

  EVERY_N_SECONDS(10)
  { // Demo changing the pixel spacing every N seconds.
    spacing = spacing + 1;
    if (spacing == 9)
    {
      spacing = 2;
    } // Reset spacing to 2
    if (spacing > 4)
    {
      spacing = 8;
    }                                                            // Jump spacing up to 8
    patternSettings.hue = patternSettings.hue + random8(30, 61); // Shift the hue to something new.
  }

  EVERY_N_MILLISECONDS(holdTime)
  {
    // holdTime = Milliseconds to hold position before advancing
    // Advance pixels to next position.

    for (int i = 0; i < (NUM_LEDS / spacing); i++)
    {
      patternSettings.pos = (spacing * (i - 1) + spacing + patternSettings.advance) % NUM_LEDS;
      patternSettings.leds[patternSettings.pos] = CHSV(patternSettings.hue, 255, 255);
    }

    //FastLED.show();

    // Fade out tail or set back to black for next loop around.
    if (patternSettings.fadingTail == true)
    {
      fadeToBlackBy(patternSettings.leds, NUM_LEDS, patternSettings.fadeRate);
    }
    else
    {
      for (int i = 0; i < (NUM_LEDS / spacing); i++)
      {
        patternSettings.pos = (spacing * (i - 1) + spacing + patternSettings.advance) % NUM_LEDS;
        patternSettings.leds[patternSettings.pos] = CRGB::Black;
      }
    }

    // Advance pixel postion down strip, and rollover if needed.
    patternSettings.advance = (patternSettings.advance + patternSettings.delta2 + NUM_LEDS) % NUM_LEDS;
  }
}

void Marqueev3(uint8_t spacing, uint16_t holdTime, uint8_t width, uint8_t hue2Shift)
{
  //https: //github.com/marmilicious/FastLED_examples/blob/master/marquee_v3.ino
  EVERY_N_SECONDS(10)
  { // Demo: Change direction every N seconds.
    patternSettings.delta2 = -1 * patternSettings.delta2;
  }

  //EVERY_N_SECONDS(10){  // Demo: Changing the pixel spacing every N seconds.
  //  spacing = spacing + 1;
  //  if (spacing == 9) { spacing = 2; }  // Reset spacing to 2
  //  if (spacing >4) { spacing = 8; }  // Jump spacing up to 8
  //}

  EVERY_N_SECONDS(10)
  {                                                              // Demo: Change the hue every N seconds.
    patternSettings.hue = patternSettings.hue + random8(30, 61); // Shift the hue to something new.
  }

  EVERY_N_MILLISECONDS(holdTime)
  { // Advance pixels to next position.

    // Advance pixel postion down strip, and rollover if needed.
    patternSettings.advance = (patternSettings.advance + patternSettings.delta2 + NUM_LEDS) % NUM_LEDS;

    // Fade out tail or set back to black for next loop around.
    if (patternSettings.fadingTail == true)
    {
      fadeToBlackBy(patternSettings.leds, NUM_LEDS, patternSettings.fadeRate);
    }
    else
    {
      for (int i = 0; i < (NUM_LEDS / spacing); i++)
      {
        for (uint8_t w = 0; w < width; w++)
        {
          //patternSettings.pos = (spacing * (i-1) + spacing + patternSettings.advance + w) % NUM_LEDS;
          patternSettings.pos = (spacing * (i - 1) + spacing + patternSettings.advance + w - 1) % NUM_LEDS;
          patternSettings.leds[patternSettings.pos] = CRGB::Black;
        }
      }
    }

    // Update pixels down the strip.
    for (int i = 0; i < (NUM_LEDS / spacing); i++)
    {
      for (uint8_t w = 0; w < width; w++)
      {
        patternSettings.pos = (spacing * (i - 1) + spacing + patternSettings.advance + w) % NUM_LEDS;
        if (w % 2 == 0)
        { // Is w even or odd?
          patternSettings.colorStorage = patternSettings.hue;
        }
        else
        {
          patternSettings.colorStorage = patternSettings.hue + hue2Shift;
        }

        patternSettings.leds[patternSettings.pos] = CHSV(patternSettings.colorStorage, 255, 255);
      }
    }

    //FastLED.show();

  } //end_every_n
}

void Sawtooth(int bpm, CRGBPalette16 currentPalette, TBlendType currentBlending)
{

  // https://github.com/atuline/FastLED-Demos/blob/master/sawtooth/sawtooth.ino
  int ms_per_beat = 60000 / bpm; // 500ms per beat, where 60,000 = 60 seconds * 1000 ms
  int ms_per_led = 60000 / bpm / NUM_LEDS;

  int cur_led = ((millis() % ms_per_beat) / ms_per_led) % (NUM_LEDS); // Using millis to count up the strand, with %NUM_LEDS at the end as a safety factor.

  if (cur_led == 0)
    fill_solid(patternSettings.leds, NUM_LEDS, CRGB::Black);
  else
    patternSettings.leds[cur_led] = ColorFromPalette(currentPalette, 0, 255, currentBlending); // I prefer to use palettes instead of CHSV or CRGB assignments.
}

void Plasma(CRGBPalette16 currentPalette, CRGBPalette16 targetPalette, TBlendType currentBlending)
{
  //https://github.com/atuline/FastLED-Demos/blob/master/plasma/plasma.ino
  EVERY_N_MILLISECONDS(50)
  { // FastLED based non-blocking delay to update/display the sequence.
    plasma(currentPalette, currentBlending);
  }

  EVERY_N_MILLISECONDS(100)
  {
    uint8_t maxChanges = 24;
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges); // AWESOME palette blending capability.
  }

  EVERY_N_SECONDS(5)
  {                            // Change the target palette to a random one every 5 seconds.
    uint8_t baseC = random8(); // You can use this as a baseline colour if you want similar hues in the next line.
    targetPalette = CRGBPalette16(CHSV(baseC + random8(32), 192, random8(128, 255)), CHSV(baseC + random8(32), 255, random8(128, 255)), CHSV(baseC + random8(32), 192, random8(128, 255)), CHSV(baseC + random8(32), 255, random8(128, 255)));
  }
}

void RainbowMarch(uint8_t thisdelay, uint8_t deltahue)
{ // The fill_rainbow call doesn't support brightness levels.

  uint8_t thishue = millis() * (255 - thisdelay) / 255; // To change the rate, add a beat or something to the result. 'thisdelay' must be a fixed value.

  // thishue = beat8(50);                                       // This uses a FastLED sawtooth generator. Again, the '50' should not change on the fly.
  // thishue = beatsin8(50,0,255);                              // This can change speeds on the fly. You can also add these to each other.

  fill_rainbow(patternSettings.leds, NUM_LEDS, thishue, deltahue); // Use FastLED's fill_rainbow routine.
}

void BeatWave(CRGBPalette16 currentPalette, CRGBPalette16 targetPalette, TBlendType currentBlending)
{
  // https://github.com/atuline/FastLED-Demos/blob/master/beatwave/beatwave.ino
  beatwave(currentPalette, currentBlending);

  EVERY_N_MILLISECONDS(100)
  {
    uint8_t maxChanges = 24;
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges); // AWESOME palette blending capability.
  }

  EVERY_N_SECONDS(5)
  { // Change the target palette to a random one every 5 seconds.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)), CHSV(random8(), 192, random8(128, 255)), CHSV(random8(), 255, random8(128, 255)));
  }
}

void BlendWave(accum88 bpm, accum88 bpm2)
{
  // https://github.com/atuline/FastLED-Demos/blob/master/blendwave/blendwave.ino
  patternSettings.speed = beatsin8(bpm, 0, 255);

  globals.clr1 = blend(CHSV(beatsin8(3, 0, 255), 255, 255), CHSV(beatsin8(4, 0, 255), 255, 255), patternSettings.speed);
  globals.clr2 = blend(CHSV(beatsin8(4, 0, 255), 255, 255), CHSV(beatsin8(3, 0, 255), 255, 255), patternSettings.speed);

  patternSettings.loc1 = beatsin8(bpm2, 0, NUM_LEDS - 1);

  fill_gradient_RGB(patternSettings.leds, 0, globals.clr2, patternSettings.loc1, globals.clr1);
  fill_gradient_RGB(patternSettings.leds, patternSettings.loc1, globals.clr2, NUM_LEDS - 1, globals.clr1);
}

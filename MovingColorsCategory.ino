void moving_colors_category(int patternMode)
{
  globalStrings.categoryName = "MOVING COLORS";

  switch (patternMode)
  {
  case 0:
  {
    globalStrings.functionName = "MC 0";
    long pattern[] = {CRGB::Green, CRGB::Grey, CRGB::Red, CRGB::Grey, CRGB::Red, CRGB::Grey, CRGB::Red, CRGB::Green, CRGB::Green, CRGB::Green};
    const int numberOfColors = sizeof(pattern) / sizeof(int); //Auto calculate your specified number of color bars
    MovingColoredBars(NUM_LEDS - 1, pattern, numberOfColors);
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
    globalStrings.functionName = "Blend Rainbow 1";
    BlendIntoRainbow(CRGB::Purple, CRGB::Blue, CRGB::Green);
    break;
  case 19:
    globalStrings.functionName = "Blend Rainbow 2";
    BlendIntoRainbow(CRGB::Red, CRGB::Blue, CRGB::White);
    break;
  case 20:
    globalStrings.functionName = "Blend Rainbow 3";
    BlendIntoRainbow(CRGB::Purple, CRGB::Orange, CRGB::White);
    break;
  case 21:
    globalStrings.functionName = "Blend Rainbow 4";
    BlendIntoRainbow(CRGB::Green, CRGB::Blue, CRGB::Yellow);
    break;
  case 22:
    globalStrings.functionName = "Blend Rainbow 5";
    BlendIntoRainbow(CRGB::Orange, CRGB::Purple, CRGB::Green);
    break;
  case 23:
    globalStrings.functionName = "HeartBeat 1";
    HeartBeat(100, 255);
    break;
  case 24:
    globalStrings.functionName = "HeartBeat 2";
    HeartBeat(20, 255);
    break;
  case 25:
    globalStrings.functionName = "HeartBeat 3";
    HeartBeat(155, 255);
    break;
  case 26:
    globalStrings.functionName = "HeartBeat 4";
    HeartBeat(75, 255);
    break;
  case 27:
    globalStrings.functionName = "HeartBeat 5";
    HeartBeat(225, 255);
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
    globalStrings.functionName = "RepeatingBlockPattern 1";
    RepeatingBlockPattern(100, 80, 5, 0, 5);
    break;
  case 35:
    globalStrings.functionName = "RepeatingBlockPattern 2";
    RepeatingBlockPattern(10, 120, 10, 20, 10);
    break;
  case 36:
    globalStrings.functionName = "RepeatingBlockPattern 3";
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
    globalStrings.functionName = "RainbowMarch 1";
    RainbowMarch(200, 10);
    break;
  case 58:
    globalStrings.functionName = "RainbowMarch 2";
    RainbowMarch(100, 10);
    break;
  case 59:
    globalStrings.functionName = "RainbowMarch 3";
    RainbowMarch(50, 100);
    break;
  case 60:
    globalStrings.functionName = "BlendWave 1";
    BlendWave(60, 10);
    break;
  case 61:
    globalStrings.functionName = "BlendWave 2";
    BlendWave(40, 20);
    break;
  case 62:
    globalStrings.functionName = "BlendWave 3";
    BlendWave(20, 20);
    break;
  case 63:
    globalStrings.functionName = "BeatWave 1";
    BeatWave(RainbowColors_p, PartyColors_p, LINEARBLEND);
    break;
  case 64:
    globalStrings.functionName = "BeatWave 2";
    BeatWave(OceanColors_p, LavaColors_p, LINEARBLEND);
    break;
  case 65:
    globalStrings.functionName = "BeatWave 3";
    BeatWave(ForestColors_p, CloudColors_p, LINEARBLEND);
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
      for (int i = 0; i < NUM_LEDS; i++)
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
      for (int i = 0; i < NUM_LEDS; i++)
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

  for (int i = 0; i < NUM_LEDS; i++)
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
    uint8_t bloodVal = sumPulse((5 / NUM_LEDS / 2) + (NUM_LEDS / 2) * i * patternSettings.flowDirection);
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

  if (patternSettings.gReverseDirection == false)
  { //false is center outward
    for (int i = 0; i < NUM_LEDS / 2; i++)
    {
      leds[(NUM_LEDS / 2) - 1 - i] = leds_temp[i];
      leds[(NUM_LEDS / 2) + i] = leds_temp[i];
    }
  }
  else
  { //true is from ends inward
    for (int i = 0; i < NUM_LEDS / 2; i++)
    {
      leds[i] = leds_temp[i];
      leds[(NUM_LEDS - 1) - i] = leds_temp[i];
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
    fadeToBlackBy(leds, NUM_LEDS, 1); // slowly fade out pixels
  }

  EVERY_N_MILLISECONDS(interval)
  {
    static uint8_t offset;
    static uint8_t shift;

    hue = ((255 / repeatEvery) * offset) + shift; // Change the hue for each pixel set.
    // hue = (20 * offset) + shift; // Change the hue for each pixel set.

    for (uint16_t x = 0; x < numberOfRepeats + 1; x++)
    {
      static uint16_t i;
      i = (repeatEvery * (x - 1)) + repeatEvery + offset; // The pixel number to draw
      if (i < NUM_LEDS)
      { // Only draw pixel numbers within NUM_LEDS
        leds[i] = CHSV(hue, saturation, 255);
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
  loopStart = count * blockSize;
  loopEnd = blockSize + count * blockSize;

  // Trying to write data to pixels that don't exit is bad.
  // Check to make sure we are still within our NUM_LEDS range
  // and clamp to NUM_LEDS if needed.
  if (loopEnd > NUM_LEDS)
  {
    loopEnd = NUM_LEDS; // limit maximum to NUM_LEDS
  }

  hue = hue + random8(8, 17); // for fun, pick a new color for each block

  EVERY_N_MILLISECONDS(250)
  {
    for (uint16_t i = loopStart; i < loopEnd; i++)
    {
      leds[i] = CHSV(hue, saturation, 255);
    }

    FastLED.show();

    for (uint16_t i = loopStart; i < loopEnd; i++)
    {
      leds[i].fadeToBlackBy(220); // fade down
    }

    count++; // increase count by one

    // reset count if we have come to the end of the strip
    if ((count * blockSize) >= NUM_LEDS)
    {
      count = 0;
      // Only change the block size when starting over on the strip
      // and after the minimum time has passed (from timer below).
      if (sizeUpdate)
      {
        blockSize = random8(2, 9); // for fun, pick a new random block size
        sizeUpdate = false;
      }
    }

  } //end_every_n

  EVERY_N_SECONDS(5)
  {
    sizeUpdate = true; // trigger size update
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
    thishue = random16(0, 255); // Randomize every LED if TRUE
  }
  if (i < NUM_LEDS)
  {
    leds[i] = CHSV(thishue, thissat, thisbri); // Only the lowest probability twinkles will do. You could even randomize the hue/saturation.
  }
  for (int j = 0; j < NUM_LEDS; j++)
  {
    leds[j].fadeToBlackBy(thisfade); // Use the FastLED fade method.
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
    leds[globals.pixelNumber] += CHSV(hue, 255, 255);
    leds[(globals.pixelNumber + 5) % NUM_LEDS] += CHSV(hue + 85, 255, 255);   // We use modulus so that the location is between 0 and NUM_LEDS
    leds[(globals.pixelNumber + 10) % NUM_LEDS] += CHSV(hue + 170, 255, 255); // Same here.
    fadeToBlackBy(leds, NUM_LEDS, thisfade);                                  // Low values = slower fade.

    if (++globals.pixelNumber >= NUM_LEDS)
    {
      globals.pixelNumber = 0;
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
      if ((globals.pixelNumber - j < NUM_LEDS) && (globals.pixelNumber - j >= 0))
      {
        setPixel(globals.pixelNumber - j, red, green, blue);
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

    leds[globals.pixelNumber] = CRGB(red, green, blue);
    blur1d(leds, NUM_LEDS, beatsin8(7, 20, 80));

    FastLED.show();
    leds[globals.pixelNumber] = CRGB::Black;
    if (++globals.pixelNumber >= NUM_LEDS)
    {
      globals.pixelNumber = 0;
    }
  }
}

void Marqueev2(uint8_t spacing, uint16_t holdTime)
{
  // https://github.com/marmilicious/FastLED_examples/blob/master/marquee_v2.ino
  EVERY_N_SECONDS(40)
  { // Change direction every N seconds.
    delta2 = -1 * delta2;
  }
  EVERY_N_SECONDS(40)
  { // Change direction every N seconds.
    delta2 = -1 * delta2;
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
    }                            // Jump spacing up to 8
    hue = hue + random8(30, 61); // Shift the hue to something new.
  }

  EVERY_N_MILLISECONDS(holdTime)
  {
    // holdTime = Milliseconds to hold position before advancing
    // Advance pixels to next position.

    for (int i = 0; i < (NUM_LEDS / spacing); i++)
    {
      pos = (spacing * (i - 1) + spacing + advance) % NUM_LEDS;
      leds[pos] = CHSV(hue, 255, 255);
    }

    FastLED.show();

    // Fade out tail or set back to black for next loop around.
    if (fadingTail == 1)
    {
      fadeToBlackBy(leds, NUM_LEDS, fadeRate);
    }
    else
    {
      for (int i = 0; i < (NUM_LEDS / spacing); i++)
      {
        pos = (spacing * (i - 1) + spacing + advance) % NUM_LEDS;
        leds[pos] = CRGB::Black;
      }
    }

    // Advance pixel postion down strip, and rollover if needed.
    advance = (advance + delta2 + NUM_LEDS) % NUM_LEDS;
  }
}

void Marqueev3(uint8_t spacing, uint16_t holdTime, uint8_t width, uint8_t hue2Shift)
{
  //https: //github.com/marmilicious/FastLED_examples/blob/master/marquee_v3.ino
  EVERY_N_SECONDS(10)
  { // Demo: Change direction every N seconds.
    delta2 = -1 * delta2;
  }

  //EVERY_N_SECONDS(10){  // Demo: Changing the pixel spacing every N seconds.
  //  spacing = spacing + 1;
  //  if (spacing == 9) { spacing = 2; }  // Reset spacing to 2
  //  if (spacing >4) { spacing = 8; }  // Jump spacing up to 8
  //}

  EVERY_N_SECONDS(10)
  {                              // Demo: Change the hue every N seconds.
    hue = hue + random8(30, 61); // Shift the hue to something new.
  }

  EVERY_N_MILLISECONDS(holdTime)
  { // Advance pixels to next position.

    // Advance pixel postion down strip, and rollover if needed.
    advance = (advance + delta2 + NUM_LEDS) % NUM_LEDS;

    // Fade out tail or set back to black for next loop around.
    if (fadingTail == 1)
    {
      fadeToBlackBy(leds, NUM_LEDS, fadeRate);
    }
    else
    {
      for (int i = 0; i < (NUM_LEDS / spacing); i++)
      {
        for (uint8_t w = 0; w < width; w++)
        {
          //pos = (spacing * (i-1) + spacing + advance + w) % NUM_LEDS;
          pos = (spacing * (i - 1) + spacing + advance + w - 1) % NUM_LEDS;
          leds[pos] = CRGB::Black;
        }
      }
    }

    // Update pixels down the strip.
    for (int i = 0; i < (NUM_LEDS / spacing); i++)
    {
      for (uint8_t w = 0; w < width; w++)
      {
        pos = (spacing * (i - 1) + spacing + advance + w) % NUM_LEDS;
        if (w % 2 == 0)
        { // Is w even or odd?
          colorStorage = hue;
        }
        else
        {
          colorStorage = hue + hue2Shift;
        }

        leds[pos] = CHSV(colorStorage, 255, 255);
      }
    }

    FastLED.show();

  } //end_every_n
}

void Sawtooth(int bpm, CRGBPalette16 currentPalette, TBlendType currentBlending)
{

  // https://github.com/atuline/FastLED-Demos/blob/master/sawtooth/sawtooth.ino
  int ms_per_beat = 60000 / bpm; // 500ms per beat, where 60,000 = 60 seconds * 1000 ms
  int ms_per_led = 60000 / bpm / NUM_LEDS;

  int cur_led = ((millis() % ms_per_beat) / ms_per_led) % (NUM_LEDS); // Using millis to count up the strand, with %NUM_LEDS at the end as a safety factor.

  if (cur_led == 0)
    fill_solid(leds, NUM_LEDS, CRGB::Black);
  else
    leds[cur_led] = ColorFromPalette(currentPalette, 0, 255, currentBlending); // I prefer to use palettes instead of CHSV or CRGB assignments.
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

  fill_rainbow(leds, NUM_LEDS, thishue, deltahue); // Use FastLED's fill_rainbow routine.
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
  speed = beatsin8(bpm, 0, 255);

  globals.clr1 = blend(CHSV(beatsin8(3, 0, 255), 255, 255), CHSV(beatsin8(4, 0, 255), 255, 255), speed);
  globals.clr2 = blend(CHSV(beatsin8(4, 0, 255), 255, 255), CHSV(beatsin8(3, 0, 255), 255, 255), speed);

  loc1 = beatsin8(bpm2, 0, NUM_LEDS - 1);

  fill_gradient_RGB(leds, 0, globals.clr2, loc1, globals.clr1);
  fill_gradient_RGB(leds, loc1, globals.clr2, NUM_LEDS - 1, globals.clr1);
}

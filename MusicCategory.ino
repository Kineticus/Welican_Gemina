void music_category(int patternMode)
{
    globalStrings.categoryName = "MUSIC";

    switch (patternMode)
    {
    case 0:
        globalStrings.functionName = "Random";
        break;
    case 1:
        musicOne();
        break;
    case 2:
        musicTwo();
        break;
    case 3:
        musicThree();
        break;
    case 4:
        musicFour();
        break;
    case 5:
        musicFive();
        break;
    case 6:
        musicSix();
        break;
    case 7:
        musicSeven();
        break;
    case 8:
        musicEight();
        break;
    case 9:
        musicNine();
        break;
    case 10:
        musicTen();
        break;
    case 11:
        musicEleven();
        break;
    case 12:
        musicTwelve();
        break;
    case 13:
        musicZero();
        break;
    case 14:
        musicFourteen();
        break;
    case 15:
        musicFifteen();
        break;
    }
}


void musicFourteen()
{
    globalStrings.functionName = "musicFourteen";

    for (int i = NUM_LEDS - 1; i > 0; i--)
    {
        patternSettings.leds[i] = patternSettings.leds[i - 1];
    }

    patternSettings.leds[1].r = eqBands.bandValues[0] / (AMPLITUDE / 2); 
    
    //patternSettings.leds[0].g = eqBands.bandValues[2] / (AMPLITUDE / 2);
    //patternSettings.leds[0].b = eqBands.bandValues[5] / (AMPLITUDE / 2);

    patternSettings.leds[0].g = 0;
    patternSettings.leds[0].b = 0;
}


void musicFifteen()
{
    globalStrings.functionName = "musicFourteen";

    DualColorFlowBounce(.55, .21, .0001, .1, 6);

    for (int i = NUM_LEDS; i > 0; i = i - 2)
    {
        patternSettings.leds[i].r = eqBands.bandValues[0] / (AMPLITUDE / 3);
        patternSettings.leds[i].g = 0;
        patternSettings.leds[i].b = 0;
    }
}

void bpm()
{
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    for (int i = 0; i < NUM_LEDS; i++)
    { //9948
        patternSettings.leds[i] = ColorFromPalette(palette, patternSettings.gHue + (i * 2), beat - patternSettings.gHue + (i * 10));
    }
}

void bpmCustom(CRGBPalette16 palette)
{
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    for (int i = 0; i < NUM_LEDS; i++)
    { //9948
        patternSettings.leds[i] = ColorFromPalette(palette, patternSettings.gHue + (i * 2), beat - patternSettings.gHue + (i * 10));
    }
}

void juggle(int saturation, int value)
{
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy(patternSettings.leds, NUM_LEDS, 20);
    byte dothue = 0;
    for (int i = 0; i < 8; i++)
    {
        patternSettings.leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(dothue, saturation, value);
        dothue += 32;
    }
}

// FUNCTIONS

void musicZero()
{
    globalStrings.functionName = "musicZero";
    bpm();
}
void musicOne()
{
    globalStrings.functionName = "musicOne";
    juggle(255, 255);
}
void musicTwo()
{
    globalStrings.functionName = "musicTwo";
    juggle(128, 255);
}
void musicThree()
{
    globalStrings.functionName = "musicThree";
    juggle(64, 255);
}
void musicFour()
{
    globalStrings.functionName = "musicFour";
    juggle(32, 255);
}
void musicFive()
{
    globalStrings.functionName = "musicFive";
    bpmCustom(PartyColors_p);
}
void musicSix()
{
    globalStrings.functionName = "musicSix";
    bpmCustom(RainbowStripeColors_p);
}
void musicSeven()
{
    globalStrings.functionName = "musicSeven";
    bpmCustom(HeatColors_p);
}
void musicEight()
{
    globalStrings.functionName = "musicEight";
    bpmCustom(RainbowColors_p);
}
void musicNine()
{
    globalStrings.functionName = "musicNine";
    bpmCustom(ForestColors_p);
}
void musicTen()
{
    globalStrings.functionName = "musicTen";
    bpmCustom(OceanColors_p);
}
void musicEleven()
{
    globalStrings.functionName = "musicEleven";
    bpmCustom(LavaColors_p);
}
void musicTwelve()
{
    globalStrings.functionName = "musicTwelve";
    bpmCustom(CloudColors_p);
}

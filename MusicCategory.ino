void music_mode(int patternMode)
{
    categoryName = "MUSIC";

    switch (patternMode)
    {
    case 0:
        musicZero();
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
        leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    }
}

void bpmCustom(CRGBPalette16 palette)
{
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    for (int i = 0; i < NUM_LEDS; i++)
    { //9948
        leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    }
}

void juggle(int saturation, int value)
{
    // eight colored dots, weaving in and out of sync with each other
    fadeToBlackBy(leds, NUM_LEDS, 20);
    byte dothue = 0;
    for (int i = 0; i < 8; i++)
    {
        leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(dothue, saturation, value);
        dothue += 32;
    }
}

// FUNCTIONS

void musicZero()
{
    functionName = "musicZero";
    bpm();
}
void musicOne()
{
    functionName = "musicOne";
    juggle(255, 255);
}
void musicTwo()
{
    functionName = "musicTwo";
    juggle(128, 255);
}
void musicThree()
{
    functionName = "musicThree";
    juggle(64, 255);
}
void musicFour()
{
    functionName = "musicFour";
    juggle(32, 255);
}
void musicFive()
{
    functionName = "musicFive";
    bpmCustom(PartyColors_p);
}
void musicSix()
{
    functionName = "musicSix";
    bpmCustom(RainbowStripeColors_p);
}
void musicSeven()
{
    functionName = "musicSeven";
    bpmCustom(HeatColors_p);
}
void musicEight()
{
    functionName = "musicEight";
    bpmCustom(RainbowColors_p);
}
void musicNine()
{
    functionName = "musicNine";
    bpmCustom(ForestColors_p);
}
void musicTen()
{
    functionName = "musicTen";
    bpmCustom(OceanColors_p);
}
void musicEleven()
{
    functionName = "musicEleven";
    bpmCustom(LavaColors_p);
}
void musicTwelve()
{
    functionName = "musicTwelve";
    bpmCustom(CloudColors_p);
}

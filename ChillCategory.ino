void chill_category(int patternMode)
{
    globalStrings.categoryName = "CHILL";

    switch (patternMode)
    {
    case 0:
        globalStrings.functionName = "redHsv";
        redHsv();
        break;
    case 1:
        globalStrings.functionName = "aquaHsv";
        aquaHsv();
        break;
    case 2:
        globalStrings.functionName = "yellowHsv";
        yellowHsv();
        break;
    case 3:
        globalStrings.functionName = "purpleHsv";
        purpleHsv();
        break;
    case 4:
        globalStrings.functionName = "redGlitterHsv";
        redGlitterHsv();
        break;
    case 5:
        globalStrings.functionName = "aquaGlitterHsv";
        aquaGlitterHsv();
        break;
    case 6:
        globalStrings.functionName = "yellowGlitterHsv";
        yellowGlitterHsv();
        break;
    case 7:
        globalStrings.functionName = "purpleGlitterHsv";
        purpleGlitterHsv();
        break;
    case 8:
        globalStrings.functionName = "confettiOne";
        confettiOne();
        break;
    case 9:
        globalStrings.functionName = "confettiTwo";
        confettiTwo();
        break;
    case 10:
        globalStrings.functionName = "confettiThree";
        confettiThree();
        break;
    case 11:
        globalStrings.functionName = "confettiFour";
        confettiFour();
        break;
    case 12:
        globalStrings.functionName = "confettiFive";
        confettiFive();
        break;
    case 13:
        globalStrings.functionName = "sinelonOne";
        sinelonOne();
        break;
    case 14:
        globalStrings.functionName = "sinelonTwo";
        sinelonTwo();
        break;
    case 15:
        globalStrings.functionName = "sinelonThree";
        sinelonThree();
        break;
    case 16:
        globalStrings.functionName = "sinelonFour";
        sinelonFour();
        break;
    case 17:
        globalStrings.functionName = "sinelonFive";
        sinelonFive();
        break;
        // case 18:
        //     RainbowOneYoffset();
        //     break;
        // case 19:
        //     RainbowTwoYoffset();
        //     break;
        // case 20:
        //     RainbowThreeXoffset();
        //     break;
        // case 21:
        //     RainbowFourXoffset();
        //     break;
        // case 22:
        //     RainbowBigXoffset();
        //     break;
        // case 23:
        //     RainbowBigYoffset();
        //     break;
    }
}

// FUNCTIONS

void redHsv()
{
    globalStrings.functionName = "redHsv";
    fill_solid(patternSettings.leds, NUM_LEDS, CHSV(0, 255, 255));
}
void aquaHsv()
{
    globalStrings.functionName = "aquaHsv";
    fill_solid(patternSettings.leds, NUM_LEDS, CHSV(128, 255, 255));
}
void yellowHsv()
{
    globalStrings.functionName = "yellowHsv";
    fill_solid(patternSettings.leds, NUM_LEDS, CHSV(64, 255, 255));
}
void purpleHsv()
{
    globalStrings.functionName = "purpleHsv";
    fill_solid(patternSettings.leds, NUM_LEDS, CHSV(192, 255, 255));
}
void redGlitterHsv()
{
    globalStrings.functionName = "redGlitterHsv";
    fill_solid(patternSettings.leds, NUM_LEDS, CHSV(0, 255, 255));
    addGlitter(80);
}
void aquaGlitterHsv()
{
    globalStrings.functionName = "aquaGlitterHsv";
    fill_solid(patternSettings.leds, NUM_LEDS, CHSV(128, 255, 255));
    addGlitter(80);
}
void yellowGlitterHsv()
{
    globalStrings.functionName = "yellowGlitterHsv";
    fill_solid(patternSettings.leds, NUM_LEDS, CHSV(64, 255, 255));
    addGlitter(40);
}
void purpleGlitterHsv()
{
    globalStrings.functionName = "purpleGlitterHsv";
    fill_solid(patternSettings.leds, NUM_LEDS, CHSV(192, 255, 255));
    addGlitter(40);
}
void confettiOne()
{
    globalStrings.functionName = "confettiOne";
    confettiCustom(200, 255, 16);
}
void confettiTwo()
{
    globalStrings.functionName = "confettiTwo";
    confettiCustom(200, 255, 32);
}
void confettiThree()
{
    globalStrings.functionName = "confettiThree";
    confettiCustom(200, 255, 64);
}
void confettiFour()
{
    globalStrings.functionName = "confettiFour";
    confettiCustom(200, 255, 128);
}
void confettiFive()
{
    globalStrings.functionName = "confettiFive";
    confettiCustom(200, 255, 255);
}
void sinelonOne()
{
    globalStrings.functionName = "sinelonOne";
    sinelonCustom(255, 255, 90, 8);
}
void sinelonTwo()
{
    globalStrings.functionName = "sinelonTwo";
    sinelonCustom(128, 255, 60, 12);
}
void sinelonThree()
{
    globalStrings.functionName = "sinelonThree";
    sinelonCustom(92, 255, 30, 16);
}
void sinelonFour()
{
    globalStrings.functionName = "sinelonFour";
    sinelonCustom(64, 255, 16, 8);
}
void sinelonFive()
{
    globalStrings.functionName = "sinelonFive";
    sinelonCustom(32, 255, 1, 12);
}
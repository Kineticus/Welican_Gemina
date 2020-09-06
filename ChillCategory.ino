void chill_category(int patternMode)
{
    categoryName = "CHILL";

    switch (patternMode)
    {
    case 0:
        functionName = "redHsv";
        redHsv();
        break;
    case 1:
        functionName = "aquaHsv";
        aquaHsv();
        break;
    case 2:
        functionName = "yellowHsv";
        yellowHsv();
        break;
    case 3:
        functionName = "purpleHsv";
        purpleHsv();
        break;
    case 4:
        functionName = "redGlitterHsv";
        redGlitterHsv();
        break;
    case 5:
        functionName = "aquaGlitterHsv";
        aquaGlitterHsv();
        break;
    case 6:
        functionName = "yellowGlitterHsv";
        yellowGlitterHsv();
        break;
    case 7:
        functionName = "purpleGlitterHsv";
        purpleGlitterHsv();
        break;
    case 8:
        functionName = "confettiOne";
        confettiOne();
        break;
    case 9:
        functionName = "confettiTwo";
        confettiTwo();
        break;
    case 10:
        functionName = "confettiThree";
        confettiThree();
        break;
    case 11:
        functionName = "confettiFour";
        confettiFour();
        break;
    case 12:
        functionName = "confettiFive";
        confettiFive();
        break;
    case 13:
        functionName = "sinelonOne";
        sinelonOne();
        break;
    case 14:
        functionName = "sinelonTwo";
        sinelonTwo();
        break;
    case 15:
        functionName = "sinelonThree";
        sinelonThree();
        break;
    case 16:
        functionName = "sinelonFour";
        sinelonFour();
        break;
    case 17:
        functionName = "sinelonFive";
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
    functionName = "redHsv";
    fill_solid(leds, NUM_LEDS, CHSV(0, 255, 255));
}
void aquaHsv()
{
    functionName = "aquaHsv";
    fill_solid(leds, NUM_LEDS, CHSV(128, 255, 255));
}
void yellowHsv()
{
    functionName = "yellowHsv";
    fill_solid(leds, NUM_LEDS, CHSV(64, 255, 255));
}
void purpleHsv()
{
    functionName = "purpleHsv";
    fill_solid(leds, NUM_LEDS, CHSV(192, 255, 255));
}
void redGlitterHsv()
{
    functionName = "redGlitterHsv";
    fill_solid(leds, NUM_LEDS, CHSV(0, 255, 255));
    addGlitter(80);
}
void aquaGlitterHsv()
{
    functionName = "aquaGlitterHsv";
    fill_solid(leds, NUM_LEDS, CHSV(128, 255, 255));
    addGlitter(80);
}
void yellowGlitterHsv()
{
    functionName = "yellowGlitterHsv";
    fill_solid(leds, NUM_LEDS, CHSV(64, 255, 255));
    addGlitter(40);
}
void purpleGlitterHsv()
{
    functionName = "purpleGlitterHsv";
    fill_solid(leds, NUM_LEDS, CHSV(192, 255, 255));
    addGlitter(40);
}
void confettiOne()
{
    functionName = "confettiOne";
    confettiCustom(200, 255, 16);
}
void confettiTwo()
{
    functionName = "confettiTwo";
    confettiCustom(200, 255, 32);
}
void confettiThree()
{
    functionName = "confettiThree";
    confettiCustom(200, 255, 64);
}
void confettiFour()
{
    functionName = "confettiFour";
    confettiCustom(200, 255, 128);
}
void confettiFive()
{
    functionName = "confettiFive";
    confettiCustom(200, 255, 255);
}
void sinelonOne()
{
    functionName = "sinelonOne";
    sinelonCustom(255, 255, 90, 8);
}
void sinelonTwo()
{
    functionName = "sinelonTwo";
    sinelonCustom(128, 255, 60, 12);
}
void sinelonThree()
{
    functionName = "sinelonThree";
    sinelonCustom(92, 255, 30, 16);
}
void sinelonFour()
{
    functionName = "sinelonFour";
    sinelonCustom(64, 255, 16, 8);
}
void sinelonFive()
{
    functionName = "sinelonFive";
    sinelonCustom(32, 255, 1, 12);
}

// void RainbowOneYoffset()
// {
//     functionName = "RainbowOneYoffset";
//     spaceinc = 0.03;
//     timeinc = (0.000025 * currSpeed);
//     yoffset += timeinc;
//     //xoffset += timeinc;
//     SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
// }
// void RainbowTwoYoffset()
// {
//     functionName = "RainbowTwoYoffset";
//     spaceinc = 0.07;
//     timeinc = (0.000025 * currSpeed);
//     yoffset += timeinc;
//     //xoffset += timeinc;
//     SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
// }
// void RainbowThreeXoffset()
// {
//     functionName = "RainbowThreeXoffset";
//     spaceinc = 0.07;
//     timeinc = (0.000025 * currSpeed);
//     //yoffset += timeinc;
//     xoffset += timeinc;
//     SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
// }
// void RainbowFourXoffset()
// {
//     functionName = "RainbowFourXoffset";
//     spaceinc = 0.03;
//     timeinc = (0.000025 * currSpeed);
//     //yoffset += timeinc;
//     xoffset += timeinc;
//     SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
// }
// void RainbowBigXoffset()
// {
//     functionName = "RainbowBigXoffset";
//     spaceinc = 0.12;
//     timeinc = (0.000025 * currSpeed);
//     //yoffset += timeinc;
//     xoffset += timeinc;
//     SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
// }
// void RainbowBigYoffset()
// {
//     functionName = "RainbowBigYoffset";
//     spaceinc = 0.12;
//     timeinc = (0.000025 * currSpeed);
//     yoffset += timeinc;
//     //xoffset += timeinc;
//     SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);
// }

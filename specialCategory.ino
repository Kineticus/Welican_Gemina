// https://cssgradient.io/
// Copy CSS code to https://palette-library.vercel.app/
// converted for FastLED with gammas (2.6, 2.2, 2.5)

DEFINE_GRADIENT_PALETTE(christmas_1){
    0, 255, 3, 1,
    130, 255, 255, 255,
    255, 0, 57, 1};
CRGBPalette16 pal_christmas_1 = christmas_1;

DEFINE_GRADIENT_PALETTE(christmas_2){
    0, 255, 3, 1,
    255, 0, 57, 1};
CRGBPalette16 pal_christmas_2 = christmas_2;

DEFINE_GRADIENT_PALETTE(rasta_flag){
    0, 255, 0, 0,
    125, 232, 255, 0,
    255, 0, 93, 1};
CRGBPalette16 pal_rasta_flag = rasta_flag;

DEFINE_GRADIENT_PALETTE(hanukkah){
    0, 1, 0, 255,
    127, 255, 255, 255,
    255, 1, 0, 255};
CRGBPalette16 pal_hanukkah = hanukkah;

DEFINE_GRADIENT_PALETTE(independence_day){
    0, 255, 0, 0,
    127, 255, 255, 255,
    255, 1, 0, 255};
CRGBPalette16 pal_independence_day = independence_day;

DEFINE_GRADIENT_PALETTE(halloween_1){
    0, 0, 0, 0,
    255, 177, 57, 0};
CRGBPalette16 pal_halloween_1 = halloween_1;

DEFINE_GRADIENT_PALETTE(halloween_2){
    0, 177, 57, 0,
    130, 17, 0, 34,
    255, 177, 57, 0};
CRGBPalette16 pal_halloween_2 = halloween_2;

// -------------------------------------------------------
// FUNCTIONS
// -------------------------------------------------------
void palette_category(int patternMode)
{
    globalStrings.categoryName = "Palettes";

    switch (patternMode)
    {
    case 1:
        Christmas1();
        break;
    case 2:
        Christmas2();
        break;
    case 3:
        IndependenceDay();
        break;
    case 4:
        Hanukkah();
        break;
    case 5:
        Halloween1();
        break;
    case 6:
        Halloween2();
        break;
    }
}

void Christmas1()
{
    globalStrings.functionName = "Christmas1";
    byte poop = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]];

    if (poop != 0)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            patternSettings.leds[i] = ColorFromPalette(pal_christmas_1, patternSettings.colorIndex[i]);
            patternSettings.colorIndex[i] += poop / 40;

            int beat1 = beatsin16(poop / 30, 0, 255, (65536 / NUM_LEDS) * i, 0);
            int beat2 = beatsin16(poop / 10, 0, 255, (65536 / NUM_LEDS) * i, 0);

            patternSettings.leds[i].fadeToBlackBy((beat1 + beat2) / 2);
        }
    }
    else
    {
        fill_palette(patternSettings.leds, NUM_LEDS, 0, 255 / NUM_LEDS, pal_christmas_1, 255, LINEARBLEND);
    }
}

void Christmas2()
{
    globalStrings.functionName = "Christmas2";
    byte poop = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]];

    if (poop != 0)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            patternSettings.leds[i] = ColorFromPalette(pal_christmas_2, patternSettings.colorIndex[i]);
            patternSettings.colorIndex[i] += poop / 40;

            int beat1 = beatsin16(poop / 30, 0, 255, (65536 / NUM_LEDS) * i, 0);
            int beat2 = beatsin16(poop / 10, 0, 255, (65536 / NUM_LEDS) * i, 0);

            patternSettings.leds[i].fadeToBlackBy((beat1 + beat2) / 2);
        }
    }
    else
    {
        fill_palette(patternSettings.leds, NUM_LEDS, 0, 255 / NUM_LEDS, pal_christmas_2, 255, LINEARBLEND);
    }
}

void Hanukkah()
{
    globalStrings.functionName = "Hanukkah";
    byte poop = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]];

    if (poop != 0)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            patternSettings.leds[i] = ColorFromPalette(pal_hanukkah, patternSettings.colorIndex[i]);
            patternSettings.colorIndex[i] += poop / 40;

            int beat1 = beatsin16(poop / 30, 0, 255, (65536 / NUM_LEDS) * i, 0);
            int beat2 = beatsin16(poop / 10, 0, 255, (65536 / NUM_LEDS) * i, 0);

            patternSettings.leds[i].fadeToBlackBy((beat1 + beat2) / 2);
        }
    }
    else
    {
        fill_palette(patternSettings.leds, NUM_LEDS, 0, 255 / NUM_LEDS, pal_hanukkah, 255, LINEARBLEND);
    }
}

void IndependenceDay()
{
    globalStrings.functionName = "IndependenceDay";
    byte poop = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]];

    if (poop != 0)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            patternSettings.leds[i] = ColorFromPalette(pal_independence_day, patternSettings.colorIndex[i]);
            patternSettings.colorIndex[i] += poop / 40;

            int beat1 = beatsin16(poop / 30, 0, 255, (65536 / NUM_LEDS) * i, 0);
            int beat2 = beatsin16(poop / 10, 0, 255, (65536 / NUM_LEDS) * i, 0);

            patternSettings.leds[i].fadeToBlackBy((beat1 + beat2) / 2);
        }
    }
    else
    {
        fill_palette(patternSettings.leds, NUM_LEDS, 0, 255 / NUM_LEDS, pal_independence_day, 255, LINEARBLEND);
    }
}

void Halloween1()
{
    globalStrings.functionName = "Halloween1";
    byte poop = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]];

    if (poop != 0)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            patternSettings.leds[i] = ColorFromPalette(pal_halloween_1, patternSettings.colorIndex[i]);
            patternSettings.colorIndex[i] += poop / 40;

            int beat1 = beatsin16(poop / 30, 0, 255, (65536 / NUM_LEDS) * i, 0);
            int beat2 = beatsin16(poop / 10, 0, 255, (65536 / NUM_LEDS) * i, 0);

            patternSettings.leds[i].fadeToBlackBy((beat1 + beat2) / 2);
        }
    }
    else
    {
        fill_palette(patternSettings.leds, NUM_LEDS, 0, 255 / NUM_LEDS, pal_halloween_1, 255, LINEARBLEND);
    }
}

void Halloween2()
{
    globalStrings.functionName = "Halloween2";
    byte poop = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]];

    if (poop != 0)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            patternSettings.leds[i] = ColorFromPalette(pal_halloween_2, patternSettings.colorIndex[i]);
            patternSettings.colorIndex[i] += poop / 40;

            int beat1 = beatsin16(poop / 30, 0, 255, (65536 / NUM_LEDS) * i, 0);
            int beat2 = beatsin16(poop / 10, 0, 255, (65536 / NUM_LEDS) * i, 0);

            patternSettings.leds[i].fadeToBlackBy((beat1 + beat2) / 2);
        }
    }
    else
    {
        fill_palette(patternSettings.leds, NUM_LEDS, 0, 255 / NUM_LEDS, pal_halloween_2, 255, LINEARBLEND);
    }
}
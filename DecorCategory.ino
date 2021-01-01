// https://cssgradient.io/
// Copy CSS code to https://palette-library.vercel.app/


         
DEFINE_GRADIENT_PALETTE( amber_warmwhite ) {
    0, 255, 0, 0,
    127, 255, 50, 0,
    255, 255, 100, 42
};
CRGBPalette16 pal_AWW = amber_warmwhite;

// converted for FastLED with gammas (2.6, 2.2, 2.5)

DEFINE_GRADIENT_PALETTE(matt_test){
    0, 1, 255, 228,
    92, 11, 139, 6,
    186, 152, 0, 128,
    255, 0, 169, 255};
CRGBPalette16 pal_Matt = matt_test;

DEFINE_GRADIENT_PALETTE(brian_test){
    0, 6, 128, 121,
    84, 1, 1, 133,
    145, 2, 64, 19,
    199, 1, 42, 154,
    255, 6, 128, 121};

CRGBPalette16 pal_Brian = brian_test;

// Gradient palette "Sunset_Real_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Sunset_Real.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 28 bytes of program space.

DEFINE_GRADIENT_PALETTE(Sunset_Real_gp){
    0, 120, 0, 0,
    22, 179, 22, 0,
    51, 255, 104, 0,
    85, 167, 22, 18,
    135, 100, 0, 103,
    198, 16, 0, 130,
    255, 0, 0, 160};

CRGBPalette16 pal_Outrun = Sunset_Real_gp;

// Gradient palette "scoutie_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/scoutie.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 16 bytes of program space.

DEFINE_GRADIENT_PALETTE(scoutie_gp){
    0, 255, 156, 0,
    127, 0, 195, 18,
    216, 1, 0, 39,
    255, 1, 0, 39};

CRGBPalette16 pal_GreenYellowBlue = scoutie_gp;

DEFINE_GRADIENT_PALETTE(rasta_flag){
    0, 255, 0, 0,
    125, 232, 255, 0,
    255, 0, 93, 1};
CRGBPalette16 pal_rasta_flag = rasta_flag;


// -------------------------------------------------------
// FUNCTIONS
// -------------------------------------------------------
void decor_category(int patternMode)
{
    globalStrings.categoryName = "DECOR";

    switch (patternMode)
    {
    case 1:
        paletteOne();
        break;
    case 2:
        paletteTwo();
        break;
    case 3:
        paletteThree();
        break;
    case 4:
        paletteFour();
        break;
    case 5:
        paletteFive();
        break;
    case 6:
        RastaFlag();
        break;
    case 7:
        paletteAmberWarmWhite();
        break;
    }
}

void paletteAmberWarmWhite()
{
    // REF: https://gist.github.com/Tejkaran/dcc4db20f00d8bcb3cef830f9f3c72e8
    static uint8_t brightness = 255;
    static uint8_t startPoint = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]; // read mod-knob setting
    static uint8_t paletteQuantityLength = 255 / NUM_LEDS; //value between 0 and 10, how much of the lights should be lit up at once, 0 being all
    TBlendType blendingType = LINEARBLEND; //tBlendType is a type of value like int/char/uint8_t etc., use to choose LINERBLEND and NOBLEND
    globalStrings.functionName = "Amber - Warm White";
    startPoint = startPoint + 1;   //if it is 0, then it will all stay the same
    // if (startPoint != 0)
    // {
    //     fill_palette(patternSettings.leds, NUM_LEDS, startPoint, 0, pal_AWW, 255, LINEARBLEND);
    // }
    // else
    // {
    //     fill_palette(patternSettings.leds, NUM_LEDS, 0, 255 / NUM_LEDS, pal_AWW, 255, LINEARBLEND);
    // }
    fill_palette(patternSettings.leds, NUM_LEDS, startPoint, paletteQuantityLength, pal_AWW, brightness, blendingType);
}

void paletteOne()
{
    globalStrings.functionName = "PaletteOne";
    byte poop = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]];

    fill_palette(patternSettings.leds, NUM_LEDS, 0, 255 / NUM_LEDS, pal_Brian, 255, LINEARBLEND);
}

void paletteTwo()
{
    globalStrings.functionName = "PaletteTwo";
    byte poop = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]];

    fill_solid(patternSettings.leds, NUM_LEDS, CHSV(poop, 255, 255));
}

void paletteThree()
{
    globalStrings.functionName = "PaletteThree";
    byte poop = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]];

    if (poop != 0)
    {
        fill_palette(patternSettings.leds, NUM_LEDS, poop, 0, pal_Outrun, 255, LINEARBLEND);
    }
    else
    {
        fill_palette(patternSettings.leds, NUM_LEDS, 0, 255 / NUM_LEDS, pal_Outrun, 255, LINEARBLEND);
    }
}

void paletteFour()
{
    globalStrings.functionName = "PaletteFour";
    byte poop = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]];

    if (poop != 0)
    {
        fadeToBlackBy(patternSettings.leds, NUM_LEDS, poop);
        patternSettings.leds[random(0, NUM_LEDS - 1)] = ColorFromPalette(pal_GreenYellowBlue, random8(), 255, LINEARBLEND);
    }
    else
    {
        fill_palette(patternSettings.leds, NUM_LEDS, 0, 255 / NUM_LEDS, pal_GreenYellowBlue, 255, LINEARBLEND);
    }
}

void paletteFive()
{
    globalStrings.functionName = "PaletteFive";
    byte poop = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]];

    if (poop != 0)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            patternSettings.leds[i] = ColorFromPalette(pal_Brian, patternSettings.colorIndex[i]);
            patternSettings.colorIndex[i] += poop / 40;

            int beat1 = beatsin16(poop / 30, 0, 255, (65536 / NUM_LEDS) * i, 0);
            int beat2 = beatsin16(poop / 10, 0, 255, (65536 / NUM_LEDS) * i, 0);

            patternSettings.leds[i].fadeToBlackBy((beat1 + beat2) / 2);
        }
    }
    else
    {
        fill_palette(patternSettings.leds, NUM_LEDS, 0, 255 / NUM_LEDS, pal_Brian, 255, LINEARBLEND);
    }
}

void RastaFlag()
{
    globalStrings.functionName = "RastaFlag";
    byte poop = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]];

    if (poop != 0)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            patternSettings.leds[i] = ColorFromPalette(pal_rasta_flag, patternSettings.colorIndex[i]);
            patternSettings.colorIndex[i] += poop / 40;

            int beat1 = beatsin16(poop / 30, 0, 255, (65536 / NUM_LEDS) * i, 0);
            int beat2 = beatsin16(poop / 10, 0, 255, (65536 / NUM_LEDS) * i, 0);

            patternSettings.leds[i].fadeToBlackBy((beat1 + beat2) / 2);
        }
    }
    else
    {
        fill_palette(patternSettings.leds, NUM_LEDS, 0, 255 / NUM_LEDS, pal_rasta_flag, 255, LINEARBLEND);
    }
}

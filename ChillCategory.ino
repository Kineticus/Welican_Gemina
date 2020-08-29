void chill_mode() {
    switch (pattern[mode])
    {
        case 0:
            redHsv();
            break;
        case 1:
            aquaHsv();
            break;
        case 2:
            yellowHsv();
            break;
        case 3:
            purpleHsv();
            break;
        case 4:
            redGlitterHsv();
            break;
        case 5:
            aquaGlitterHsv();
            break;
        case 6:
            yellowGlitterHsv();
            break;
        case 7:
            purpleGlitterHsv();
            break;
        case 8:
            confettiOne();
            break;
        case 9:
            confettiTwo();
            break;
        case 10:
            confettiThree();
            break;
        case 11:
            confettiFour();
            break;
        case 12:
            confettiFive();
            break;
        case 13:
            sinelonOne();
            break;
        case 14:
            sinelonTwo();
            break;
        case 15:
            sinelonThree();
            break;
        case 16:
            sinelonFour();
            break;
        case 17:
            sinelonFive();
            break;
        case 18:
            RainbowOneYoffset();
            break;
        case 19:
            RainbowTwoYoffset();
            break;
        case 20:
            RainbowThreeXoffset();
            break;
        case 21:
            RainbowFourXoffset();
            break;
        case 22:
            RainbowBigXoffset();
            break;
        case 23:
            RainbowBigYoffset();
            break;
    }
}

// FUNCTIONS

void redHsv() {
    functionName = "redHsv";
    fill_solid(leds, NUM_LEDS, CHSV(0,255,255));
}
void aquaHsv() {
    functionName = "aquaHsv";
    fill_solid(leds, NUM_LEDS, CHSV(128,255,255));
}
void yellowHsv() {
    functionName = "yellowHsv";
    fill_solid(leds, NUM_LEDS, CHSV(64,255,255));
}
void purpleHsv() {
    functionName = "purpleHsv";
    fill_solid(leds, NUM_LEDS, CHSV(192,255,255));
}
void redGlitterHsv() {
    functionName = "redGlitterHsv";
    fill_solid(leds, NUM_LEDS, CHSV(0,255,255));
    addGlitter(80);
}
void aquaGlitterHsv() {
    functionName = "aquaGlitterHsv";
    fill_solid(leds, NUM_LEDS, CHSV(128,255,255));
    addGlitter(80);
}
void yellowGlitterHsv() {
    functionName = "yellowGlitterHsv";
    fill_solid(leds, NUM_LEDS, CHSV(64,255,255));
    addGlitter(40);
}
void purpleGlitterHsv() {
    functionName = "purpleGlitterHsv";
    fill_solid(leds, NUM_LEDS, CHSV(192,255,255));
    addGlitter(40);
}
void confettiOne() {
    functionName = "confettiOne";
    confettiCustom(200,255,16);
}
void confettiTwo() {
    functionName = "confettiTwo";
    confettiCustom(200,255,32);
}
void confettiThree() {
    functionName = "confettiThree";
    confettiCustom(200,255,64);
}
void confettiFour() {
    functionName = "confettiFour";
    confettiCustom(200,255,128);
}
void confettiFive() {
    functionName = "confettiFive";
    confettiCustom(200,255,255);
}
void sinelonOne() {
    functionName = "sinelonOne";
    sinelonCustom(255,255,90,8);
}
void sinelonTwo() {
    functionName = "sinelonTwo";
    sinelonCustom(128,255,60,12);
}
void sinelonThree() {
    functionName = "sinelonThree";
    sinelonCustom(92,255,30,16);
}
void sinelonFour() {
    functionName = "sinelonFour";
    sinelonCustom(64,255,16,8);
}
void sinelonFive() {
    functionName = "sinelonFive";
    sinelonCustom(32,255,1,12);
}


void RainbowOneYoffset(){
    functionName = "RainbowOneYoffset";
    spaceinc = 0.03;
    timeinc = (0.000025 * currSpeed);
    yoffset += timeinc; 
    //xoffset += timeinc;
    SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowTwoYoffset(){
    functionName = "RainbowTwoYoffset";
    spaceinc = 0.07;
    timeinc = (0.000025 * currSpeed);
    yoffset += timeinc; ; 
    //xoffset += timeinc;
    SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowThreeXoffset(){
    functionName = "RainbowThreeXoffset";
    spaceinc = 0.07;
    timeinc = (0.000025 * currSpeed);
    //yoffset += timeinc; 
    xoffset += timeinc;
    SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowFourXoffset(){
    functionName = "RainbowFourXoffset";
    spaceinc = 0.03;
    timeinc = (0.000025 * currSpeed);
    //yoffset += timeinc; 
    xoffset += timeinc;
    SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowBigXoffset(){
    functionName = "RainbowBigXoffset";
    spaceinc = 0.12;
    timeinc = (0.000025 * currSpeed);
    //yoffset += timeinc; 
    xoffset += timeinc;
    SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}
void RainbowBigYoffset(){
    functionName = "RainbowBigYoffset";
    spaceinc = 0.12;
    timeinc = (0.000025 * currSpeed);
    yoffset += timeinc; ; 
    //xoffset += timeinc;
    SimplexNoisePatternInterpolated(spaceinc, timeinc, yoffset, xoffset);    
}

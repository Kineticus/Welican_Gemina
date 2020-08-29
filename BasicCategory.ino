void basic_mode() {
    switch (pattern[mode])
    {
        case 0:
            red();
            break;
        case 1:
            green();
            break;
        case 2:
            blue();
            break;
        case 3:
            purple();
            break;
        case 4:
            teal();
            break;
        case 5:
            pink();
            break;
        case 6:
            amber();
            break;
        case 7:
            amberTwo();
            break;
        case 8:
            amberThree();
            break;
        case 9:
            amberFour();
            break;
        case 10:
            warmWhite();
            break;
        case 11:
            white();
            break;
        case 12:
            daylight();
            break;
    }
}

// FUNCTIONS

void red() {
    functionName = "red";
    fill_solid(leds, NUM_LEDS, CRGB(255,0,0));
}
void green() {
    functionName = "green";
    fill_solid(leds, NUM_LEDS, CRGB(0,255,0));
}
void blue() {
    functionName = "blue";
    fill_solid(leds, NUM_LEDS, CRGB(0,0,255));
}
void teal() {
    functionName = "teal";
    fill_solid(leds, NUM_LEDS, CRGB(0, 128, 255));
}
void pink() {
    functionName = "pink";
    fill_solid(leds, NUM_LEDS, CRGB(255, 0, 98));
}
void purple() {
    functionName = "purple";
    fill_solid(leds, NUM_LEDS, CRGB(98,0,255));
}
void amber() {
    functionName = "amber";
    fill_solid(leds, NUM_LEDS, CRGB(255,12,0));
}
void amberTwo() {
    functionName = "amberTwo";
    fill_solid(leds, NUM_LEDS, CRGB(255,32,0));
}
void amberThree() {
    functionName = "amberThree";
    fill_solid(leds, NUM_LEDS, CRGB(255,64,0));
}
void amberFour() {
    functionName = "amberFour";
    fill_solid(leds, NUM_LEDS, CRGB(255,92,0));
}
void warmWhite() {
    functionName = "warmWhite";
    fill_solid(leds, NUM_LEDS, CRGB(255,192,42));
}
void white() {
    functionName = "white";
    fill_solid(leds, NUM_LEDS, CRGB(255,224,80));
}
void daylight() {
    functionName = "daylight";
    fill_solid(leds, NUM_LEDS, CRGB(255,255,255));
}

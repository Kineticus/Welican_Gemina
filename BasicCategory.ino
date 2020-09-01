void basic_category(int patternMode)
{
    categoryName = "BASIC";

    switch (patternMode)
    {
    case 0:
        functionName = "red";
        customColor(255, 0, 0);
        break;
    case 1:
        functionName = "green";
        customColor(0, 255, 0);
        break;
    case 2:
        functionName = "blue";
        customColor(0, 0, 255);
        break;
    case 3:
        functionName = "purple";
        customColor(98, 0, 255);
        break;
    case 4:
        functionName = "teal";
        customColor(0, 128, 255);
        break;
    case 5:
        functionName = "pink";
        customColor(255, 0, 98);
        break;
    case 6:
        functionName = "amber";
        customColor(255, 12, 0);
        break;
    case 7:
        functionName = "amberTwo";
        customColor(255, 32, 0);
        break;
    case 8:
        functionName = "amberThree";
        customColor(255, 64, 0);
        break;
    case 9:
        functionName = "amberFour";
        customColor(255, 92, 0);
        break;
    case 10:
        functionName = "warmWhite";
        customColor(255, 192, 42);
        break;
    case 11:
        functionName = "white";
        customColor(255, 224, 80);
        break;
    case 12:
        functionName = "daylight";
        customColor(255, 255, 255);
        break;
    }
}

// FUNCTIONS

void customColor(int r, int g, int b)
{
    fill_solid(leds, NUM_LEDS, CRGB(r, g, b));
}
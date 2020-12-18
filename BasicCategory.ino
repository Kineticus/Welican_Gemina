void basic_category(int patternMode)
{
    globalStrings.categoryName = "BASIC";

    switch (patternMode)
    {
    case 0:
        globalStrings.functionName = "Random";
        break;
    case 1:
        globalStrings.functionName = "Red";
        customColor(255, 0, 0);
        break;
    case 2:
        globalStrings.functionName = "Green";
        customColor(0, 255, 0);
        break;
    case 3:
        globalStrings.functionName = "Blue";
        customColor(0, 0, 255);
        break;
    case 4:
        globalStrings.functionName = "Purple";
        customColor(128, 0, 128);
        break;
    case 5:
        globalStrings.functionName = "Teal";
        customColor(0, 128, 128);
        break;
    case 6:
        globalStrings.functionName = "Teal Blue";
        customColor(0, 92, 172);
        break;
    case 7:
        globalStrings.functionName = "Teal Green";
        customColor(0, 172, 92);
        break;
    case 8:
        globalStrings.functionName = "Pink";
        customColor(255, 0, 98);
        break;
    case 9:
        globalStrings.functionName = "Amber 1";
        customColor(255, 12, 0);
        break;
    case 10:
        globalStrings.functionName = "Amber 2";
        customColor(255, 24, 0);
        break;
    case 11:
        globalStrings.functionName = "Amber 3";
        customColor(255, 32, 0);
        break;
    case 12:
        globalStrings.functionName = "Amber 4";
        customColor(255, 42, 0);
        break;
    case 13:
        globalStrings.functionName = "Amber 5";
        customColor(255, 50, 0);
        break;
    case 14:
        globalStrings.functionName = "Amber 6";
        customColor(255, 55, 5);
        break;
    case 15:
        globalStrings.functionName = "Warm White 1";
        customColor(255, 55, 10);
        break;
    case 16:
        globalStrings.functionName = "Warm White 2";
        customColor(255, 64, 17);
        break;
    case 17:
        globalStrings.functionName = "Warm White 3";
        customColor(255, 64, 17);
        break;
    case 18:
        globalStrings.functionName = "Warm White 4";
        customColor(255, 72, 18);
        break;
    case 19:
        globalStrings.functionName = "Warm White 5";
        customColor(255, 78, 21);
        break;
    case 20:
        globalStrings.functionName = "Warm White 6";
        customColor(255, 82, 23);
        break;
    case 21:
        globalStrings.functionName = "White 1";
        customColor(255, 84, 25);
        break;
    case 22:
        globalStrings.functionName = "White 2";
        customColor(255, 92, 32);
        break;
    case 23:
        globalStrings.functionName = "White 3";
        customColor(255, 100, 42);
        break;
    }
}

// FUNCTIONS

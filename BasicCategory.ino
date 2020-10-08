void basic_category(int patternMode)
{
    globalStrings.categoryName = "BASIC";

    switch (patternMode)
    {
    case 0:
        globalStrings.functionName = "Random";
        break;
    case 1:
        globalStrings.functionName = "red";
        customColor(255, 0, 0);
        break;
    case 2:
        globalStrings.functionName = "green";
        customColor(0, 255, 0);
        break;
    case 3:
        globalStrings.functionName = "blue";
        customColor(0, 0, 255);
        break;
    case 4:
        globalStrings.functionName = "purple";
        customColor(98, 0, 255);
        break;
    case 5:
        globalStrings.functionName = "teal";
        customColor(0, 128, 255);
        break;
    case 6:
        globalStrings.functionName = "pink";
        customColor(255, 0, 98);
        break;
    case 7:
        globalStrings.functionName = "amber";
        customColor(255, 12, 0);
        break;
    case 8:
        globalStrings.functionName = "amberTwo";
        customColor(255, 32, 0);
        break;
    case 9:
        globalStrings.functionName = "amberThree";
        customColor(255, 64, 0);
        break;
    case 10:
        globalStrings.functionName = "amberFour";
        customColor(255, 92, 0);
        break;
    case 11:
        globalStrings.functionName = "warmWhite";
        customColor(255, 192, 42);
        break;
    case 12:
        globalStrings.functionName = "white";
        customColor(255, 224, 80);
        break;
    case 13:
        globalStrings.functionName = "daylight";
        customColor(255, 255, 255);
        break;
    }
}

// FUNCTIONS

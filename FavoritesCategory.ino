void favorites_category(int patternMode)
{
  globalStrings.categoryName = "FAVORITES";

  patternSettings.displayPattern = patternSettings.favoritePattern[patternMode];

  if (patternSettings.displayPattern == 0)
  {
    if (((millis() - globals.randomTime) > globals.randomInterval) && globals.randomMin != 0)
    {
      pickRandom();
    }

    patternSettings.displayPattern = patternSettings.randomPattern;
  }

  switch (patternSettings.favoriteMode[patternMode])
  {
    case 1: // BASIC
      basic_category(patternSettings.displayPattern);
      break;
    case 2: // DECOR
      decor_category(patternSettings.displayPattern);
      break;
    case 3: // PARTY
      moving_colors_category(patternSettings.displayPattern);
      break;
    case 4: // ADVANCED
      chill_category(patternSettings.displayPattern);
      break;
    case 5: // COMPLEX
      decor_category(patternSettings.displayPattern);
      break;
    case 6: // SPECIAL
      special_category(patternSettings.displayPattern);
      break;
    case 7: // SOUND REACTIVE
      soundReactive_category(patternSettings.displayPattern);
      break;
    case 8: // LEGACY
      legacy_category(patternSettings.displayPattern);
      break;
    case 9: // WEATHER REACTIVE
      weatherReactive_category(patternSettings.displayPattern);
      break;
  }
}

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
  case 0:
    basic_category(patternSettings.displayPattern);
    break;
  case 1:
    soundReactive_category(patternSettings.displayPattern);
    break;
  case 2:
    chill_category(patternSettings.displayPattern);
    break;
  case 3:
    moving_colors_category(patternSettings.displayPattern);
    break;
  case 4:
    chill_category(patternSettings.displayPattern);
    break;
  case 6:
    decor_category(patternSettings.displayPattern);
    break;
  }
}

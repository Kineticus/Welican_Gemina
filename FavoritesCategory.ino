void favorites_category(int patternMode)
{
  globalStrings.categoryName = "FAVORITES";

  patternSettings.displayPattern = patternSettings.favoritePattern[patternMode];

  if (patternSettings.displayPattern == 0)
  {
    if ((millis() - globals.randomTime) > globals.randomInterval)
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
    music_category(patternSettings.displayPattern);
    break;
  case 2:
    chill_category(patternSettings.displayPattern);
    break;
  case 3:
    moving_colors_category(patternSettings.displayPattern);
    break;
  case 4:
    legacy_category(patternSettings.displayPattern);
    break;
  }
}

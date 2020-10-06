void favorites_category(int patternMode)
{
  globalStrings.categoryName = "FAVORITES";

  switch (patternSettings.favoriteMode[patternMode])
  {
  case 0:
    basic_category(patternSettings.favoritePattern[patternMode]);
    break;
  case 1:
    music_category(patternSettings.favoritePattern[patternMode]);
    break;
  case 2:
    chill_category(patternSettings.favoritePattern[patternMode]);
    break;
  case 3:
    moving_colors_category(patternSettings.favoritePattern[patternMode]);
    break;
  case 4:
    legacy_category(patternSettings.favoritePattern[patternMode]);
    break;
  }
}

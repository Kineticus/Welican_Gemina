void magic_game()
{
  u8g2.setFont(u8g2_font_profont12_mf);
  u8g2.setCursor(SCREEN_WIDTH_HALF, 8);
  u8g2.print(magicWordsGame.gameName);

  u8g2.setCursor(SCREEN_WIDTH_HALF - 50, SCREEN_HEIGHT_HALF);
  u8g2.print(MAGIC_QUESTION[0]);
}

void magic_reset()
{
}
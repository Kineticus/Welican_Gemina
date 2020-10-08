void magic_game()
{
  u8g2.setFont(u8g2_font_profont12_mf);
  u8g2.setCursor(0, SCREEN_HEIGHT);
  u8g2.print(magicWordsGame.gameName);

  u8g2.setCursor(SCREEN_WIDTH - 30, SCREEN_HEIGHT);
  u8g2.print(MAGIC_QUESTION[0]);
}

void magic_reset()
{
}
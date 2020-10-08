void magic_game()
{
  u8g2.setFont(u8g2_font_profont12_mf);
  u8g2.setCursor(SCREEN_WIDTH_HALF - 30, 8);
  u8g2.print(magicWordsGame.gameName);

  if (magicWordsGame.answerMode == false)
  {
    u8g2.setCursor(SCREEN_WIDTH_HALF - 30, SCREEN_HEIGHT_HALF);
    u8g2.print(MAGIC_QUESTION[magicWordsGame.randomQuestionNumber]);

    if (knob1.click == 1)
    {
      magicWordsGame.answerMode = true;
    }
  }
  else
  {
    u8g2.setCursor(SCREEN_WIDTH_HALF - 30, SCREEN_HEIGHT_HALF);
    u8g2.print(MAGIC_ANSWERS[magicWordsGame.randomAnswerNumber]);

    if (knob1.click == 1)
    {
      magicWordsGame.answerMode = false;
    }
  }

  if (knob2.click == 1)
  {
    endGameMode();
  }
}

void magic_reset()
{
  magicWordsGame.answerMode = false;
}
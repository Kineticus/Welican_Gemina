void magic_game()
{
  u8g2.setFont(u8g2_font_profont12_mf);
  u8g2.setCursor(SCREEN_WIDTH_HALF - 30, 8);
  u8g2.print(magicWordsGame.gameName);

  if (magicWordsGame.answerMode == false)
  {
    u8g2.setCursor(SCREEN_WIDTH_HALF - 30, SCREEN_HEIGHT_HALF);
    u8g2.print("Question: ");

    u8g2.setCursor(SCREEN_WIDTH_HALF - 60, SCREEN_HEIGHT_HALF + 20);
    u8g2.print(MAGIC_QUESTION[magicWordsGame.randomQuestionNumber]);

    if (knob1.click == 1)
    {
      magicWordsGame.answerMode = true;
    }
  }
  else
  {
    u8g2.setCursor(SCREEN_WIDTH_HALF - 30, SCREEN_HEIGHT_HALF);
    u8g2.print("Answer: ");

    u8g2.setCursor(SCREEN_WIDTH_HALF - 60, SCREEN_HEIGHT_HALF + 20);
    u8g2.print(MAGIC_ANSWERS[magicWordsGame.randomAnswerNumber]);

    if (knob1.click == 1)
    {
      magicWordsGame.answerMode = false;
      resetQA();
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

void resetQA()
{
  magicWordsGame.randomQuestionArrSize = sizeof(MAGIC_QUESTION) / sizeof(MAGIC_QUESTION[0]);
  magicWordsGame.randomQuestionNumber = random(0, magicWordsGame.randomQuestionArrSize);
  magicWordsGame.randomAnswerArrSize = sizeof(MAGIC_ANSWERS) / sizeof(MAGIC_ANSWERS[0]);
  magicWordsGame.randomAnswerNumber = random(0, magicWordsGame.randomAnswerArrSize);
}
void drawMenuWords(String menuName, String first, String second, String third, String fourth = "")
{
  drawMenuTop(menuName);

  u8g2.setCursor(5, globalMenu.firstLineHorizontal);
  u8g2.print(first);
  u8g2.setCursor(69, globalMenu.firstLineHorizontal);
  u8g2.print(second);
  u8g2.setCursor(5, globalMenu.secondLineHorizontal);
  u8g2.print(third);

  if (fourth == "")
  {
    u8g2.setCursor(69, globalMenu.secondLineHorizontal);
    u8g2.print("Back");
  }
  else
  {
    u8g2.setCursor(69, globalMenu.secondLineHorizontal);
    u8g2.print(fourth);
  }
}

void drawMenuSelectionFrames()
{
  switch (globalMenu.menu[globalMenu.currentMenu])
  {
  case 0: // First Selection
    u8g2.drawRFrame(0,
                    globalMenu.firstLineHorizontal - globalMenu.selectionBubblePadding,
                    globalMenu.selectionBubbleWidth,
                    globalMenu.selectionBubbleHeight,
                    globalMenu.selectionBubbleRadius);
    break;
  case 1: // Second Selection
    u8g2.drawRFrame(globalMenu.verticalDividePosition,
                    globalMenu.firstLineHorizontal - globalMenu.selectionBubblePadding,
                    globalMenu.selectionBubbleWidth,
                    globalMenu.selectionBubbleHeight,
                    globalMenu.selectionBubbleRadius);
    break;
  case 2: // Third Selection
    u8g2.drawRFrame(0,
                    globalMenu.secondLineHorizontal - globalMenu.selectionBubblePadding,
                    globalMenu.selectionBubbleWidth,
                    globalMenu.selectionBubbleHeight,
                    globalMenu.selectionBubbleRadius);
    break;
  case 3: // Fourth Selection
    u8g2.drawRFrame(globalMenu.verticalDividePosition,
                    globalMenu.secondLineHorizontal - globalMenu.selectionBubblePadding,
                    globalMenu.selectionBubbleWidth,
                    globalMenu.selectionBubbleHeight,
                    globalMenu.selectionBubbleRadius);
    break;
  }
}

void drawMenuTop(String menuName)
{
  u8g2.setCursor(0, 8);
  u8g2.print(menuName);
}

void drawYesNoMenuFrame(String question)
{
  drawMenuTop(question);

  u8g2.setCursor(5, globalMenu.firstLineHorizontal);
  u8g2.print("No");
  u8g2.setCursor(69, globalMenu.firstLineHorizontal);
  u8g2.print("Yes");

  switch (globalMenu.menu[globalMenu.currentMenu])
  {
  case 0: // No
    u8g2.drawRFrame(0,
                    globalMenu.selectionBubblePadding,
                    globalMenu.selectionBubbleWidth,
                    globalMenu.selectionBubbleHeight,
                    globalMenu.selectionBubbleRadius);
    break;
  case 1: // Yes
    u8g2.drawRFrame(globalMenu.verticalDividePosition,
                    globalMenu.firstLineHorizontal - globalMenu.selectionBubblePadding,
                    globalMenu.selectionBubbleWidth,
                    globalMenu.selectionBubbleHeight,
                    globalMenu.selectionBubbleRadius);
    break;
  }
}

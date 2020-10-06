

void drawDebug()
{
  u8g2.setFont(u8g2_font_ncenB08_tr);

  drawMenuTop(VERSION_INFO);

  u8g2.setCursor(0, 24);
  u8g2.print("Knob 1: ");
  //u8g2.print(globals.encoder.getCount());
  u8g2.setCursor(80, 24);
  u8g2.print(patternSettings.pattern[globals.mode]);

  if (knob1.click == true)
  {
    u8g2.setCursor(0, 36);
    u8g2.print("CLICK");
  }
  u8g2.setCursor(0, 48);
  u8g2.print("Knob 2: ");
  //u8g2.print(globals.encoder2.getCount());
  if (knob2.click == true)
  {
    u8g2.setCursor(0, 60);
    u8g2.print("CLICK");
  }

  u8g2.setCursor(80, 48);
  u8g2.print(brightness.current);

  u8g2.setCursor(80, 64);
  u8g2.print(globals.mode);
}

void drawTop()
{
  //Only use top 16 rows!!
  u8g2.setFont(u8g2_font_profont12_mf);

  //Blackout box
  u8g2.setDrawColor(0);
  u8g2.drawBox(0, 0, VISUALIZER_Y, 16);
  u8g2.setDrawColor(1);

  switch (globals.mode)
  {
  case 0:
    u8g2.drawXBMP(0, 0, STAR_WIDTH, STAR_HEIGHT, WAVE);
    break;
  case 1:
    // u8g2.drawXBMP(0, 0, WAVE_WIDTH, WAVE_HEIGHT, WAVE);
    u8g2.drawXBMP(0, 0, MUSIC_NOTE_WIDTH, MUSIC_NOTE_HEIGHT, MUSIC_NOTE);
    break;
  case 2:
    u8g2.drawXBMP(0, 0, HASHTAG_WIDTH, HASHTAG_HEIGHT, HASHTAG);
    break;
  case 3:
    u8g2.drawXBMP(0, 0, DONUT_WIDTH, DONUT_HEIGHT, DONUT);
    break;
  case 4:
    u8g2.drawXBMP(0, 0, STAR_WIDTH, STAR_HEIGHT, STAR_SHAPE);
    break;
  case 5:
    u8g2.drawXBMP(0, 0, HEART_WIDTH, HEART_HEIGHT, HEART);
    break;
  }

  //u8g2.print(globals.mode);
  u8g2.setCursor(12, 8);
  u8g2.print(patternSettings.pattern[globals.mode]);
  u8g2.setCursor(32, 8);
  u8g2.print(globalStrings.functionNameOutString);
  //u8g2.drawXBMP(42,0,DONUT_WIDTH, DONUT_HEIGHT, DONUT);
  //u8g2.drawXBMP(54,0,MUSIC_NOTE_WIDTH, MUSIC_NOTE_HEIGHT, MUSIC_NOTE);
  //u8g2.drawXBMP(68,0,HEART_WIDTH, HEART_HEIGHT, HEART);

  //Hosting our own AP?
  u8g2.setCursor(112, 8);
  u8g2.print(globals.softAPEnable);

  /*
  WL_IDLE_STATUS	0
  WL_NO_SSID_AVAIL	1
  WL_SCAN_COMPLETED	2
  WL_CONNECTED	3
  WL_CONNECT_FAILED	4
  WL_CONNECTION_LOST	5
  WL_DISCONNECTED	6
  */
  //WiFi Status, see codes above
  u8g2.setCursor(120, 8);
  u8g2.print(WiFi.status());

  //WiFi Strength % (99 is MAX, 1 is MIN)
  //RSSItoPercent(WiFi.RSSI());

  u8g2_horizontal_line(16);
  drawProgressBar();
}

void drawBottom()
{
  int tempMode = globals.mode;

  if (globals.mode == 5) //favorites
  {
    tempMode = patternSettings.favoriteMode[patternSettings.pattern[globals.mode]];
  }

  switch (tempMode)
  {
  case 0:
    movingTriangles();
    break;
  case 1:
    drawCircleEQ();
    drawDiscSectionsEQ();
    drawEQ();
    break;
  case 2:
    gravityWell();
    break;
  case 3:
    drawIPAddress();
    break;
  case 4:
    starBounce();
    break;
  case 5:
    dvdBounce();
    break;
  }
}

void u8g2_horizontal_line(uint8_t a)
{
  u8g2.drawHLine(0, a, 128);
}

void drawProgressBar()
{
  int boxWidth = (SCREEN_WIDTH / globalMenu.patternMax[globals.mode]);
  if (boxWidth < 4)
  {
    boxWidth = 4;
  }
  u8g2.drawBox(((float(SCREEN_WIDTH - boxWidth) / globalMenu.patternMax[globals.mode]) * patternSettings.pattern[globals.mode]), 12, boxWidth, 4);
}

void showLogo(int millisTime)
{
  if (millis() < millisTime)
  {
    //Clear da buffer
    u8g2.clearBuffer();

    //Show logo
    u8g2.setBitmapMode(true /* transparent*/);
    u8g2.drawXBMP(32, 0, WELICAN_LOGO_WIDTH, WELICAN_LOGO_HEIGHT, WELICAN_LOGO);
  }
}

void drawClock()
{
  u8g2.setDrawColor(1);

  //7 Segment Style
  /*  
  u8g2.setFont(u8g2_font_7Segments_26x42_mn);
  if (globalTime.currentHour != 100) //Default setting is 100, so we know time is set
  {
    u8g2.setCursor(20, 64);

    if (globalTime.currentHour > 9)
    {
      u8g2.setCursor(-14, 64);
    }

    u8g2.print(globalTime.currentHour);
    
    u8g2.setCursor(50, 64);
    u8g2.print(":");
    
    u8g2.setCursor(68, 64);
    if (globalTime.currentMinute < 10)
    {
      u8g2.print("0");
    }
    u8g2.print(globalTime.currentMinute);
  } else
  {
    //u8g2.print("0:00");
    //Decided to just show nothing if we don't have a time sync
  }
  */

  //Flip Card style
  /*
  u8g2.setFont(u8g2_font_fub30_tn);
  if (globalTime.currentHour != 100) //Default setting is 100, so we know time is set
  {
    u8g2.setCursor(30, 64);

    if (globalTime.currentHour > 9)
    {
      u8g2.setCursor(0, 64);
    }

    u8g2.print(globalTime.currentHour);

    u8g2.setCursor(50, 60);
    u8g2.print(":");

    u8g2.setCursor(68, 64);
    if (globalTime.currentMinute < 10)
    {
      u8g2.print("0");
    }
    u8g2.print(globalTime.currentMinute);
  }
  else
  {
    //u8g2.print("0:00");
    //Decided to just show nothing if we don't have a time sync
  }
  */

  //Old Time style
  /*
  u8g2.setFont(u8g2_font_osb35_tn);
  if (globalTime.currentHour != 100) //Default setting is 100, so we know time is set
  {
    u8g2.setCursor(30, 64);

    if (globalTime.currentHour > 9)
    {
      u8g2.setCursor(0, 64);
    }

    u8g2.print(globalTime.currentHour);

    u8g2.setCursor(56, 60);
    u8g2.print(":");

    u8g2.setCursor(68, 64);
    if (globalTime.currentMinute < 10)
    {
      u8g2.print("0");
    }
    u8g2.print(globalTime.currentMinute);
  }
  else
  {
    //u8g2.print("0:00");
    //Decided to just show nothing if we don't have a time sync
  }
  */

  //Modern Font
  //u8g2.setFont(u8g2_font_logisoso38_tn);
  u8g2.setFont(u8g2_font_logisoso42_tn);
  if (globalTime.currentHour != 100) //Default setting is 100, so we know time is set
  {
    u8g2.setCursor(30, 60);

    if (globalTime.currentHour > 9)
    {
      u8g2.setCursor(0, 60);
    }

    u8g2.print(globalTime.currentHour);

    u8g2.setCursor(56, 56);
    u8g2.print(":");

    u8g2.setCursor(72, 60);
    if (globalTime.currentMinute < 10)
    {
      u8g2.print("0");
    }
    u8g2.print(globalTime.currentMinute);
  }
  else
  {
    //u8g2.print("0:00");
    //Decided to just show nothing if we don't have a time sync
  }
}

void showBrightnessDisplay()
{
  int frameX = 44;
  int frameY = 22;
  int frameW = 38;
  int frameH = 39;

  if (brightness.debounce > millis())
  {
    u8g2.setDrawColor(0);
    u8g2.drawBox(frameX, frameY - 1, frameW, frameH);
    u8g2.setDrawColor(1);
    u8g2.drawRFrame(frameX, frameY - 1, frameW, frameH, 7);

    if (brightness.current == 0)
    {
      u8g2.drawXBMP(frameX, frameY, brightness1_width, brightness1_height, brightness1);
    }
    else if (brightness.current == 255)
    {
      u8g2.drawXBMP(frameX, frameY, brightness8_width, brightness8_height, brightness8);
    }
    else if (brightness.current > 200)
    {
      u8g2.drawXBMP(frameX, frameY, brightness7_width, brightness7_height, brightness7);
    }
    else if (brightness.current > 160)
    {
      u8g2.drawXBMP(frameX, frameY, brightness6_width, brightness6_height, brightness6);
    }
    else if (brightness.current > 120)
    {
      u8g2.drawXBMP(frameX, frameY, brightness5_width, brightness5_height, brightness5);
    }
    else if (brightness.current > 80)
    {
      u8g2.drawXBMP(frameX, frameY, brightness4_width, brightness4_height, brightness4);
    }
    else if (brightness.current > 40)
    {
      u8g2.drawXBMP(frameX, frameY, brightness3_width, brightness3_height, brightness3);
    }
    else if (brightness.current > 0)
    {
      u8g2.drawXBMP(frameX, frameY, brightness2_width, brightness2_height, brightness2);
    }
  }
}

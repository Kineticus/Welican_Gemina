

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
  case 0: // Basic Category
    u8g2.drawXBMP(0, 0, WAVE_WIDTH, WAVE_HEIGHT, WAVE);
    break;
  case 1: // Music Category
    u8g2.drawXBMP(0, 0, MUSIC_NOTE_WIDTH, MUSIC_NOTE_HEIGHT, MUSIC_NOTE);
    break;
  case 2: // Chill Category
    u8g2.drawXBMP(0, 0, HASHTAG_WIDTH, HASHTAG_HEIGHT, HASHTAG);
    break;
  case 3: // Moving Colors
    u8g2.drawXBMP(0, 0, DONUT_WIDTH, DONUT_HEIGHT, DONUT);
    break;
  case 4: // Legacy
    u8g2.drawXBMP(0, 0, HASHTAG_WIDTH, HASHTAG_HEIGHT, HASHTAG);
    break;
  case 5: // Favorites
    u8g2.drawXBMP(0, 0, HEART_WIDTH, HEART_HEIGHT, STAR_SHAPE);
    break;
  case 6: // Palette
    u8g2.drawXBMP(0, 0, WAVE_WIDTH, WAVE_HEIGHT, WAVE);
    break;
  }

  //u8g2.print(globals.mode);
  u8g2.setCursor(12, 8);
  if ((patternSettings.pattern[globals.mode] == 0) || ((globals.mode == 5) && (patternSettings.favoritePattern[patternSettings.pattern[globals.mode]] == 0)))
  {
    u8g2.print("RM");
  }
  else
  {
    u8g2.print(patternSettings.pattern[globals.mode]);
  }

  u8g2.setCursor(32, 8);
  u8g2.print(globalStrings.functionNameOutString);
  //u8g2.drawXBMP(42,0,DONUT_WIDTH, DONUT_HEIGHT, DONUT);
  //u8g2.drawXBMP(54,0,MUSIC_NOTE_WIDTH, MUSIC_NOTE_HEIGHT, MUSIC_NOTE);
  //u8g2.drawXBMP(68,0,HEART_WIDTH, HEART_HEIGHT, HEART);

  //Hosting our own AP?
  if (globals.softAPEnable == 1)
  {
    u8g2.setCursor(112, 8);
    u8g2.print("T");
  }

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
  //u8g2.setCursor(120, 8);
  //u8g2.print(WiFi.status());

  EVERY_N_MILLISECONDS(1000)
  {
    globals.signalStrength = 0;

    if (WiFi.status() == 3)
    {
      globals.signalStrength = RSSItoStrength(WiFi.RSSI());
    }
  }

  switch (globals.signalStrength)
  {
  case 0:
    u8g2.drawXBMP(119, 0, WIFI_0_WIDTH, WIFI_0_HEIGHT, WIFI_0);
    break;
  case 1:
    // u8g2.drawXBMP(0, 0, WAVE_WIDTH, WAVE_HEIGHT, WAVE);
    u8g2.drawXBMP(119, 0, WIFI_1_WIDTH, WIFI_1_HEIGHT, WIFI_1);
    break;
  case 2:
    u8g2.drawXBMP(119, 0, WIFI_2_WIDTH, WIFI_2_HEIGHT, WIFI_2);
    break;
  case 3:
    u8g2.drawXBMP(119, 0, WIFI_3_WIDTH, WIFI_3_HEIGHT, WIFI_3);
    break;
  case 4:
    u8g2.drawXBMP(119, 0, WIFI_4_WIDTH, WIFI_4_HEIGHT, WIFI_4);
    break;
  }

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
    //movingTriangles();
    lavaLamp(5, 128, 0, 0, millis() / 50);
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
    //lavaLampFast(20, 128, 0, 0, millis() / 33);
    break;
  case 4:
    starBounce();
    break;
  case 5:
    //Will show favorite category
    break;
  case 6:
    lavaLamp(5, 128, 0, millis() / 50, 0);
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
  
  //Draw borders for testing if desired
  if (1 == 0)
  {
    u8g2.drawVLine(0, 0, SCREEN_HEIGHT);
    u8g2.drawVLine(SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    u8g2.drawHLine(0, 0, SCREEN_WIDTH);
    u8g2.drawHLine(0, SCREEN_HEIGHT, SCREEN_WIDTH + 1);
  }

  switch (globalMenu.menu[26])
  {
  case 0: //7 Segment Style
  {
    dateTemp1();
    timeSegment();
  }
  break;
  case 1: //Flip Card style
  {
    dateTemp1();
    timeFlip();
  }
  break;
  case 2: //Old Time style
  {
    dateTemp1();
    timeOlde();
  }
  break;
  case 3: //Modern Font 
  {
    timeModern();
  }
  break;
  case 4: //Modern Font 2
  {
    dateTemp1();
    timeModern();
  }
  break;
  case 5: //Modern Font 2
  {
    dateTemp1();
    timeModern();
    lavaLamp(5, 128, 0, millis() / 50, 0);
  }
  break;
  case 6:
  {
    dateTemp5();
    lavaLamp(5, 128, 0, millis() / 50, 0);
  }
  break;
  case 7:
  { 
    dateTemp5();
    u8g2.setBitmapMode(true /* transparent*/);
    u8g2.drawXBMP(32, 0, WELICAN_LOGO_WIDTH, WELICAN_LOGO_HEIGHT, WELICAN_LOGO);
    lavaLamp(5, 128, 0, millis() / 50, 0);
  }
  break;
  case 8:
  {
    lavaLamp(5, 128, 0, 0, millis() / 50);
  }
  break;
  case 10: //Weather 1
  {
    u8g2.setFont(u8g2_font_profont12_mf);
    u8g2.setCursor(10, 10);
    u8g2.print(weather.currentWeatherTitle);
    u8g2.setCursor(10, 20);
    u8g2.print(weather.currentWeatherDescription);

    u8g2.setCursor(10, 30);
    u8g2.print(String(weather.currentTemperature));
    u8g2.setCursor(40, 30);
    u8g2.print(String(weather.currentTemperatureMin));
    u8g2.setCursor(55, 30);
    u8g2.print(" - ");
    u8g2.setCursor(70, 30);
    u8g2.print(String(weather.currentTemperatureMax));

    String sunrise = "rise: ";
    sunrise += String(weather.sunrise);
    String sunset = "set: ";
    sunset += String(weather.sunset);

    u8g2.setCursor(10, 40);
    u8g2.print(sunrise);
    u8g2.setCursor(10, 60);
    u8g2.print(sunset);
  }
  break;
  case 11: //Weather 2
  {
    u8g2.setCursor(10, 10);
    u8g2.print(weather.currentWeatherDescription);

    u8g2.setCursor(10, 20);
    u8g2.print(String(weather.currentTemperature));
    u8g2.setCursor(40, 20);
    u8g2.print(String(weather.currentTemperatureMin));
    u8g2.setCursor(55, 20);
    u8g2.print(" - ");
    u8g2.setCursor(70, 20);
    u8g2.print(String(weather.currentTemperatureMax));
  }
  break;
  case 12: //Weather 3
  {
    u8g2.setCursor(10, 10);
    u8g2.print(weather.currentWeatherTitle);

    u8g2.setCursor(10, 20);
    u8g2.print(String(weather.currentTemperature));
    u8g2.setCursor(40, 20);
    u8g2.print(String(weather.currentTemperatureMin));
    u8g2.setCursor(55, 20);
    u8g2.print(" - ");
    u8g2.setCursor(70, 20);
    u8g2.print(String(weather.currentTemperatureMax));
  }
  break;
  case 13: //Weather 4
  {
    u8g2.setCursor(10, 0);
    u8g2.print(weather.currentWeatherTitle);
    u8g2.setCursor(10, 20);
    u8g2.print(weather.currentWeatherDescription);

    String sunrise = "rise: ";
    sunrise += String(weather.sunrise);
    String sunset = "set: ";
    sunset += String(weather.sunset);

    u8g2.setCursor(10, 30);
    u8g2.print(sunrise);
    u8g2.setCursor(10, 50);
    u8g2.print(sunset);
  }
  break;
  case 14: //Test
  {
    u8g2.drawXBMP(20, 20, FACE_SMIRK_0_WIDTH, FACE_SMIRK_0_HEIGHT, FACE_SMIRK_0);
    u8g2.drawXBMP(60, 20, FACE_SMIRK_1_WIDTH, FACE_SMIRK_1_HEIGHT, FACE_SMIRK_1);
  }
  }
}

void dateTemp1()
{
  u8g2.setFont(u8g2_font_profont12_mf);

  //Print Date
  //Sun Dec  6th
  u8g2.setCursor(50, 10);
  char buf[80];
  strftime(buf, sizeof(buf), "%a %b %e", &timeinfo);
  u8g2.print(buf);
  u8g2.print(dateOrdinal());

  //Temperature in Upper Left
  u8g2.setCursor(2, 10);
  u8g2.print(weather.currentTemperature);
  u8g2.print("\xb0 "); //Degree symbol

}

void dateTemp2()
{
  u8g2.setFont(u8g2_font_profont12_mf);

  //Print Date 
  //Sunday December  6th
  char buf[80];
  strftime(buf, sizeof(buf), "%A, %b. %e", &timeinfo);
  u8g2.setCursor(5, 10);
  u8g2.print(buf);
  u8g2.print(dateOrdinal());
}

void dateTemp3()
{
  u8g2.setFont(u8g2_font_profont12_mf);

  //Print Date
  //12/06/20
  char buf[80];
  strftime(buf, sizeof(buf), "%D", &timeinfo);
  u8g2.setCursor(80, 10);
  u8g2.print(buf);

  //Temperature in Upper Left
  u8g2.setCursor(2, 10);
  u8g2.print(weather.currentTemperature);
  u8g2.print("\xb0 "); //Degree symbol
}

void dateTemp4()
{
  u8g2.setFont(u8g2_font_profont12_mf);

  //Print Date
  //Sun  6
  char buf[80];
  strftime(buf, sizeof(buf), "%a %e", &timeinfo);
  u8g2.setCursor(90, 10);
  u8g2.print(buf);

  //Temperature in Upper Left
  u8g2.setCursor(2, 10);
  u8g2.print(weather.currentTemperature);
  u8g2.print("\xb0 "); //Degree symbol
}

void dateTemp5()
{
  u8g2.setFont(u8g2_font_profont12_mf);

  //Print Time
  //04:20
  char buf[80];
  strftime(buf, sizeof(buf), "%I:%M", &timeinfo);
  u8g2.setCursor(95, 10);
  u8g2.print(buf);

  //Temperature in Upper Left
  u8g2.setCursor(4, 10);
  u8g2.print(weather.currentTemperature);
  u8g2.print("\xb0 "); //Degree symbol
}


void timeSegment()
{
  u8g2.setFont(u8g2_font_7Segments_26x42_mn);
  if (globalTime.currentHour != 100) //Default setting is 100, so we know time is set
  {
    u8g2.setCursor(20, 64);

    if ((globalTime.currentHour > 9) || (globalTime.currentHour == 0))
    {
      u8g2.setCursor(-14, 64);
    }

    if (globalTime.currentHour == 0)
    {
      u8g2.print("12");
    }
    else
    {
      u8g2.print(globalTime.currentHour);
    }

    u8g2.setCursor(50, 64);
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
}

void timeFlip()
{
  u8g2.setFont(u8g2_font_fub30_tn);
  if (globalTime.currentHour != 100) //Default setting is 100, so we know time is set
  {
    u8g2.setCursor(30, 64);

    if ((globalTime.currentHour > 9) || (globalTime.currentHour == 0))
    {
      u8g2.setCursor(0, 64);
    }

    if (globalTime.currentHour == 0)
    {
      u8g2.print("12");
    }
    else
    {
      u8g2.print(globalTime.currentHour);
    }

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
}

void timeModern()
{
  u8g2.setFont(u8g2_font_logisoso42_tn);
  if (globalTime.currentHour != 100) //Default setting is 100, so we know time is set
  {
    u8g2.setCursor(30, 62);

    if ((globalTime.currentHour > 9) || (globalTime.currentHour == 0))
    {
      u8g2.setCursor(0, 62);
    }

    if (globalTime.currentHour == 0)
    {
      u8g2.print("12");
    }
    else
    {
      u8g2.print(globalTime.currentHour);
    }

    u8g2.setCursor(56, 58);
    u8g2.print(":");

    u8g2.setCursor(72, 62);
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

void timeOlde()
{
  u8g2.setFont(u8g2_font_osr41_tn);

  if (globalTime.currentHour != 100) //Default setting is 100, so we know time is set
  {
    u8g2.setCursor(20, 64);

    if ((globalTime.currentHour > 9) || (globalTime.currentHour == 0))
    {
      u8g2.setCursor(-5, 64);
    }

    if ((globalTime.currentHour == 0) || (globalTime.currentHour == 12))
    {
      u8g2.print("1");
      u8g2.setCursor(21, 64);
      u8g2.print("2");
    }
    else
    {
      u8g2.print(globalTime.currentHour);
    }

    u8g2.setCursor(55, 60);
    u8g2.print(":");

    u8g2.setCursor(64, 64);
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

void newFavoritesMenu()
{
  u8g2.setFont(u8g2_font_profont12_mf);
  drawMenuTop("Add New Favorite");

  //This is a menu with patternSettings.numberOfFavorites 'selections', each indicating a favorite slot
  if (globalMenu.menu[globalMenu.currentMenu] < 10)
  {
    u8g2.setCursor(55, 46);
  }
  else
  {
    u8g2.setCursor(40, 46);
  }

  if (globalMenu.menu[globalMenu.currentMenu] < 1)
  {
    globalMenu.menu[globalMenu.currentMenu] = 1;
  }

  u8g2.setFont(u8g2_font_fub30_tn);

  u8g2.print(globalMenu.menu[globalMenu.currentMenu]);

  //u8g2.drawRFrame(50, 14, 20, 16, 3);

  //Call the favorite for the slot we're looking at
  //The real function call is below this, so LEDs will not show bad data

  if (patternSettings.favoritePattern[globalMenu.menu[globalMenu.currentMenu]] == 0)
  {
    globalStrings.functionName = "Randomizer";
  }
  else
  {
    //Backup current RGB Settings
    for (int i = 0; i < NUM_LEDS; i++)
    {
      patternSettings.tempLeds[i] = patternSettings.leds[i];
    }

    //Run existing favorite category to get string name
    favorites_category(globalMenu.menu[globalMenu.currentMenu]);

    //Restore RGB settings
    for (int i = 0; i < NUM_LEDS; i++)
    {
      patternSettings.leds[i] = patternSettings.tempLeds[i];
    }
  }

  //Convert the strings
  globalStrings.functionName.toCharArray(globalStrings.functionNameOutString, 20);
  globalStrings.categoryName.toCharArray(globalStrings.categoryNameOutString, 20);

  u8g2.setFont(u8g2_font_profont12_mf);
  u8g2.setCursor(16, 44);
  //u8g2.print("Current Setting");
  //u8g2.print(globalStrings.categoryNameOutString);

  switch (patternSettings.favoriteMode[globalMenu.menu[globalMenu.currentMenu]])
  {
  case 0:
    u8g2.drawXBMP(2, 53, STAR_WIDTH, STAR_HEIGHT, WAVE);
    break;
  case 1:
    // u8g2.drawXBMP(0, 0, WAVE_WIDTH, WAVE_HEIGHT, WAVE);
    u8g2.drawXBMP(2, 53, MUSIC_NOTE_WIDTH, MUSIC_NOTE_HEIGHT, MUSIC_NOTE);
    break;
  case 2:
    u8g2.drawXBMP(2, 53, HASHTAG_WIDTH, HASHTAG_HEIGHT, HASHTAG);
    break;
  case 3:
    u8g2.drawXBMP(2, 53, DONUT_WIDTH, DONUT_HEIGHT, DONUT);
    break;
  case 4:
    u8g2.drawXBMP(2, 53, STAR_WIDTH, STAR_HEIGHT, STAR_SHAPE);
    break;
  case 5:
    u8g2.drawXBMP(2, 53, HEART_WIDTH, HEART_HEIGHT, HEART);
    break;
  }
  u8g2.setCursor(12, 60);
  u8g2.print(globalStrings.functionNameOutString);
}

void showBrightnessDisplay()
{
  int frameX = 44;
  int frameY = 22;
  int frameW = 38;
  int frameH = 39;

  //Draw Brightness Adjustment
  if ((brightness.debounce > millis()) && (brightness.debounce > brightness.debounce2))
  {
    u8g2.setDrawColor(0);
    u8g2.drawBox(frameX, frameY - 1, frameW, frameH);
    u8g2.setDrawColor(1);
    u8g2.drawRFrame(frameX, frameY - 1, frameW, frameH, 7);

    if (brightness.target == 0)
    {
      u8g2.drawXBMP(frameX, frameY, brightness1_width, brightness1_height, brightness1);
    }
    else if (brightness.target == 255)
    {
      u8g2.drawXBMP(frameX, frameY, brightness8_width, brightness8_height, brightness8);
    }
    else if (brightness.target > 200)
    {
      u8g2.drawXBMP(frameX, frameY, brightness7_width, brightness7_height, brightness7);
    }
    else if (brightness.target > 160)
    {
      u8g2.drawXBMP(frameX, frameY, brightness6_width, brightness6_height, brightness6);
    }
    else if (brightness.target > 120)
    {
      u8g2.drawXBMP(frameX, frameY, brightness5_width, brightness5_height, brightness5);
    }
    else if (brightness.target > 80)
    {
      u8g2.drawXBMP(frameX, frameY, brightness4_width, brightness4_height, brightness4);
    }
    else if (brightness.target > 40)
    {
      u8g2.drawXBMP(frameX, frameY, brightness3_width, brightness3_height, brightness3);
    }
    else if (brightness.target > 0)
    {
      u8g2.drawXBMP(frameX, frameY, brightness2_width, brightness2_height, brightness2);
    }
  }

  //Draw Pattern Adjustment
  if ((brightness.debounce2 > millis()) && (brightness.debounce2 > brightness.debounce))
  {
    u8g2.setFont(u8g2_font_profont12_mf);
    u8g2.setDrawColor(0);
    u8g2.drawBox(frameX, frameY - 1, frameW, frameH);
    u8g2.setDrawColor(1);

    u8g2.setCursor(61, 31);

    if (patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]] > 9)
    {
      u8g2.setCursor(58, 31);
    }
    if (patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]] > 99)
    {
      u8g2.setCursor(55, 31);
    }

    u8g2.print(patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);

    //Constrain a 0-255 value to 1/2 of a circle
    tA.point1 = 5.8 - float(patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]) * .021;

    //Calculate point on circle
    tA.x1 = tA.x + (tA.radius * sin(tA.point1)) + .5;
    tA.y1 = tA.y + (tA.radius * cos(tA.point1)) + .5;

    //Draw a circle
    u8g2.drawCircle(tA.x, tA.y, tA.radius, U8G2_DRAW_ALL);

    //Notch it out
    u8g2.setDrawColor(0);
    u8g2.drawBox(tA.x - 17, tA.y + 12, 35, 5);
    u8g2.setDrawColor(1);

    //Draw a line
    u8g2.drawLine(tA.x1, tA.y1, tA.x, tA.y);

    //Frame it up
    u8g2.drawRFrame(frameX, frameY - 1, frameW, frameH, 7);

    /* Show a dot
    u8g2.drawDisc(tA.x1, tA.y1, 5, U8G2_DRAW_ALL);
    */
  }
}

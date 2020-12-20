void debugScreenOutline(bool on = false) 
{
  if (on)
  {
    u8g2.drawVLine(0, 0, SCREEN_HEIGHT);
    u8g2.drawVLine(SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    u8g2.drawHLine(0, 0, SCREEN_WIDTH);
    u8g2.drawHLine(0, SCREEN_HEIGHT, SCREEN_WIDTH + 1);
  }
}

void drawDebug()
{
  u8g2.setFont(u8g2_font_b12_b_t_japanese1);

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

void drawWeatherIcon(int posX, int posY)
{
  if (weather.currentWeatherId.startsWith("2")) 
  {
    animateImages(posX, posY, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_SUNNY_0, WEATHER_SUNNY_1);
  } else if (weather.currentWeatherId.startsWith("3")) 
  {
    animateImages(posX, posY, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_LIGHT_RAIN_0, WEATHER_LIGHT_RAIN_1);
  } else if (weather.currentWeatherId.startsWith("5")) 
  {
    animateImages(posX, posY, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_RAINY_DAY_0, WEATHER_RAINY_DAY_1);
  } else if (weather.currentWeatherId.startsWith("6")) 
  {
    animateImages(posX, posY, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_SNOW_0, WEATHER_SNOW_1);
  } else if (weather.currentWeatherId == "800") 
  {
    animateImages(posX, posY, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_SUNNY_0, WEATHER_SUNNY_1);
  } else if (weather.currentWeatherId.startsWith("80")) 
  {
    animateImages(posX, posY, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_PARTLY_CLOUDY_0, WEATHER_PARTLY_CLOUDY_1);
  }
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
    case 0: // FAVORITES
      u8g2.drawXBMP(0, 0, STAR_WIDTH, STAR_HEIGHT, STAR_SHAPE);
      break;
    case 1: // BASIC
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_0);
      break;
    case 2: // DECOR
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_1);
      break;
    case 3: // PARTY
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_2);
      break;
    case 4: // ADVANCED
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_3);
      break;
    case 5: // COMPLEX
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_4);
      break;
    case 6: // SPECIAL
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_5);
      break;
    case 7: // SOUND REACTIVE
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_6);
      break;
    case 8: // LEGACY
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_7);
      break;
    case 9: // WEATHER REACTIVE
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_8);
      break;
  }

  u8g2.setCursor(12, 8);
  if ((patternSettings.pattern[globals.mode] == 0) || ((globals.mode == 5) && (patternSettings.favoritePattern[patternSettings.pattern[globals.mode]] == 0)))
  {
    u8g2.print("RM");
  }
  else
  {
    u8g2.print(patternSettings.pattern[globals.mode]);
  }

  //Simple style top
  u8g2.setCursor(32, 8);
  u8g2.print(globalStrings.functionNameOutString);

  //Advanced style
  /* 
  if (globals.animationFrame % 2) {
    u8g2.setCursor(28, 8);
  
    if (sizeof(globalStrings.categoryNameOutString)/sizeof(globalStrings.categoryNameOutString[0]) > 7) {
      u8g2.setFont(u8g2_font_ncenB08_tr);
    } else {
      u8g2.setFont(u8g2_font_blipfest_07_tr);
    }
    
    u8g2.print(globalStrings.categoryNameOutString);
  } else {
    u8g2.setFont(u8g2_font_blipfest_07_tr);
    u8g2.setCursor(69, 8);
    u8g2.print(globalStrings.functionNameOutString);
  }
  EVERY_N_MILLISECONDS(1500)
  {
   globals.animationFrame++;
  }

  if (globals.animationFrame > 10) {
    globals.animationFrame = 0;
  }
  */

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

  if (globals.mode == 0) //favorites
  {
    tempMode = patternSettings.favoriteMode[patternSettings.pattern[globals.mode]];
  }

  switch (tempMode)
  {
  case 0: // FAVORITES
    //Will show favorite category
    break;
  case 1: // BASIC
    gravityWell();
    break;
  case 2: // DECOR
    lavaLamp(5, 128, 0, millis() / 50, 0);
    break;
  case 3: // PARTY
    lavaLampFast(20, 128, 0, 0, millis() / 33);
    break;
  case 4: // ADVANCED
    movingTriangles();
    break;
  case 5: // COMPLEX
    lavaLamp(10, 128, 0, millis() / 50, 0);
    break;
  case 6: // SPECIAL
    starBounce();
    break;
  case 7: // WEATHER REACTIVE
    drawCircleEQ();
    drawDiscSectionsEQ();
    drawEQ();
    break;
  case 8: // BASIC
    dvdBounce();
    lavaLamp(10, 128, 0, millis() / 50, 0);
    break;
  case 9: // SOUND REACTIVE
    //lavaLamp(15, 128, 0, millis() / 50, 0);
    drawEQ();
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

void drawClock(int Selection)
{
  u8g2.setDrawColor(1);
  
  //Draw borders for testing if desired
  debugScreenOutline(false);

  switch (Selection)
  {
    case 1: //7 Segment Style
    {
      dateTemp1();
      timeSegment();
    }
    break;
    case 2: //Flip Card style
    {
      dateTemp1();
      timeFlip();
    }
    break;
    case 3: //Old Time style
    {
      dateTemp1();
      timeOlde();
    }
    break;
    case 4: //Modern Font 
    {
      timeModern();
    }
    break;
    case 5: //Modern Font 2
    {
      dateTemp1();
      timeModern();
    }
    break;
    case 6: //Modern Font 2
    {
      dateTemp1();
      timeModern();
      lavaLamp(5, 128, 0, millis() / 50, 0);
    }
    break;
    case 7:
    {
      dateTemp5();
      lavaLamp(5, 128, 0, millis() / 50, 0);
    }
    break;
    case 8:
    { 
      dateTemp5();
      u8g2.setBitmapMode(true /* transparent*/);
      u8g2.drawXBMP(32, 0, WELICAN_LOGO_WIDTH, WELICAN_LOGO_HEIGHT, WELICAN_LOGO);
      lavaLamp(5, 128, 0, millis() / 50, 0);
    }
    break;
    case 9:
    {
      lavaLamp(5, 128, 0, 0, millis() / 50);
    }
    break;
    case 10: //Weather 1
    {
      u8g2.setFont(u8g2_font_profont12_mf);
      u8g2.setFontMode(1);

      //Row 1
      u8g2.setCursor(0, 9);
      char buf[80];
      strftime(buf, sizeof(buf), "%a %b %e", &timeinfo);
      u8g2.print(buf);
      u8g2.print(dateOrdinal());
      u8g2.print("    ");
      u8g2.print(String(weather.currentTemperature));
      u8g2.print("\xb0 "); //Degree symbol

      //Row 2
      u8g2.setCursor(0, 20);
      u8g2.print(weather.currentWeatherTitle);
      u8g2.print(", ");
      u8g2.print(weather.currentWeatherDescription);

      //Row 3
      u8g2.setCursor(0, 31);
      u8g2.print("High ");
      u8g2.print(String(weatherCurrentDay.tempMax));
      u8g2.print("\xb0 "); //Degree symbol
      u8g2.print(" Low ");
      u8g2.print(String(weatherCurrentDay.tempMin));
      u8g2.print("\xb0 "); //Degree symbol

      //Row 4
      u8g2.setCursor(0, 42);
      u8g2.print("Rain ");
      u8g2.print(String(int(weatherCurrentDay.pop * 100)));
      u8g2.print("%  Humid ");
      u8g2.print(weather.currentHumidity);
      u8g2.print("%");

      //Row 5
      String sunrise = "Sunrise ";
      sunrise += String(weather.sunrise);
      u8g2.setCursor(0, 53);
      u8g2.print(sunrise);

      //Row 6
      u8g2.setCursor(0, 64);
      String sunset = "Sunset  ";
      sunset += String(weather.sunset);
      u8g2.print(sunset);
    }
    break;
    case 11: //Weather 2
    {
      drawWeatherIcon(0, 0);
      lavaLamp(5, 128, 0, millis() / 50, 0);

      u8g2.setFont(u8g2_font_profont12_mf);
      u8g2.setFontMode(1);

      int posXRightOfIcon = 37; // 5px padding
      int posX = 2; // 2x padding (under icon)
      int posYUnderIcon = 44;

      // first row
      u8g2.setCursor(posXRightOfIcon, 10);
      u8g2.print(weather.currentWeatherTitle);
      u8g2.setCursor(posXRightOfIcon, 20);
      u8g2.print(weather.currentWeatherDescription);

      // Under Animated Icon
      showLargeTime(3, 60);

      // Bottom Right - Temp
      largeTemp(100, 60, weather.currentTemperature);
    }
    break;
    case 12: //Weather 3
    {
      drawWeatherIcon(0, 0);
      u8g2.setFont(u8g2_font_profont12_mf);
      u8g2.setFontMode(1);

      int posXRightOfIcon = 37; // 5px padding
      int posX = 2; // 2x padding (under icon)
      int posYUnderIcon = 44;

      // first row
      u8g2.setCursor(posXRightOfIcon, 10);
      u8g2.print(weather.currentWeatherTitle);
      u8g2.setCursor(posXRightOfIcon, 20);
      u8g2.print(weather.currentWeatherDescription);

      // Under Animated Icon
      showLargeTimeSegment(3, 60);

      // Bottom Right - Temp
      largeTemp(100, 60, weather.currentTemperature);
    }
    break;
    case 13: //Weather 4
    {
      drawWeatherIcon(0, 0);
      u8g2.setFont(u8g2_font_profont12_mf);
      u8g2.setFontMode(1);

      int posXRightOfIcon = 37; // 5px padding
      int posX = 2; // 2x padding (under icon)
      int posYUnderIcon = 44;

      // first row
      u8g2.setCursor(posXRightOfIcon, 10);
      u8g2.print(weather.currentWeatherTitle);
      u8g2.setCursor(posXRightOfIcon, 20);
      u8g2.print(weather.currentWeatherDescription);

      // Under Animated Icon
      showLargeTime(3, 60);

      // Bottom Right - Temp
      largeTemp(100, 60, weather.currentTemperature);
    }
    break;
    case 14: //Weather  - rain % and UVI and cloudiness
    {
      drawWeatherIcon(0, 0);
      u8g2.setFont(u8g2_font_blipfest_07_tr);
      u8g2.setFontMode(1);

      int posXRightOfIcon = 37; // 5px padding
      int posX = 2; // 2x padding (under icon)
      int posYUnderIcon = 44;

      // first row
      u8g2.setCursor(posXRightOfIcon, 10);
      u8g2.print(weather.currentWeatherDescription);

      // second row - large font
      u8g2.setFont(u8g2_font_fub14_tr);
      u8g2.setCursor(posXRightOfIcon, 26);
      u8g2.print(String(int(weatherCurrentDay.pop * 100)));
      // second row - small font
      u8g2.setFont(u8g2_font_profont10_mf);
      u8g2.setCursor(posXRightOfIcon + 37, 26);
      u8g2.print("% rain");
      
      // Under Animated Icon
      u8g2.setFont(u8g2_font_profont10_mf);
      u8g2.setCursor(posX, posYUnderIcon);
      u8g2.print("wind speed: ");
      // Under Animated Icon - large font
      u8g2.setFont(u8g2_font_fub14_tr);
      u8g2.setCursor(posX + 54, posYUnderIcon);
      u8g2.print(String(weatherCurrentDay.windSpeed));
      u8g2.setFont(u8g2_font_profont10_mf);
      u8g2.setCursor(posX + 78, posYUnderIcon);
      u8g2.print("mph");

      // bottom row
      // Date time
      char buf[80];
      strftime(buf, sizeof(buf), "%a %D", &timeinfo);
      u8g2.setFont(u8g2_font_profont12_mf);
      u8g2.setCursor(3, 60); 
      u8g2.print(buf);

      // Bottom Right - Temp
      largeTemp(100, 60, weather.currentTemperature);
    }
    break;
    case 15: //Weather - Temps
    {
      drawWeatherIcon(0, 0);
      u8g2.setFont(u8g2_font_profont12_mf);
      u8g2.setFontMode(1);

      int posXRightOfIcon = 37; // 5 Xpadding
      int posX = 3; // 2x padding (under icon)
      int posYUnderIcon = 44;

      u8g2.setCursor(posXRightOfIcon, 10);
      u8g2.print(weather.currentWeatherTitle);
      u8g2.setFont(u8g2_font_profont12_mf);
      u8g2.setCursor(posXRightOfIcon, 20);
      u8g2.print(weather.currentWeatherDescription);

      // Under Animated Icon
      u8g2.setFont(u8g2_font_profont10_mf);
      u8g2.setCursor(posX, posYUnderIcon);
      u8g2.print("Range: ");
      largeTemp(posXRightOfIcon - 4, posYUnderIcon, weather.currentTemperatureMin);

      u8g2.setFont(u8g2_font_fub14_tr);
      u8g2.setCursor(posXRightOfIcon + 18, posYUnderIcon);
      u8g2.print(" - ");
      
      largeTemp(posXRightOfIcon + 36, posYUnderIcon, weather.currentTemperatureMax);

      // bottom row
      // Date time
      char buf[80];
      strftime(buf, sizeof(buf), "%m/%d/%Y", &timeinfo);
      u8g2.setFont(u8g2_font_profont12_mf);
      u8g2.setCursor(posX, 60); 
      u8g2.print(buf);
      // u8g2.print(dateOrdinal());

      // Temp
      largeTemp(100, 60, weather.currentTemperature);
    }
    break;
    case 16: //Weather - Humidity D
    {
      drawWeatherIcon(0, 0);
      u8g2.setFont(u8g2_font_profont12_mf);
      u8g2.setFontMode(1);

      int posXRightOfIcon = 37; // 5 Xpadding
      int posX = 3; // 2x padding (under icon)
      int posYUnderIcon = 44;

      u8g2.setCursor(posXRightOfIcon, 10);
      u8g2.print(weather.currentWeatherTitle);
      u8g2.setFont(u8g2_font_profont12_mf);
      u8g2.setCursor(posXRightOfIcon, 20);
      u8g2.print(weather.currentWeatherDescription);

      // Under Animated Icon
      u8g2.setFont(u8g2_font_profont10_mf);
      u8g2.setCursor(posX, posYUnderIcon);
      u8g2.print("humidity");
      u8g2.setFont(u8g2_font_fub14_tr);
      u8g2.setCursor(posXRightOfIcon + 6, posYUnderIcon);
      u8g2.print(String(weatherCurrentDay.humidity));
      
      u8g2.setFont(u8g2_font_profont10_mf);
      u8g2.setCursor(posXRightOfIcon + 30, posYUnderIcon);
      u8g2.print("dew pnt");
      u8g2.setFont(u8g2_font_fub14_tr);
      u8g2.setCursor(posXRightOfIcon + 65, posYUnderIcon);
      u8g2.print(String(weatherCurrentDay.dewPoint));
      
      // bottom row
      // Date time
      char buf[80];
      strftime(buf, sizeof(buf), "%m/%d/%Y", &timeinfo);
      u8g2.setFont(u8g2_font_profont12_mf);
      u8g2.setCursor(posX, 60); 
      u8g2.print(buf);
      // u8g2.print(dateOrdinal());

      // Temp: 
      largeTemp(100, 60, weather.currentTemperature);
    }
    break;
    case 17: //Weather - Sunrise/Set
    {
      drawWeatherIcon(0, 0);
      animateImages(96, 0, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_SUNNY_0, WEATHER_SUNNY_1);

      u8g2.setFont(u8g2_font_blipfest_07_tr);
      u8g2.setFontMode(1);

      int posXRightOfIcon = 37; // 5px padding
      int posX = 2; // 2x padding (under icon)
      int posYUnderIcon = 44;

      // first row
      u8g2.setCursor(posXRightOfIcon, 10);
      u8g2.print(weather.currentWeatherDescription);

      u8g2.setFont(u8g2_font_profont10_mf);
      u8g2.setCursor(posXRightOfIcon, 26);
      u8g2.print("uvi: ");
      // Under Animated Icon - large font
      u8g2.setFont(u8g2_font_fub14_tr);
      u8g2.setCursor(posXRightOfIcon + 16, 26);
      u8g2.print(String(weatherCurrentDay.uvi));
      
      // Under Animated Icon
      String sunrise = "rise: ";
      sunrise += String(weather.sunrise);
      String sunset = "set: ";
      sunset += String(weather.sunset);

      u8g2.setFont(u8g2_font_blipfest_07_tr);
      u8g2.setCursor(posX, posYUnderIcon);
      u8g2.print(sunrise);
      u8g2.setCursor(posX + 66, posYUnderIcon);
      u8g2.print(sunset);

      // bottom row
      // Date time
      char buf[80];
      strftime(buf, sizeof(buf), "%a %D", &timeinfo);
      u8g2.setFont(u8g2_font_profont12_mf);
      u8g2.setCursor(3, 60); 
      u8g2.print(buf);

      // Bottom Right - Temp
      largeTemp(100, 60, weather.currentTemperature);
    }
    break;
    case 18: //Test
    {
      animateImages(32, -5, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_CLOUDY_0, WEATHER_CLOUDY_1, WEATHER_CLOUDY_2, WEATHER_CLOUDY_3);
      lavaLamp(6, 69, 0, millis() / 50, 0);
    }
    break;
    case 19: //Test
    {
      animateImages(64, -5, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_MIST_0, WEATHER_MIST_1);
      lavaLamp(10, 100, 0, millis() / 100, 0);
    }
    break;
    case 20: //Test
    {
      animateImages(0, 20, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_SUNNY_0, WEATHER_SUNNY_1);
      lavaLamp(10, 100, 0, millis() / 100, 0);
    }
    break;
    case 21: //Test
    {
      animateImages(32, 20, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_PARTLY_CLOUDY_20, WEATHER_PARTLY_CLOUDY_21, WEATHER_PARTLY_CLOUDY_22, WEATHER_PARTLY_CLOUDY_23);
      lavaLamp(6, 69, 0, millis() / 50, 0);
    }
    break;
    case 22: //Test
    {
      animateImages(64, 20, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_LIGHT_RAIN_0, WEATHER_LIGHT_RAIN_1);
      lavaLamp(8, 128, 0, millis() / 20, 0);
    }
    break;
    case 23: //Test
    {
      animateImages(0, 40, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_CLOUDY_20, WEATHER_CLOUDY_21, WEATHER_CLOUDY_22, WEATHER_CLOUDY_23);
      lavaLamp(4, 128, 0, millis() / 10, 0);
    }
    break;
    case 24: //Test
    {
      animateImages(32, 40, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_THUNDERSTORM_0, WEATHER_THUNDERSTORM_1);
    }
    break;
    case 25: //Test
    {
      animateImages(96, 40, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_RAINY_DAY_0, WEATHER_RAINY_DAY_1);
    }
    break;
    case 26: //Test
    {
      animateImages(64, 40, WEATHER_ICON_WIDTH, WEATHER_ICON_HEIGHT, WEATHER_SNOW_0, WEATHER_SNOW_1);
    }
    break;
    case 27: //Test
    {
      animateImages(96, 20, FACE_SMIRK_WIDTH, FACE_SMIRK_HEIGHT, FACE_SMIRK_0, FACE_SMIRK_1);
      lavaLamp(5, 128, 0, millis() / 50, 0);
    }
    break;
  }
}

void largeTemp(byte posX, byte posY, String tempVal) 
{
  u8g2.setFont(u8g2_font_fub14_tr); // large font
  u8g2.setCursor(posX, posY);
  u8g2.print(String(tempVal)); // print current Temp

  u8g2.setFont(u8g2_font_profont10_mf); // change font for better symbol
  u8g2.setCursor(posX + 22, posY - 8); // move symbol up & to right
  u8g2.print("\xb0 "); //Degree symbol  
}
void animateImages(byte posX, byte posY, int imageWidth, int imageHeight, const unsigned char* image1, const unsigned char* image2) 
{
  int maxFrames = 2;

  if (globals.animationFrame % maxFrames) {
    u8g2.drawXBMP(posX, posY, imageWidth, imageHeight, image1);
  } else {    
    u8g2.drawXBMP(posX, posY, imageWidth, imageHeight, image2);
  }

  EVERY_N_MILLISECONDS(600)
  {
    globals.animationFrame++;
    if (globals.animationFrame > maxFrames) {
      globals.animationFrame = 0;
    }
  }
}

void animateImages(byte posX, byte posY, int imageWidth, int imageHeight, const unsigned char* image1, const unsigned char* image2, const unsigned char* image3,  const unsigned char* image4) 
{
  int maxFrames = 3;

  if (globals.animationFrame == 0) {
    u8g2.drawXBMP(posX, posY, imageWidth, imageHeight, image1);
  } else if (globals.animationFrame == 1) {    
    u8g2.drawXBMP(posX, posY, imageWidth, imageHeight, image2);
  } else if (globals.animationFrame == 2) {
    u8g2.drawXBMP(posX, posY, imageWidth, imageHeight, image3);
  } else if (globals.animationFrame == 3) {
    u8g2.drawXBMP(posX, posY, imageWidth, imageHeight, image4);
  }

  EVERY_N_MILLISECONDS(600)
  {
    globals.animationFrame++;
    if (globals.animationFrame > maxFrames) {
      globals.animationFrame = 0;
    }
  }
}

void showLargeTime(byte posX, byte posY) 
{
  u8g2.setFont(u8g2_font_fub30_tn);
  if (globalTime.currentHour != 100) //Default setting is 100, so we know time is set
  {
    u8g2.setCursor(posX, posY);

    if ((globalTime.currentHour > 9) || (globalTime.currentHour == 0))
    {
      u8g2.setCursor(posX - 30, posY);
    }

    if (globalTime.currentHour == 0)
    {
      u8g2.print("12");
    }
    else
    {
      u8g2.print(globalTime.currentHour);
    }

    u8g2.setCursor(posX + 20, posY - 4);
    u8g2.print(":");

    u8g2.setCursor(posX + 38, posY);
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
  
void showLargeTimeSegment(byte posX, byte posY) 
{
  u8g2.setFont(u8g2_font_7Segments_26x42_mn);
  if (globalTime.currentHour != 100) //Default setting is 100, so we know time is set
  {
    u8g2.setCursor(posX,posY);

    if ((globalTime.currentHour > 9) || (globalTime.currentHour == 0))
    {
      u8g2.setCursor(posX - 34, posY);
    }

    if (globalTime.currentHour == 0)
    {
      u8g2.print("12");
    }
    else
    {
      u8g2.print(globalTime.currentHour);
    }

    u8g2.setCursor(posX + 30,posY);
    u8g2.print(":");

    u8g2.setCursor(posX + 48, posY);
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
  //u8g2.setFont(u8g2_font_profont12_mf);
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
    case 1: // BASIC
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_0);
      break;
    case 2: // DECOR
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_1);
      break;
    case 3: // PARTY
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_2);
      break;
    case 4: // ADVANCED
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_3);
      break;
    case 5: // COMPLEX
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_4);
      break;
    case 6: // SPECIAL
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_5);
      break;
    case 7: // SOUND REACTIVE
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_6);
      break;
    case 8: // LEGACY
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_7);
      break;
    case 9: // WEATHER REACTIVE
      u8g2.drawXBMP(0, 0, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_ICON_WIDTH, CATEGORY_MENU_8);
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
  if ((knob2.heldTime > 0) || ((brightness.debounce2 > millis()) && (brightness.debounce2 > brightness.debounce)))
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
    u8g2.drawBox(tA.x - 17, tA.y + 12, 35, 2);
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


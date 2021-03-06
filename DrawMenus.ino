/*******************************************************************
 *  Menu System - globalMenu.currentMenu sets menu page. globalMenu.menu[] contains selection
 *                globalMenu.menuMax[] specifies max selection
 *  0 - Main Page
 *  1 - Games Page
 *  2 - Settings Page 
 *        3 - LED Count   4 - IP Address
 * 
 *  5 - Favorites Page
 *        6 - Max Favs    7 - Reset Favs   8 - New Fav 
 * *****************************************************************/

void drawMenu(int numberOfItems, int currentlySelected, ...)
{
  //Normal drawing color
  u8g2.setDrawColor(1);

  //Create a new list with however many items we received
  va_list menuItems;
  va_start (menuItems, currentlySelected);

  //Take the first string and send it to the drawMenuTop function
  drawMenuTop(String(va_arg (menuItems, char*)));

  //Spacers for top
  if (currentlySelected == 0)
  {
    u8g2.setCursor(4, 20);
    u8g2.print("- - - - - - -");
    u8g2.setCursor(4, 30);
    u8g2.print("- - - - - - -");
    for (int i = 1; i <= numberOfItems; i++)        
    {
      u8g2.setCursor(4, 30 + (10 * i));
      //u8g2.print(i);
      //u8g2.print(" - ");
      u8g2.print(String(va_arg (menuItems, char*))); 

      //Stop if we have gone off the screen
      if (i > 2)
      {
        i = 100;
      }
    }
  }

  if (currentlySelected == 1)
  {
    u8g2.setCursor(4, 20);
    u8g2.print("- - - - - - -");
    for (int i = 1; i <= numberOfItems; i++)        
    {
      u8g2.setCursor(4, 20 + (10 * i));
      //u8g2.print(i);
      //u8g2.print(" - ");
      u8g2.print(String(va_arg (menuItems, char*))); 

      //Stop if we have gone off the screen
      if (i > 3)
      {
        i = 100;
      }
    }
  }

  if (currentlySelected > 1)
  {
    //Cycle through offscreen items
    for (int i = 0; i <= currentlySelected - 3; i++)
    {
      String bogus = String(va_arg (menuItems, char*));
    }

    for (int i = 0; i <= numberOfItems - currentlySelected + 1; i++)        
    {
      u8g2.setCursor(4, 20 + (10 * i));
      //u8g2.print(i);
      //u8g2.print(" - ");
      u8g2.print(String(va_arg (menuItems, char*))); 

      //Stop if we have gone off the screen
      if (i >= 4)
      {
        i = 100;
      }
    }
  }

  //Spacers for bottom
  if (numberOfItems - currentlySelected == 2)
  {
    u8g2.setCursor(4, 60);
    u8g2.print("- - - - - - -");
  }

  if (numberOfItems - currentlySelected == 1)
  {
    u8g2.setCursor(4, 50);
    u8g2.print("- - - - - - -");
    u8g2.setCursor(4, 60);
    u8g2.print("- - - - - - -");
  }

  //Close our list
  va_end (menuItems);
  
  //Invert drawing color & draw the middle box
  u8g2.setDrawColor(2);
  u8g2.drawBox(0, 31, 128, 10);

  //Back to default draw color
  u8g2.setDrawColor(1);
}


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
  u8g2_horizontal_line(9);
}

void drawMenuCommander()
{
  u8g2.setFont(u8g2_font_ncenB08_tr);

    //Draw Screen
  switch (globalMenu.currentMenu)
  {
  case 0: // Draw Image
  {
    //drawMenuWords("Welican Gemina",
    //              "Games", "Settings", "Customize", "Exit");
    
    

    drawMenuSelectionFrames();

    if (globals.mode == 0)
    {
      drawMenuWords("Welican Gemina",
                    "Games", " - - - - - -", "Display", "Settings");
    }
    else
    {
      drawMenuWords("Welican Gemina",
                    "Games", "Favorite", "Display", "Settings");
    }
    

    drawIPAddress();
  }
  break;
  case 1: // Draw Games
  {
    drawMenu(6, globalMenu.menu[globalMenu.currentMenu], "Games", 
      "Fallios", "Block Breaker", "Magic 8 Ball", "Daddy Worm", "Pong", "2P - Daddy Worm");
  }
  break;
  case 2: // Draw Settings
  {
    //drawMenuWords("Settings",
    //              "LEDs", "Time", "ZIP Code", "WiFi");

    drawMenu(8, globalMenu.menu[globalMenu.currentMenu], "Settings",
      "LED Configuration", "Timezone", "Time (No Internet)", "ZIP Code", "WiFi","Max Favorites","Randomizer Time","System Information");
    //drawMenuSelectionFrames();
  }
  break;
  case 3: // LED
  {
    //drawMenuTop("Settings > LED Settings");
    //drawMenuWords("Settings > LED",
    //              "# LEDs", "Order", "Fade", "Speed");
    drawMenu(4, globalMenu.menu[globalMenu.currentMenu], "Settings > LED",
      "Number of LEDs", "Color Order", "Crossfade Amount", "Power Limit");

    //drawMenuSelectionFrames();
  }
  break;
  case 4: // Zip Code Menu
  {
    drawMenuTop("Settings > ZIP Code");

    u8g2.setCursor(16, 50);
    u8g2.print("Current ZIP Code ");

    updateZipCodeString();
    u8g2.print(weatherSettings.zipCode);
  }
  break;
  case 5:
  {

  }
  break;
  case 6: //Max Favorites
  {
    drawNumberInput("Settings > Max Favorites",
                    globalMenu.menu[globalMenu.currentMenu]);

    if (globalMenu.menu[globalMenu.currentMenu] < 1) //gotta have at least 1 favorite
    {
      globalMenu.menu[globalMenu.currentMenu] = 1;
    }
  }
  break;
  case 7: // Favorites Reset Menu
  {
    drawYesNoMenuFrame("Factory Reset?");
  }
  break;
  case 8: // WIFI Menu
  {
    switch (globals.softAPEnable)
    {
    case 0:
    {
      drawMenuWords("Settings > WiFi",
                    "Scan", "Host", "Connect", "Disconn.");
    }
    break;

    case 1:
    {
      drawMenuWords("Settings > WiFi",
                    "Scan", "Hosting!", "Connect", "Disconn.");
    }
    break;
    }
    drawMenuWords("Settings > WiFi",
                  "Scan", "Host", "Connect", "Disconn.");

    u8g2.setCursor(10, 64);
    drawIPAddress();
    if (WiFi.status() == WL_CONNECTED)
    {     
      int temp = WiFi.SSID().length();
      temp = 64 - (temp * 2);

      if (temp < 0)
      {
        temp = 0;
      }

      u8g2.setCursor(temp, 51);
      u8g2.print(WiFi.SSID());

      //u8g2.print("   ");
      //u8g2.print(RSSItoPercent(WiFi.RSSI()));
      //u8g2.print(WiFi.RSSI());
      //u8g2.print("%");

    }
    drawMenuSelectionFrames();
  }
  break;
  case 9:
  {

  }
  break;
  case 10: // Add New Favorites Menu
  {
    newFavoritesMenu();
  }
  break;
  case 11: // Set Zip Code Menu
  {
    setZipCodeMenu();
  }
  break;
  case 12: // WIFI Scan Results
  {
    drawMenuTop("WiFi Scan Results");

    u8g2.setCursor(15, 60);
    if (globals.networkScan == WIFI_SCAN_FAILED)
    {
      u8g2.print("Scan Failed");
    }

    if (globals.networkScan == 0)
    {
      Serial.println("No Networks Found");
    }

    if (globals.networkScan > 0)
    {
      for (int i = 0; i < globals.networkScan; ++i)
      {
        //u8g2.setCursor(10, 19 + (9 * i));
        //u8g2.print(RSSItoPercent(WiFi.RSSI(i)));
        switch (RSSItoStrength(WiFi.RSSI(i)))
        {
        case 0:
          u8g2.drawXBMP(10, 11 + (9 * i), WIFI_0_WIDTH, WIFI_0_HEIGHT, WIFI_0);
          break;
        case 1:
          // u8g2.drawXBMP(0, 0, WAVE_WIDTH, WAVE_HEIGHT, WAVE);
          u8g2.drawXBMP(10, 11 + (9 * i), WIFI_1_WIDTH, WIFI_1_HEIGHT, WIFI_1);
          break;
        case 2:
          u8g2.drawXBMP(10, 11 + (9 * i), WIFI_2_WIDTH, WIFI_2_HEIGHT, WIFI_2);
          break;
        case 3:
          u8g2.drawXBMP(10, 11 + (9 * i), WIFI_3_WIDTH, WIFI_3_HEIGHT, WIFI_3);
          break;
        case 4:
          u8g2.drawXBMP(10, 11 + (9 * i), WIFI_4_WIDTH, WIFI_4_HEIGHT, WIFI_4);
          break;
        }

        //u8g2.setCursor(25, 19 + (9 * i));
        if (WiFi.encryptionType(i) != WIFI_AUTH_OPEN)
        {
          u8g2.drawXBMP(23, 11 + (9 * i), LOCK_WIDTH, LOCK_HEIGHT, LOCK);
        }
        //u8g2.print((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
        u8g2.setCursor(35, 19 + (9 * i));
        u8g2.print(WiFi.SSID(i));
      }

      u8g2.setCursor(0, 19 + (9 * globalMenu.menu[globalMenu.currentMenu]));
      u8g2.print(">");
    }
  }
  break;
  case 13: // Enter WiFi PW
  {
    drawMenuTop("Enter WiFi Password");

    if (globalMenu.menu[globalMenu.currentMenu] < 33)
    {
      globalMenu.menu[globalMenu.currentMenu] = 33;
    }

    u8g2.setCursor(0, 24);
    u8g2.print(globals.ssid);

    u8g2.setCursor(0, 40);
    u8g2.print(globals.password);

    if (globalMenu.menu[globalMenu.currentMenu] > 127)
    {
      u8g2.setCursor(0, 60);
      u8g2.print("Connect!");
    }
    else
    {
      WiFi.SSID().length();
      u8g2.setCursor(30, 60);
      u8g2.print((char)globalMenu.menu[globalMenu.currentMenu]);

      //u8g2.setCursor(70, 60);
      //u8g2.print(globalMenu.menu[globalMenu.currentMenu]);
    }

    //32 = " "
    //33 = !
    //126 = ~
  }
  break;
  case 14: // Test connection to new WiFi
  {
    drawMenuTop("Test Connection");

    if (WiFi.status() == WL_CONNECTED)
    {
      u8g2.setCursor(0, 30);

      int temp = WiFi.SSID().length();

      temp = 58 - (temp * 2);

      if (temp < 0)
      {
        temp = 0;
      }

      u8g2.setCursor(temp, 51);
      u8g2.print(WiFi.SSID());

      globals.ipAddress = WiFi.localIP().toString();
      temp = globals.ipAddress.length();

      temp = 58 - (temp * 2);

      if (temp < 0)
      {
        temp = 0;
      }

      u8g2.setCursor(temp, 64);
      u8g2.print(globals.ipAddress);
    }
    else
    {
      u8g2.setCursor(5, 60);
      u8g2.print("Trying to Connect...");
      if ((millis() - globals.networkReconnect) > 3000)
      {
        globals.networkReconnect = millis();
        WiFi.disconnect();
        delay(10);
        //WiFi.begin();
        WiFi.begin((const char *)globals.ssid.c_str(), (const char *)globals.password.c_str());
        delay(42);
      }
    }
    u8g2.setCursor(30, 30);
    switch (WiFi.status())
    {
    case 0:
      u8g2.print("IDLE_STATUS");
      break;
    case 1:
      u8g2.print("NO_SSID_AVAIL");
      break;
    case 2:
      u8g2.print("SCAN_COMPLETED");
      break;
    case 3:
      u8g2.print("CONNECTED");
      break;
    case 4:
      u8g2.print("IDLE_STATUS");
      break;
    case 5:
      u8g2.print("CONNECTION_LOST");
      break;
    case 6:
      u8g2.print("DISCONNECTED");
      break;
    }
  }
  break;
  case 15:
  {
    if (globalMenu.menu[globalMenu.currentMenu] < 1) //gotta have at least 1 LED
    {
      globalMenu.menu[globalMenu.currentMenu] = 1;
    }

    drawNumberInput("Set # of LEDs",
                    globalMenu.menu[globalMenu.currentMenu] * 5);
  }
  break;
  case 16: //RGB Order
  {
    drawMenuWords("Settings > LED > Order",
                  "RGB", "GRB", "BGR");
    drawMenuSelectionFrames();
  }
  break;
  case 17: //Fade Time
  {
    if (globalMenu.menu[globalMenu.currentMenu] < 1) //gotta have at least 1
    {
      globalMenu.menu[globalMenu.currentMenu] = 1;
    }

    drawNumberInput("Crossfade Duration",
                    globalMenu.menu[globalMenu.currentMenu]);

    u8g2.setFont(u8g2_font_profont12_mf);
    u8g2.setCursor(0, 64);
    u8g2.print("1 < SHORT--LONG > 50");
  }
  break;
  case 18: //Speed?
  {
  }
  break;
  case 19:  //Time
  {
    drawMenuWords("Settings > Time",
                  "Timezone", "Manual", "NTP Sync", "Date");
    drawMenuSelectionFrames();
  }
  break;
  case 20: //Time Zone
  {
    drawMenu(7, globalMenu.menu[globalMenu.currentMenu], "Settings > Timezone", 
      "Eastern", "Central", "Mountain", "Mountain (No DST)", "Pacific", "Alaska", "Hawaii"); 
  }
  break;

  case 21: //Manual Time Entry Hour
  {
      drawMenuTop("Settings > Time");
      u8g2.setFont(u8g2_font_fub30_tn);
      if (globalMenu.menu[globalMenu.currentMenu] == 0)
      {
        globalMenu.menu[globalMenu.currentMenu] = 1;
      }
      u8g2.setCursor(30, 58);
      if (globalMenu.menu[21] > 9)
      {
        u8g2.setCursor(0, 58);
      }
      u8g2.print(globalMenu.menu[21]);
      u8g2.setCursor(50, 54);
      u8g2.print(":");
      u8g2.setCursor(68, 58);
      if (globalMenu.menu[22] < 10)
      {
        u8g2.print("0");
      }
      u8g2.print(globalMenu.menu[22]);
      u8g2.drawBox(5, 62, 45, 3);
  }
  break;

  case 22: //Manual Date Entry Minute
  {
      drawMenuTop("Settings > Time");
      u8g2.setFont(u8g2_font_fub30_tn);
      u8g2.setCursor(30, 58);
      if (globalMenu.menu[21] > 9)
      {
        u8g2.setCursor(0, 58);
      }
      u8g2.print(globalMenu.menu[21]);
      u8g2.setCursor(50, 54);
      u8g2.print(":");
      u8g2.setCursor(68, 58);
      if (globalMenu.menu[22] < 10)
      {
        u8g2.print("0");
      }
      u8g2.print(globalMenu.menu[22]);
      u8g2.drawBox(68, 62, 50, 3);
  }
  break;

  case 23: //NTP Enable/Disable
  {

  }
  break;

  case 24: //Customize > Display
  {
    drawMenu(8, globalMenu.menu[globalMenu.currentMenu], "Display",
            "Timeout", "Brightness", "Display 1",  "Display 1 Duration", "Display 2", "Display 2 Duration", "Display 3", "Display 3 Duration");
    //drawMenuSelectionFrames();
  }
  break;

  case 25: //Customize > Timeout
  {
    drawMenuTop("Display > Timeout");

    u8g2.setCursor(20, 32);

    if (globalMenu.menu[globalMenu.currentMenu] < 12)
    {
      if (globalMenu.menu[globalMenu.currentMenu] == 0)
      {
        u8g2.print("No Timeout");
      }
      else
      {
        u8g2.print(globalMenu.menu[globalMenu.currentMenu] * 5);
        u8g2.print(" Seconds");
      }
    }
    else
    {
      u8g2.print(globalMenu.menu[globalMenu.currentMenu] - 11);
      u8g2.print(" Minutes");
    }    
  }
  break;

  case 26: //Display 1 Selection
  {
    drawClock(globalMenu.menu[26]);
  }
  break;

  case 27: //Display 2 Selection
  {
    drawClock(globalMenu.menu[27]);
  }
  break;

  case 28: //Display 3 Selection
  {
    drawClock(globalMenu.menu[28]);
  }
  break;

  case 29: //Customize > Random
  {
    drawMenuTop("Settings > Randomizer");

    u8g2.setCursor(20, 32);

    //u8g2.print(timeOutString(globalMenu.menu[globalMenu.currentMenu]));

    if (globalMenu.menu[globalMenu.currentMenu] < 12)
    {
      if (globalMenu.menu[globalMenu.currentMenu] == 0)
      {
        u8g2.print("Never");
      }
      else
      {
        u8g2.print(globalMenu.menu[globalMenu.currentMenu] * 5);
        u8g2.print(" - ");
        u8g2.print(globalMenu.menu[globalMenu.currentMenu] * 10);
        u8g2.print(" Seconds");
      }
    }
    else
    {
      u8g2.print(globalMenu.menu[globalMenu.currentMenu] - 11);
      u8g2.print(" - ");
      u8g2.print((globalMenu.menu[globalMenu.currentMenu] - 11) * 2);
      u8g2.print(" Minutes");
    }   
  }
  break;

  case 30: //Display 1 Time
  {
    drawNumberInput("Display 1 Duration", globalMenu.menu[globalMenu.currentMenu]);
    u8g2.setFont(u8g2_font_profont12_mf);
    u8g2.setCursor(45, 64);
    u8g2.print("Seconds");
  }
  break;

  case 31: //Display 2 Time
  {
    drawNumberInput("Display 2 Duration", globalMenu.menu[globalMenu.currentMenu]);
    u8g2.setFont(u8g2_font_profont12_mf);
    u8g2.setCursor(45, 64);
    u8g2.print("Seconds");
  }
  break;

  case 32: //Display 3 Time
  {
    drawNumberInput("Display 3 Duration", globalMenu.menu[globalMenu.currentMenu]);
    u8g2.setFont(u8g2_font_profont12_mf);
    u8g2.setCursor(45, 64);
    u8g2.print("Seconds");
  }
  break;

  case 33: //Brightness
  {
    u8g2.drawBox(108, 9, 10, 64);
    u8g2.drawBox(120, 9, 2, 64);
    u8g2.drawBox(124, 9, 1, 64);
    u8g2.drawBox(126, 9, 1, 64);
    
    u8g2.drawBox(0, 52, 128, 5);
    u8g2.drawBox(0, 59, 128, 2);
    u8g2.drawBox(0, 62, 128, 1);
    drawNumberInput("Display > Brightness", globalMenu.menu[globalMenu.currentMenu]);
    u8g2.setContrast(globalMenu.menu[33] * 25.5);
  }
  break;

  case 34: //System Information
  {
    drawMenuTop("Welican Gemina");
    u8g2.setCursor(0, 25);
    u8g2.print(VERSION_INFO);
    u8g2.setCursor(10, 42);
    u8g2.print("Brian Schimke");
    u8g2.setCursor(10, 53);
    u8g2.print("Matt Taylor");
    u8g2.setCursor(10, 64);
    u8g2.print("Sam Millard");
  }
  break;

  case 35: //Power Limit
  {
    if (globalMenu.menu[globalMenu.currentMenu] == 0)
    {
      drawMenuTop("Settings > LED > Power");
      u8g2.setFont(u8g2_font_profont12_mf);
      u8g2.setCursor(40, 32);
      u8g2.print("Not Limited");
      FastLED.setMaxPowerInMilliWatts(4200000000);
      u8g2.setCursor(30, 64);
      u8g2.print(String((float(calculate_unscaled_power_mW(patternSettings.leds, NUM_LEDS) / 1000.00) * (brightness.current / 200) + NUM_LEDS * 0.025)));
      u8g2.print(" Watts");
    }
    else
    {
      FastLED.setMaxPowerInMilliWatts(globalMenu.menu[35] * 1000);
      drawNumberInput("Settings > LED > Power", globalMenu.menu[globalMenu.currentMenu]);
      u8g2.setFont(u8g2_font_profont12_mf);
      u8g2.setCursor(90, 32);
      u8g2.print("Watt");
      u8g2.setCursor(90, 52);
      u8g2.print("Limit");
    }
  }
  break;


  } //End of Display

  // Back Button Action
  if (knob2.click == 1)
  {
    switch (globalMenu.currentMenu)
    {
    case 0: //main menu
      globals.runMode = -1;
      break;
    case 1: //Games Menu
      globalMenu.currentMenu = 0;
      break;
    case 2: //Settings Menu
      globalMenu.currentMenu = 0;
      break;
    case 3:
      globalMenu.currentMenu = 2;
      break;
    case 4: //Zip Code Menu
      globalMenu.currentMenu = 2;
      break;
    case 5: //Favorites Main Menu
      globalMenu.currentMenu = 9;
      break;
    case 6: //Favorites Set Max
      globalMenu.currentMenu = 2;
      break;
    case 7:
      globalMenu.currentMenu = 34;
      break;
    case 8: //WiFi Menu
      globalMenu.currentMenu = 2;
      break;
    case 9: //Customize Menu
      globalMenu.currentMenu = 0;
      break;
    case 10: //Add New Favorite
      globalMenu.currentMenu = 0;
      break;
    case 11:
    {
      //ZIP Code, advance one
      int temp = globalMenu.currentMenuMultiplier;
      switch (temp)
      {
      case 10000:
        globalMenu.currentMenuMultiplier = 1;
        globalMenu.currentMenu = 4; //Go back to main
        globalMenu.currentMenuMultiplier = 1;
        break;
      case 1000:
        globalMenu.currentMenuMultiplier = 10000;
        break;
      case 100:
        globalMenu.currentMenuMultiplier = 1000;
        break;
      case 10:
        globalMenu.currentMenuMultiplier = 100;
        break;
      case 1:
        globalMenu.currentMenuMultiplier = 10;
        break;
      }
    }
    break;
    case 12:
    {
      globalMenu.currentMenu = 8;
      WiFi.begin();
    }
    break;
    case 13:
    {
      int temp = globals.password.length();
      if (temp > 1)
      {
        //globals.password -= " ";
        globals.password.remove(temp - 1, 1);
      }
      else
      {
        globalMenu.currentMenu = 8;
      }
    }
    break;
    case 14:
    {
      globalMenu.menu[13] = 0;
      globalMenu.currentMenu = 12;
    }
    break;
    case 15:
    {
      globalMenu.currentMenu = 3;
    }
    break;
    case 16:
    {
      globalMenu.currentMenu = 3;
    }
    break;
    case 17:
    {
      globalMenu.currentMenu = 3;
    }
    break;
    case 18:
    {
      globalMenu.currentMenu = 3;
    }
    break;
    case 19:
    {
        globalMenu.currentMenu = 2;
    }
    break;
    case 20: //
    {
      EEPROM.get(234, globalMenu.menu[20]);
      globalMenu.currentMenu = 2;
    }
    break;
    case 21: //Manual Time Entry 1
    {
      globalMenu.currentMenu = 2;
    }
    break;
    case 22: //Manual Time Entry 2
    {
      globalMenu.currentMenu = 21;
    }
    break;
    case 23: //
    {

    }
    break;
    case 24: //
    {
      globalMenu.currentMenu = 0;
    }
    break;
    case 25: //
    {
      EEPROM.get(242, globalMenu.menu[globalMenu.currentMenu]);
      globalMenu.currentMenu = 24;
    }
    break;
    case 26: //
    {
      EEPROM.get(254, globalMenu.menu[globalMenu.currentMenu]);
      globalMenu.currentMenu = 24;
    }
    break;
    case 27: //
    {
      EEPROM.get(262, globalMenu.menu[globalMenu.currentMenu]);
      globalMenu.currentMenu = 24;
    }
    break;

    case 28: //
    {
      EEPROM.get(270, globalMenu.menu[globalMenu.currentMenu]);
      globalMenu.currentMenu = 24;
    }
    break;

    case 29: //Random Time
    {
      EEPROM.get(238, globalMenu.menu[globalMenu.currentMenu]);
      globalMenu.currentMenu = 2;
    }
    break;

    case 30:
    {
      EEPROM.get(258, globalMenu.menu[globalMenu.currentMenu]);
      globalMenu.currentMenu = 24;
    }
    break;
    case 31:
    {
      EEPROM.get(266, globalMenu.menu[globalMenu.currentMenu]);
      globalMenu.currentMenu = 24;
    }
    break;
    case 32:
    {
      EEPROM.get(274, globalMenu.menu[globalMenu.currentMenu]);
      globalMenu.currentMenu = 24;
    }
    break;

    case 33:
    {
      EEPROM.get(230, globalMenu.menu[globalMenu.currentMenu]); //Display Brightness
      if (globalMenu.menu[globalMenu.currentMenu] > globalMenu.menuMax[globalMenu.currentMenu])
      {
        globalMenu.menu[globalMenu.currentMenu] = 10;
      }
      u8g2.setContrast(globalMenu.menu[33] * 25.5);
      globalMenu.currentMenu = 24;
    }
    break;

    case 34:
    {
      globalMenu.currentMenu = 2;
    }
    break;

    case 35:
    {
      EEPROM.get(212, globalMenu.menu[globalMenu.currentMenu]);

      if (globalMenu.menu[globalMenu.currentMenu] > globalMenu.menuMax[globalMenu.currentMenu])
      {
        globalMenu.menu[globalMenu.currentMenu] = 0;
      }

      if (globalMenu.menu[35] == 0)
      {
        FastLED.setMaxPowerInMilliWatts(4200000000);
      }
      else
      {
        FastLED.setMaxPowerInMilliWatts(globalMenu.menu[35] * 1000);
      }

      globalMenu.currentMenu = 3;
    }
    break;

    }
  }

  // Forward/Confirm Button Action
  if (knob1.click == 1)
  {
    switch (globalMenu.currentMenu)
    {
    case 0: // Main Menu
    {
      switch (globalMenu.menu[globalMenu.currentMenu])
      {
      case 0:
        globalMenu.currentMenu = 1; // games
        break;
      case 1:
        if (globals.mode != 0) //Only if not already a favorite
        {
          globalMenu.currentMenu = 10; // Add Favorite
        }
        break;
      case 2:
        globalMenu.currentMenu = 24;  //Display
        break;
      case 3:
        globalMenu.currentMenu = 2; // Settings
        break;
    }
    break;
    case 1: // games menu click
      switch (globalMenu.menu[globalMenu.currentMenu])
      {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        setGameMode();
        break;
      //case 6:
        //globalMenu.currentMenu = 0; // back to main menu
        break;
      }
    }
    break;
    case 2: // Settings click
    {
      switch (globalMenu.menu[globalMenu.currentMenu])
      {
      case 0: //LED Settings
        globalMenu.currentMenu = 3;
        break;
      case 1: //Timezone menu
        globalMenu.currentMenu = 20;
        break;
      case 2: //Manual time entry
        globalMenu.currentMenu = 21;
        break;
      case 3: // ZIP Code
        globalMenu.currentMenu = 4;
        break;
      case 4: // Wifi
        globalMenu.currentMenu = 8;
        break;
      case 5: // Max Favoirtes
        globalMenu.currentMenu = 6;
        globalMenu.menu[6] = patternSettings.numberOfFavorites;
        break;
      case 6: //Randomizer Time
        globalMenu.currentMenu = 29;
        break;
      case 7: //System Information
        globalMenu.currentMenu = 34;
      }
    }
    break;
    case 3: //LED click
    {
      switch (globalMenu.menu[globalMenu.currentMenu])
      {
      case 0: //# LED
        //ESP gets a reboot if changed, so save current pattern
        globalTime.save == 2;
        globalMenu.currentMenu = 15;
        break;
      case 1: //Order
        globalMenu.currentMenu = 16;
        break;
      case 2: //Fade
        globalMenu.currentMenu = 17;
        break;
      case 3: //Power Limit
        globalMenu.currentMenu = 35;
        break;
      }
    }
    break;
    case 4: // ZIP Code settings click
    {
      globalMenu.currentMenuMultiplier = 10000;
      globalMenu.currentMenu = 11;
      getZipCode();
    }
    break;
    case 5: // Favorites Setting Menu Click
    {
      switch (globalMenu.menu[globalMenu.currentMenu])
      {
      case 0: // Add New, can't favorite a favorite!
        if (globals.mode != 0)
        {
          globalMenu.currentMenu = 10;
        }
        break;
      case 1: // Set Max
        globalMenu.currentMenu = 6;
        globalMenu.menu[6] = patternSettings.numberOfFavorites;
        break;
      case 2: // Reset
        globalMenu.currentMenu = 7;
        break;
      case 3: // Back to settings
        globalMenu.currentMenu = 9;
        break;
      }
    }
    break;
    case 6: // Set Max Favorites Click
    {
      ledcWrite(STATUS_LED, 4095);
      patternSettings.numberOfFavorites = globalMenu.menu[globalMenu.currentMenu];
      globalMenu.patternMax[0] = patternSettings.numberOfFavorites;
      globalMenu.menuMax[10] = patternSettings.numberOfFavorites;
      EEPROM.write(99, patternSettings.numberOfFavorites);
      EEPROM.commit();
      globalMenu.currentMenu = 2;
    }
    break;
    case 7: // Reset Favorites Click
    {
      switch (globalMenu.menu[globalMenu.currentMenu])
      {
      case 0: // No
        globalMenu.currentMenu = 5;
        break;
      case 1: // Yes
        resetFavorites();
        // picture of trash can or something and small delay later
        globals.runMode = -1;
        break;
      }
    }
    break;
    case 8: // Network Scan
    {
      switch (globalMenu.menu[globalMenu.currentMenu])
      {
      case 0: // Scan
      {
        globalMenu.currentMenu = 12;
        WiFiScan();

        // Limit to first 6 results
        if (globals.networkScan > 6)
        {
          globals.networkScan = 6;
        }

        globalMenu.menuMax[12] = globals.networkScan - 1;
      }
      break;
      case 1: // Host
      {
        //https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html

        switch (globals.softAPEnable)
        {
        case 0:
        {
          //WiFi.mode(WIFI_AP); // Disable STA Mode, not actually needed though? Not calling allows both to work simultaneously
          globals.softAPEnable = WiFi.softAP("Welican Gemina");
        }
        break;

        case 1:
        {
          WiFi.mode(WIFI_STA); // Disable AP Mode
          globals.softAPEnable = WiFi.softAPdisconnect();
        }
        break;
        }
      }
      break;
      case 2: // Connect
      {
        WiFi.enableSTA(true);
        WiFi.begin();
        if (WiFi.status() == WL_CONNECTED)
        {
          setTimezone(globalMenu.menu[20]);
        }
      }
      break;
      case 3: // Disconnect
        WiFi.disconnect();
        break;
      }
    }
    break;
    case 9: //Customize
    {
      switch (globalMenu.menu[globalMenu.currentMenu])
      {
      case 0: //Favorites
      {
        globalMenu.currentMenu = 5;
      }
      break;
      case 1: //Weather
      {
        globalMenu.currentMenu = 2;
      }
      break;
      case 2: //Display
      {
        globalMenu.currentMenu = 24;
      }
      break;
      case 3: //Random Time
      {
        globalMenu.currentMenu = 29;
      }
      break;
      }
    }
    break;
    case 10: // New Favorites Click
    {
      ledcWrite(STATUS_LED, 4095);
      writeFavorites();
      globals.runMode = -1;
    }
    break;
    case 11: // Zip Code
    {
      int temp = globalMenu.currentMenuMultiplier;
      switch (temp)
      {
      case 10000:
        globalMenu.currentMenuMultiplier = 1000;
        break;
      case 1000:
        globalMenu.currentMenuMultiplier = 100;
        break;
      case 100:
        globalMenu.currentMenuMultiplier = 10;
        break;
      case 10:
        globalMenu.currentMenuMultiplier = 1;
        break;
      case 1:
        ledcWrite(STATUS_LED, 4095);
        weatherSettings.zipCode = globalMenu.menu[11]; //Update ZIP Code
        globalMenu.currentMenuMultiplier = 1;
        globalMenu.currentMenu = 2; //Go back to main
        putZipCode();
        updateZipCodeString();
        break;
      }
      if (globalMenu.currentMenuMultiplier > 10000)
      {
        globalMenu.currentMenuMultiplier = 1;
        globalMenu.currentMenu = 2;
      }
    }
    break;
    case 12: // WIFI SSID / Password
    {
      globals.ssid = WiFi.SSID(globalMenu.menu[globalMenu.currentMenu]);
      globalMenu.currentMenu = 13;
      //globalMenu.menu[13] = 40;
      if (WiFi.encryptionType(globalMenu.menu[globalMenu.currentMenu]) == WIFI_AUTH_OPEN)
      {
        globals.password = "";
        globalMenu.currentMenu = 14;
      }
    }
    break;
    case 13: // Password
    {
      if (globalMenu.menu[globalMenu.currentMenu] > 126)
      {
        globalMenu.currentMenu = 14;
      }
      else
      {
        globals.password += (char)globalMenu.menu[globalMenu.currentMenu];
      }
    }
    break;
    case 14: //
    {
      globalMenu.currentMenu = 8;
      globalMenu.menu[13] = 0;
    }
    break;
    case 15: //
    {
      saveNumberOfLEDs();
    }
    break;
    case 16:
    {
      if (globalMenu.menu[globalMenu.currentMenu] != 3)
      {
        globalLED.colorOrder = globalMenu.menu[globalMenu.currentMenu];
        saveNumberOfLEDs();
      }
      else
      {
        globalMenu.currentMenu = 3;
      }
    }
    break;
    case 17:
    {
      setSmoothOperator(globalMenu.menu[globalMenu.currentMenu]);
      globalMenu.currentMenu = 3;
    }
    break;
    case 18:
    {
      globalMenu.currentMenu = 3;
    }
    break;
    case 20:
    {
      ledcWrite(STATUS_LED, 4095);
      EEPROM.put(234, globalMenu.menu[globalMenu.currentMenu]);
      EEPROM.commit();
      setTimezone(globalMenu.menu[20]);
      updateTimeProcess();
      globalMenu.currentMenu = 2;
    }
    break;

    case 21:
    {
      globalMenu.currentMenu = 22;
    }
    break;

    case 22:
    {
      ledcWrite(STATUS_LED, 4095);
      // set current day/time
      struct timeval tv;
      //1555718400 == 04/20/2019 @ 12:00am (UTC)
      tv.tv_sec =  1555718400 + (globalMenu.menu[21] * 3600) + (globalMenu.menu[22] * 60);  // enter UTC UNIX time (get it from https://www.unixtimestamp.com )
      settimeofday(&tv, NULL);
      setenv("TZ", "WET+0", 1); // https://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
      tzset();
      updateTimeProcess();
      globalMenu.currentMenu = 2;
    }
    break;

    case 24:
    {
      switch (globalMenu.menu[globalMenu.currentMenu])
      {
      case 0: //Timeout
      {
        globalMenu.currentMenu = 25;
      }
      break;
      case 1: //Brightness
      {
        globalMenu.currentMenu = 33;
      }
      break;
      case 2: //Display 1
      {
        globalMenu.currentMenu = 26;
      }
      break;
      case 3: //Display 1 Duration
      {
        globalMenu.currentMenu = 30;
      }
      break;
      case 4: //Display 2
      {
        globalMenu.currentMenu = 27;
      }
      break;
      case 5: //Display 2 Duration
      {
        globalMenu.currentMenu = 31;
      }
      break;
      case 6: //Display 3
      {
        globalMenu.currentMenu = 28;
      }
      break;
      case 7: //Display 3 Duration
      {
        globalMenu.currentMenu = 32;
      }
      break;
      }
    }
    break;

    case 25:
    {
      ledcWrite(STATUS_LED, 4095);
      globalTime.timeOut = timeOutConverter(globalMenu.menu[globalMenu.currentMenu]);

      EEPROM.put(242, globalMenu.menu[globalMenu.currentMenu]);
      EEPROM.commit();
      globalMenu.currentMenu = 24;    
    }
    break;

    case 26:
    {
      ledcWrite(STATUS_LED, 4095);
      EEPROM.put(254, globalMenu.menu[globalMenu.currentMenu]);
      EEPROM.commit();
      globalMenu.currentMenu = 24;  
    }
    break;

    case 27:
    {
      ledcWrite(STATUS_LED, 4095);
      EEPROM.put(262, globalMenu.menu[globalMenu.currentMenu]);
      EEPROM.commit();
      globalMenu.currentMenu = 24;  
    }
    break;

    case 28:
    {
      ledcWrite(STATUS_LED, 4095);
      EEPROM.put(270, globalMenu.menu[globalMenu.currentMenu]);
      EEPROM.commit();
      globalMenu.currentMenu = 24;  
    }
    break;

    case 29: //Random Time
    {
      ledcWrite(STATUS_LED, 4095);
      EEPROM.put(238, globalMenu.menu[29]);
      EEPROM.commit();
      globals.randomMin = timeOutConverter(globalMenu.menu[29]);
      globals.randomMax = globals.randomMin * 2;
      globalMenu.currentMenu = 2;
    }
    break;

    case 30:
    {
      ledcWrite(STATUS_LED, 4095);
      EEPROM.put(258, globalMenu.menu[globalMenu.currentMenu]);
      EEPROM.commit();
      globalMenu.currentMenu = 24;
    }
    break;

    case 31:
    {
      ledcWrite(STATUS_LED, 4095);
      EEPROM.put(266, globalMenu.menu[globalMenu.currentMenu]);
      EEPROM.commit();
      globalMenu.currentMenu = 24;
    }
    break;
    case 32:
    {
      ledcWrite(STATUS_LED, 4095);
      EEPROM.put(274, globalMenu.menu[globalMenu.currentMenu]);
      EEPROM.commit();
      globalMenu.currentMenu = 24;
    }
    break;
    case 33:
    {
      ledcWrite(STATUS_LED, 4095);
      EEPROM.put(230, globalMenu.menu[globalMenu.currentMenu]);
      EEPROM.commit();
      globalMenu.currentMenu = 24;
    }
    break;
    case 34:
    {
      globalMenu.currentMenu = 7;
    }
    break;
    case 35:
    {
      ledcWrite(STATUS_LED, 4095);
      EEPROM.put(212, globalMenu.menu[globalMenu.currentMenu]);
      EEPROM.commit();
      globalMenu.currentMenu = 3;
    }
    break;
    
    }
  }
}

int timeOutConverter(int timeOut)
{
  if (timeOut < 12)
  {
    if (timeOut == 0)
    {
      //No Timeout
      timeOut = 0;
    }
    else
    {
      timeOut = (timeOut * 5 * 1000);
    }
  }
  else
  {
    timeOut = ((timeOut - 11) * 60000);
  }

  return timeOut;
}

void drawNumberInput(String menuName, int numberValue)
{
  //u8g2.setFont(u8g2_font_profont12_mf);
  drawMenuTop(menuName);

  if (numberValue > 99)
  {
    u8g2.setCursor(25, 50);
  }
  else if (numberValue > 9)
  {
    u8g2.setCursor(40, 50);
  }
  else
  {
    u8g2.setCursor(55, 50);
  }

  if (globalMenu.menu[globalMenu.currentMenu] < 1)
  {
    //globalMenu.menu[globalMenu.currentMenu] = 1;
  }

  u8g2.setFont(u8g2_font_fub30_tn);

  u8g2.print(numberValue);
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
  u8g2_horizontal_line(9);
}

String timeOutString(int timeValue)
{
  String tempString;

  if (timeValue < 12)
    {
      if (timeValue == 0)
      {
        tempString = "No Timeout";
      }
      else
      {
        tempString = String(timeValue * 5) + " Seconds";
      }
    }
    else
    {
      tempString = String(timeValue - 11) + " Minutes";
    }    

    return tempString;
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

void inputCompute(void *parameter)
{
  //Create an infinite for loop as this is a task and we want it to keep repeating
  for (;;)
  {
    // Sample the audio pin
    for (int i = 0; i < SAMPLES; i++)
    {
      globals.newTime = micros();
      globals.vReal[i] = analogRead(AUDIO_IN_PIN); // A conversion takes about 9.7uS on an ESP32
      globals.vImag[i] = 0;
      while ((micros() - globals.newTime) < globals.samplingPeriodUs)
      {
        /* chill */
      }
    }

    //Serial.print("A ");
    //Serial.println(millis());
    //updateEncoders();

    // Compute FFT
    FFT.DCRemoval();
    FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(FFT_FORWARD);
    FFT.ComplexToMagnitude();

    // Reset temp variables
    for (int i = 0; i < NUM_BANDS; i++)
    {
      eqBands.tempBandValues[i] = 0;
    }

    // Analyse FFT results
    for (int i = 2; i < (SAMPLES / 2); i++)
    { // Don't use sample 0 and only first SAMPLES/2 are usable. Each array element represents a frequency bin and its value the amplitude.
      if (globals.vReal[i] > NOISE)
      { // Add a crude noise filter

        //8 bands, 12kHz top band
        if (i <= 3)
          eqBands.tempBandValues[0] += (int)globals.vReal[i];
        if (i > 3 && i <= 6)
          eqBands.tempBandValues[1] += (int)globals.vReal[i];
        if (i > 6 && i <= 13)
          eqBands.tempBandValues[2] += (int)globals.vReal[i];
        if (i > 13 && i <= 27)
          eqBands.tempBandValues[3] += (int)globals.vReal[i];
        if (i > 27 && i <= 55)
          eqBands.tempBandValues[4] += (int)globals.vReal[i];
        if (i > 55 && i <= 112)
          eqBands.tempBandValues[5] += (int)globals.vReal[i];
        if (i > 112 && i <= 229)
          eqBands.tempBandValues[6] += (int)globals.vReal[i];
        if (i > 229)
          eqBands.tempBandValues[7] += (int)globals.vReal[i];

        /*16 bands, 12kHz top band 
        if (i<=2 )           eqBands.tempBandValues[0]  += (int)globals.vReal[i];
        if (i>2   && i<=3  ) eqBands.tempBandValues[1]  += (int)globals.vReal[i];
        if (i>3   && i<=5  ) eqBands.tempBandValues[2]  += (int)globals.vReal[i];
        if (i>5   && i<=7  ) eqBands.tempBandValues[3]  += (int)globals.vReal[i];
        if (i>7   && i<=9  ) eqBands.tempBandValues[4]  += (int)globals.vReal[i];
        if (i>9   && i<=13 ) eqBands.tempBandValues[5]  += (int)globals.vReal[i];
        if (i>13  && i<=18 ) eqBands.tempBandValues[6]  += (int)globals.vReal[i];
        if (i>18  && i<=25 ) eqBands.tempBandValues[7]  += (int)globals.vReal[i];
        if (i>25  && i<=36 ) eqBands.tempBandValues[8]  += (int)globals.vReal[i];
        if (i>36  && i<=50 ) eqBands.tempBandValues[9]  += (int)globals.vReal[i];
        if (i>50  && i<=69 ) eqBands.tempBandValues[10] += (int)globals.vReal[i];
        if (i>69  && i<=97 ) eqBands.tempBandValues[11] += (int)globals.vReal[i];
        if (i>97  && i<=135) eqBands.tempBandValues[12] += (int)globals.vReal[i];
        if (i>135 && i<=189) eqBands.tempBandValues[13] += (int)globals.vReal[i];
        if (i>189 && i<=264) eqBands.tempBandValues[14] += (int)globals.vReal[i];
        if (i>264          ) eqBands.tempBandValues[15] += (int)globals.vReal[i];*/
      }
    }

    //Refresh main variables with temp data
    for (int i = 0; i < NUM_BANDS; i++)
    {
      eqBands.bandValues[i] = eqBands.tempBandValues[i];
    }

    //Look for Peaks
    for (byte band = 0; band < NUM_BANDS; band++)
    {

      if (eqBands.bandValues[band] > eqBands.peak[band])
      {
        eqBands.peak[band] = eqBands.bandValues[band];
      }

      // Decay peak
      for (byte band = 0; band < NUM_BANDS; band++)
        if (eqBands.peak[band] > 500)
          eqBands.peak[band] -= 500;
    }

    //Update variables compared to current encoder location
    updateEncoders();

    updateTime();

    updateWeather();

    //We are only serving DNS requests to Soft AP clients
    if (globals.softAPEnable == 1)
    {
      dnsServer.processNextRequest();
    }

    devEnv.fftps++; //Debug, tracking loops per second

    //Serial.println(xPortGetFreeHeapSize()); //How much memory is left in the task heap? If out we get a panic with "Stack canary watchpoint triggered"
    //vTaskDelay(50); //Give some time back to the scheduler. Normally this task never lets up. Use this to share resousrces better on assigned core.
  }
}

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

void updateEncoders()
{
  //--CLICK--

  //Read knob 1 digital pin, button pulls pin low
  globals.tempValue = digitalRead(KNOB_1C);

  //Is the button pulling the pin low and the debounce counter is at 0 (no recent button press) ?
  if ((globals.tempValue == false) && (knob1.debounce == 0))
  {
    //if yes we should set a debounce variable
    knob1.debounce = 3;

    //And set click for Knob 1 to True!
    knob1.click = 1;

    //Are we running in normal mode? If not we can skip these checks
    if (globals.runMode == 0)
    {
      //Check to see if the Brightness Knob (#2) is also held down
      if (knob2.debounce == 0)
      {
        //It's not? Just advance the mode by once
        globals.mode += 1;

        //Since we have changed the mode we should save it in a bit
        globalTime.save = 100;

        //And let the fade function know to start
        smoothOperatorStart();

        //Check to make sure we haven't gone over the maximum amount of modes
        if (globals.mode > globals.modeMax)
        {
          //if we did go over let's roll mode back to 0
          globals.mode = 0;
        }

        //Clear up some other variables
        knob2.heldTime = 0;
      }
      else
      {
        //brightness knob is clicked at the same time as the program knob?
        //Change the globals.runMode variable to Menu
        globals.runMode = 1;
        globalMenu.currentMenu = 0;           //Select main menu page
        globalMenu.currentMenuMultiplier = 1; //Set multiplier back to 1, just in case (used in ZIP Code)
        knob1.click = 0;                      //Null out clicks so menu doesn't get confused on first run
        knob2.click = 0;
      }
    }

    //Are we in clock/weather/visualizer/sleep mode?
    if (globals.runMode == 3)
    {
      globals.runMode = -1;
      knob1.click = 0;
    }
  }
  if ((globals.tempValue == true) && (knob1.debounce > 0)) //No button press and there is debounce to reduce?
  {
    knob1.debounce -= 1;
  }

  //Read knob 2 digital pin, button pulls pin low
  globals.tempValue = digitalRead(KNOB_2C);
  if ((globals.tempValue == false) && (knob2.debounce == 0))
  {
    knob2.debounce = 3;
    knob2.click = 1;

    if (globals.runMode == 3)
    {
      globals.runMode = -1;
      knob2.click = 0;
    }
  }
  else if ((globals.tempValue == false) && (knob2.debounce > 0))
  {
    knob2.heldTime += 1;
  }
  if ((globals.tempValue == true) && (knob2.debounce > 0))
  {
    knob2.debounce -= 1;
  }

  if ((knob2.heldTime > 69) && (globals.mode != 5)) //Can't set a favorite of a favorite
  {
    //Save Favorite Menu
    knob2.heldTime = 0;
    globals.runMode = 1;         //enter Menu Mode
    globalMenu.currentMenu = 10; //Select the 10th menu, New Favorite
    //globalMenu.menu[10] = 0;
  }

  //--PATTERN ENCODER--

  globals.tempValue = globals.encoder.getCount() - knob1.temp; //Read current knob position vs. last time we checked

  if (globals.runMode == 0)
  {
    while (globals.tempValue >= 4)
    { //Quadrature encoder sends 4 pulses for each physical detent. Anything less than that we ignore
      globals.tempValue -= 4;
      knob1.temp += 4;
      patternSettings.pattern[globals.mode] += 1;
      smoothOperatorStart();
    }
    while (globals.tempValue <= -4)
    {
      globals.tempValue += 4;
      knob1.temp -= 4;
      patternSettings.pattern[globals.mode] -= 1;
      smoothOperatorStart();
    }

    //Constrain Mode - add switch to allow 3 options - constrain; rollover back to beginning/end; rollover to next/previous mode
    if (patternSettings.pattern[globals.mode] > globalMenu.patternMax[globals.mode])
    {
      //Mode 1 - constrain
      patternSettings.pattern[globals.mode] = globalMenu.patternMax[globals.mode];
    }
    if (patternSettings.pattern[globals.mode] <= 0)
    {
      //Mode 1 - constrain
      patternSettings.pattern[globals.mode] = 0;
    }
  }
  else if (globals.runMode == 1)
  {
    while (globals.tempValue >= 4)
    { //Quadrature encoder sends 4 pulses for each physical detent. Anything less than that we ignore
      globals.tempValue -= 4;
      knob1.temp += 4;
      globalMenu.menu[globalMenu.currentMenu] += 1 * globalMenu.currentMenuMultiplier;
    }
    while (globals.tempValue <= -4)
    {
      globals.tempValue += 4;
      knob1.temp -= 4;
      globalMenu.menu[globalMenu.currentMenu] -= 1 * globalMenu.currentMenuMultiplier;
    }

    if (globalMenu.menu[globalMenu.currentMenu] > globalMenu.menuMax[globalMenu.currentMenu])
    {
      //Mode 1 - constrain
      globalMenu.menu[globalMenu.currentMenu] = globalMenu.menuMax[globalMenu.currentMenu];
    }
    else if (globalMenu.menu[globalMenu.currentMenu] < 0)
    {
      //Mode 1 - constrain
      globalMenu.menu[globalMenu.currentMenu] = 0;
    }
  }
  else if (globals.runMode == 2)
  {
    while (globals.tempValue >= 4)
    { //Quadrature encoder sends 4 pulses for each physical detent. Anything less than that we ignore
      globals.tempValue -= 4;
      knob1.temp += 4;
      player.X += 4;
    }
    while (globals.tempValue <= -4)
    {
      globals.tempValue += 4;
      knob1.temp -= 4;
      player.X -= 4;
    }
  }
  else if (globals.runMode == 3)
  {
    while (globals.tempValue >= 4)
    { //Quadrature encoder sends 4 pulses for each physical detent. Anything less than that we ignore
      globals.tempValue -= 4;
      knob1.temp += 4;
      globals.runMode = -1;
    }
    while (globals.tempValue <= -4)
    {
      globals.tempValue += 4;
      knob1.temp -= 4;
      globals.runMode = -1;
    }
  }
  //check for out of sync condition (knob is reseting at value that is not divisible by 4)
  if ((abs(globals.encoder.getCount()) % 4) > 0)
  {
    utils.encoderUnstick++;
  }
  else
  {
    utils.encoderUnstick = 0;
  }
  if (utils.encoderUnstick > 200)
  {
    globals.encoder.clearCount();
    knob1.temp = 0;
  }

  //--BRIGHTNESS ENCODER--

  globals.tempValue = globals.encoder2.getCount() - knob2.temp; //Read current knob position vs. last time we checked
  knob2.temp = globals.encoder2.getCount();                     //Store this position to compare next time around

  if ((globals.runMode == 0) || (globals.runMode == 3))
  {
    if (globals.tempValue != 0)
    {
      brightness.debounce = millis() + 1420;
      globalTime.save = 100;
    }

    //Determine "acceleration" based on change amount. Large change = fast turn of knob
    //There are 96 pulses per revolution

    if (abs(globals.tempValue) > 10) // 100% acceleration
    {
      globals.tempValue = globals.tempValue * 7;
    }
    else if (abs(globals.tempValue) > 7) // 75%
    {
      globals.tempValue = globals.tempValue * 5;
    }
    else if (abs(globals.tempValue) > 4) // 50%
    {
      globals.tempValue = globals.tempValue * 3;
    }
    else if (abs(globals.tempValue) > 2) // 25%  acceleration
    {
      globals.tempValue = globals.tempValue * 2;
    }
    else //No acceleration applied
    {
      globals.tempValue = globals.tempValue;
    }

    //Add adjusted value to brightness
    brightness.current += globals.tempValue;

    //Constrain (for some reason constrain function gave me fits)
    if (brightness.current > 255)
    {
      brightness.current = 255;
    }
    if (brightness.current < 0)
    {
      brightness.current = 0;
    }

    // set master brightness control
    FastLED.setBrightness(brightness.current);
  }
  else if (globals.runMode == 2)
  {
    while (globals.tempValue > 0)
    { //Quadrature encoder sends 4 pulses for each physical detent. Anything less than that we ignore
      globals.tempValue -= 1;
      player.Y += 1;
    }
    while (globals.tempValue < 0)
    {
      globals.tempValue += 1;
      player.Y -= 1;
    }
  }
}

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

void setGameMode()
{
  globals.runMode = 2;                                         //game mode
  brightness.temp = brightness.current;                        //save brightness
  globals.tempPattern = patternSettings.pattern[globals.mode]; //and program in case they get messed up

  switch (globalMenu.menu[1]) //Call reset code for whatever game we're about to run
  {
  case 0:
    fallios_reset();
    break;
  case 1:
    blockbreaker_reset();
    break;
  case 2:
    //tetris_reset();
    break;
  }
}

void endGameMode()
{
  //Run update encoder to sync encoders
  updateEncoders();

  //Set values to right when game mode started in case they got dorked with
  brightness.current = brightness.temp;
  patternSettings.pattern[globals.mode] = globals.tempPattern;

  //Don't want to see brightness indicator when we leave
  brightness.debounce = 0;

  //Set globals.runMode to -1 to reset system vars and runMode back to 0
  globals.runMode = -1;
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
    u8g2.drawXBMP(0, 0, STAR_WIDTH, STAR_HEIGHT, STAR_SHAPE);
    break;
  case 1:
    u8g2.drawXBMP(0, 0, WAVE_WIDTH, WAVE_HEIGHT, WAVE);
    // u8g2.drawXBMP(0,0,MUSIC_NOTE_WIDTH, MUSIC_NOTE_HEIGHT, MUSIC_NOTE);
    break;
  case 2:
    u8g2.drawXBMP(0, 0, HASHTAG_WIDTH, HASHTAG_HEIGHT, HASHTAG);
    break;
  case 3:
    u8g2.drawXBMP(0, 0, DONUT_WIDTH, DONUT_HEIGHT, DONUT);
    break;
  case 4:
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

void convertUnixToTime(time_t t)
{
  struct tm ts;
  char buf[80];

  // Get current time
  time(&t);

  // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
  ts = *localtime(&t);
  strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
  Serial.println("time stuff --------------");
  Serial.println(buf);
}

time_t timeConvert(String timeToConvert)
{
  struct tm tm;
  char __createdTime[sizeof(timeToConvert)];
  timeToConvert.toCharArray(__createdTime, sizeof(__createdTime));
  strptime(__createdTime, "%H:%M:%S", &tm);
  time_t t = mktime(&tm); // t is now your desired time_t
  return t;
}
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
void drawMenu()
{
}
void drawMenuCommander()
{
  u8g2.setFont(u8g2_font_ncenB08_tr);

  u8g2_horizontal_line(9);

  switch (globalMenu.currentMenu)
  {
  case 0: // Draw Image
  {
    drawMenuWords("Welican Gemina",
                  "Games", "Settings", "Stuff", "Exit");
    drawMenuSelectionFrames();
  }
  break;
  case 1: // Draw Games
  {
    drawMenuWords("Games",
                  "Fallios", "Block Breaker", "Tetris");
    drawMenuSelectionFrames();
  }
  break;
  case 2: // Draw Settings
  {
    drawMenuWords("Settings",
                  "LED Config", "Favorites", "ZIP Code", "WIFI");
    drawMenuSelectionFrames();
  }
  break;
  case 3: // LED Count Menu
  {
    drawMenuTop("Settings > LED Count");
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
  case 5: // Favorites Menu
  {
    drawMenuWords("Settings > Favorites",
                  "Add New", "Set Max", "Reset", "Back");
    drawMenuSelectionFrames();
  }
  break;
  case 6:
  {

    drawNumberInput("Set Max Favorites",
                    globalMenu.menu[globalMenu.currentMenu]);

    if (globalMenu.menu[globalMenu.currentMenu] < 1) //gotta have at least 1 favorite
    {
      globalMenu.menu[globalMenu.currentMenu] = 1;
    }
  }
  break;
  case 7: // Favorites Reset Menu
  {
    drawYesNoMenuFrame("Reset All Favorites?");
  }
  break;
  case 8: // WIFI Menu
  {
    drawMenuWords("Settings > WiFi",
                  "Scan", "Host " + globals.softAPEnable, "Connect", "Disconn.");

    u8g2.setCursor(10, 64);
    if (WiFi.status() == WL_CONNECTED)
    {
      int temp = WiFi.SSID().length();

      temp = 44 - (temp * 2);

      if (temp < 0)
      {
        temp = 0;
      }

      u8g2.setCursor(temp, 51);
      u8g2.print(WiFi.SSID());

      u8g2.print("   ");
      u8g2.print(RSSItoPercent(WiFi.RSSI()));
      u8g2.print("%");

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
      u8g2.setCursor(25, 60);
      u8g2.print("Not Connected");
    }
    drawMenuSelectionFrames();
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
        u8g2.setCursor(10, 19 + (9 * i));
        u8g2.print(RSSItoPercent(WiFi.RSSI(i)));
        u8g2.setCursor(25, 19 + (9 * i));
        u8g2.print((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
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
  }

  // Back Button
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
    case 4: //Zip Code Menu
      globalMenu.currentMenu = 2;
      break;
    case 5: //Favorites Main Menu
      globalMenu.currentMenu = 2;
      break;
    case 6: //Favorites Set Max
      globalMenu.currentMenu = 5;
      break;
    case 8: //WiFi Menu
      globalMenu.currentMenu = 2;
      break;
    case 10: //Add New Favorite
      globals.runMode = -1;
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
      globalMenu.menu[13] = 0;
      globalMenu.currentMenu = 12;
      break;
    }
  }

  // Forward/Confirm Button
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
        globalMenu.currentMenu = 2; // settings
        break;
      case 2: // stuff
        break;
      case 3:
        globals.runMode = -1; // exit
        break;
      }
      break;
    case 1: // games menu click
      switch (globalMenu.menu[globalMenu.currentMenu])
      {
      case 0:
        globals.runMode = 2; // game mode
        setGameMode();
        break;
      case 1:
        globals.runMode = 2; // game mode
        setGameMode();
        break;
      case 2:
        break;
      case 4:
        globalMenu.currentMenu = 0; // back to main menu
        break;
      }
    }
    break;
    case 2: // Settings click
    {
      switch (globalMenu.menu[globalMenu.currentMenu])
      {
      case 0: //LED Count
        break;
      case 1: // Favorites Settings Menu
        globalMenu.currentMenu = 5;
        break;
      case 2: // ZIP Code
        globalMenu.currentMenu = 4;
        break;
      case 3: // Wifi
        globalMenu.currentMenu = 8;
        break;
      }
    }
    break;
    case 4: // ZIP Code settings click
    {
      globalMenu.currentMenuMultiplier = 10000;
      globalMenu.currentMenu = 11;
      readZipCode();
    }
    break;
    case 5: // Favorites Setting Menu Click
    {
      switch (globalMenu.menu[globalMenu.currentMenu])
      {
      case 0: // Add New, can't favorite a favorite!
        if (globals.mode != 5)
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
        globalMenu.currentMenu = 2;
        break;
      }
    }
    break;
    case 6: // Set Max Favorites Click
    {
      patternSettings.numberOfFavorites = globalMenu.menu[globalMenu.currentMenu];
      globalMenu.patternMax[5] = patternSettings.numberOfFavorites;
      globalMenu.menuMax[10] = patternSettings.numberOfFavorites;
      EEPROM.write(99, patternSettings.numberOfFavorites);
      EEPROM.commit();
      globalMenu.currentMenu = 5;
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
      }
      break;
      case 3: // Disconnect
        WiFi.disconnect();
        break;
      }
    }
    break;
    case 10: // New Favorites Click
    {
      saveFavorites();
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
        weatherSettings.zipCode = globalMenu.menu[11]; //Update ZIP Code
        globalMenu.currentMenuMultiplier = 1;
        globalMenu.currentMenu = 2; //Go back to main
        writeZipCode();
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
    }
  }
}

void WiFiScan()
{
  //Serial.println("scan starting");
  //globalMenu.currentMenu = 12;
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  globals.networkScan = WiFi.scanNetworks();
  //Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
}

int RSSItoPercent(int RSSI)
{
  int percent = RSSI + 30;

  percent = abs(percent);

  percent = percent * 1.4;
  if (percent > 99)
  {
    percent = 99;
  }
  if (percent < 1)
  {
    percent = 1;
  }

  percent = 100 - percent;

  return percent;
}

void setZipCodeMenu()
{
  drawMenuTop("Set ZIP Code");

  u8g2.setCursor(54, 26);
  if (globalMenu.menu[globalMenu.currentMenu] < 10000)
  {
    u8g2.print("0");
  }
  if (globalMenu.menu[globalMenu.currentMenu] < 1000)
  {
    u8g2.print("0");
  }
  if (globalMenu.menu[globalMenu.currentMenu] < 100)
  {
    u8g2.print("0");
  }
  if (globalMenu.menu[globalMenu.currentMenu] < 10)
  {
    u8g2.print("0");
  }

  u8g2.print(globalMenu.menu[globalMenu.currentMenu]);

  u8g2.setCursor(54, 46);
  switch (globalMenu.currentMenuMultiplier)
  {
  case 10000:
    u8g2.print("^");
    break;
  case 1000:
    u8g2.print("  ^");
    break;
  case 100:
    u8g2.print("    ^");
    break;
  case 10:
    u8g2.print("      ^");
    break;
  case 1:
    u8g2.print("        ^");
    break;
  }
}

void writeZipCode()
{
  //Break ZIP into 3 bytes as EEPROM is 1 byte per space. ZIP is a (16 bit) unsigned integer
  uint8_t xlow = globalMenu.menu[11] & 0xff;
  uint8_t xmed = (globalMenu.menu[11] >> 8) & 0xff;
  uint8_t xhigh = (globalMenu.menu[11] >> 16) & 0xff;
  //Save the 16 bit unsigned integer into two bytes of EEPROM
  EEPROM.write(90, xlow);
  EEPROM.write(91, xmed);
  EEPROM.write(92, xhigh);
  EEPROM.commit();
}

void readZipCode()
{
  //readZipCode
  //globalMenu.menu[11] = EEPROM.read(90) + (EEPROM.read(91) * 256) + (EEPROM.read(92) * 65536);

  EEPROM.get(90, globalMenu.menu[11]);

  //Make sure data is in range. If not, set to default ZIP code
  if ((globalMenu.menu[11] > 99999) || (globalMenu.menu[11] == 0))
  {
    globalMenu.menu[11] = 33701;
  }
}

void updateZipCodeString()
{
  u8g2.setCursor(44, 30);

  weatherSettings.zipCode = String(globalMenu.menu[11]);

  if (globalMenu.menu[11] < 10000)
  {
    weatherSettings.zipCode = "0" + String(globalMenu.menu[11]);
  }
  if (globalMenu.menu[11] < 1000)
  {
    weatherSettings.zipCode = "00" + String(globalMenu.menu[11]);
  }
  if (globalMenu.menu[11] < 100)
  {
    weatherSettings.zipCode = "000" + String(globalMenu.menu[11]);
  }
  if (globalMenu.menu[11] < 10)
  {
    weatherSettings.zipCode = "0000" + String(globalMenu.menu[11]);
  }
  if (globalMenu.menu[11] == 0)
  {
    weatherSettings.zipCode = "00000";
  }
}

void newFavoritesMenu()
{
  drawMenuTop("Add New Favorite");

  //This is a menu with patternSettings.numberOfFavorites 'selections', each indicating a favorite slot
  if (globalMenu.menu[globalMenu.currentMenu] < 10)
  {
    u8g2.setCursor(57, 26);
  }
  else
  {
    u8g2.setCursor(54, 26);
  }

  u8g2.print(globalMenu.menu[globalMenu.currentMenu]);

  u8g2.drawRFrame(50, 14, 20, 16, 3);

  //Call the favorite for the slot we're looking at
  //The real function call is below this, so LEDs will not show bad data
  favorites_category(globalMenu.menu[globalMenu.currentMenu]);

  //Convert the strings
  globalStrings.functionName.toCharArray(globalStrings.functionNameOutString, 20);
  globalStrings.categoryName.toCharArray(globalStrings.categoryNameOutString, 20);

  u8g2.setCursor(16, 44);
  u8g2.print("Current Setting");
  //u8g2.print(globalStrings.categoryNameOutString);

  switch (patternSettings.favoriteMode[globalMenu.menu[globalMenu.currentMenu]])
  {
  case 0:
    u8g2.drawXBMP(2, 53, STAR_WIDTH, STAR_HEIGHT, WAVE);
    break;
  case 1:
    u8g2.drawXBMP(2, 53, WAVE_WIDTH, WAVE_HEIGHT, WAVE);
    // u8g2.drawXBMP(0,0,MUSIC_NOTE_WIDTH, MUSIC_NOTE_HEIGHT, MUSIC_NOTE);
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

void saveFavorites()
{
  EEPROM.write(100 + globalMenu.menu[globalMenu.currentMenu] * 2, patternSettings.pattern[globals.mode]); //the pattern we're on
  EEPROM.write(101 + (globalMenu.menu[globalMenu.currentMenu] * 2), globals.mode);                        //the mode we're on

  EEPROM.commit(); //write it to memory

  patternSettings.favoriteMode[globalMenu.menu[globalMenu.currentMenu]] = globals.mode;                             //update running variables
  patternSettings.favoritePattern[globalMenu.menu[globalMenu.currentMenu]] = patternSettings.pattern[globals.mode]; //first updated in readFavorites
}

void readFavorites()
{
  //Read the favorites from EEPROM
  for (int i = 0; i < 50; i++)
  {
    patternSettings.favoritePattern[i] = EEPROM.read(100 + i * 2);
    patternSettings.favoriteMode[i] = EEPROM.read(101 + i * 2);
    //check for out of range data, 255 indicates default setting
    if (patternSettings.favoritePattern[i] == 255 || patternSettings.favoriteMode[i] == 255)
    {
      patternSettings.favoritePattern[i] = 0;
      patternSettings.favoriteMode[i] = 0;
    }
  }

  patternSettings.numberOfFavorites = EEPROM.read(99);
  if (patternSettings.numberOfFavorites == 0)
  {
    patternSettings.numberOfFavorites = 25;
  }
  globalMenu.patternMax[5] = patternSettings.numberOfFavorites;
  globalMenu.menuMax[10] = patternSettings.numberOfFavorites;
}

void resetFavorites()
{
  //Just Favorites
  for (int i = 0; i < 50; i++)
  {
    //Set everything to 0
    patternSettings.favoritePattern[i] = 0;
    patternSettings.favoriteMode[i] = 0;

    //including EEPROM area
    EEPROM.write((100 + (i * 2)), 0);
    EEPROM.write((101 + (i * 2)), 0);
  }

  //TESTING - Reset ALL MEMORY WITH THIS FUNCTION
  for (int i = 0; i < 511; i++)
  {
    EEPROM.write(i, 0);
  }

  EEPROM.commit(); //write it to memory
}

void smoothOperator()
{
  //Check for interfade
  if (globalLED.interfade == 0)
  {
    /*
    //take snapshot
    for (int i = 0; i < NUM_LEDS; i++)
    {
      patternSettings.tempLeds[i] = patternSettings.leds[i];
    }
    */
  }
  else
  {
    for (int i = 0; i < NUM_LEDS; i++)
    {
      patternSettings.leds[i] = blend(patternSettings.leds[i], patternSettings.tempLeds[i], globalLED.interfade * globalLED.interfadeSpeed);
    }

    //Only want to interfade for a bit
    globalLED.interfade -= 1;

    if (globalLED.interfade < 1)
    {
      globalLED.interfade = 0;
    }
  }
}

//make this an int and calculate variables based on time
void smoothOperatorStart()
{
  globalLED.interfade = globalLED.interfadeMax;

  for (int i = 0; i < NUM_LEDS; i++)
  {
    patternSettings.tempLeds[i] = patternSettings.leds[i];
  }

  globalTime.save = 100;

  globalTime.touchTime = millis();
}

void updateTime()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    if (globalTime.currentHour == 100)
    {
      configTime(3600 * globals.timeZone, 0, globals.ntpServer, NULL, NULL);

      setenv("TZ", "EST5EDT,M3.2.0,M11.1.0", 1);
    }

    getLocalTime(&timeinfo);                   //Update time struct with new data
    globalTime.currentDay = timeinfo.tm_wday;  //Update day
    globalTime.currentHour = timeinfo.tm_hour; //Update hour
    //Are we in PM/ over 12 hours?

    if (globalTime.currentHour > 12)
    {
      globalTime.currentHour -= 12;
      globalTime.currentPM = 1;
    }
    else
    {
      globalTime.currentPM = 0; //If not then it is morning time
    }

    globalTime.currentMinute = timeinfo.tm_min; //Update minutes
  }
}

void updateWeather()
{
  if (globals.runMode == 3)
  {
    EVERY_N_MILLISECONDS(weatherSettings.weatherTimerDelay)
    {
      if (WiFi.status() == WL_CONNECTED)
      {
        weatherSettings.zipCode = globalMenu.menu[11];
        String serverPath = "http://api.openweathermap.org/data/2.5/weather?zip=" + weatherSettings.zipCode + "," + weatherSettings.countryCode + "&units=imperial&APPID=" + globals.openWeatherMapApiKey;

        weather.jsonBuffer = httpGETRequest(serverPath.c_str());
        weather.weatherJson = JSON.parse(weather.jsonBuffer);

        // JSON.typeof(jsonVar) can be used to get the type of the var
        if (JSON.typeof(weather.weatherJson) == "undefined")
        {
          Serial.println("Parsing input failed!");
          return;
        }

        Serial.println("JSON object = ");
        Serial.println(weather.weatherJson);

        weather.currentTemperature = weather.weatherJson["main"]["temp"];
        weather.currentTemperatureMax = weather.weatherJson["main"]["temp_max"];
        weather.currentTemperatureMax = weather.weatherJson["main"]["temp_min"];
        weather.currentHumidity = weather.weatherJson["main"]["humidity"];
        weather.currentWindSpeed = weather.weatherJson["wind"]["speed"];
        weather.currentWeatherId = weather.weatherJson["weather"][0]["id"];
        weather.currentWeatherTitle = weather.weatherJson["weather"][0]["main"];
        weather.currentWeatherDescription = weather.weatherJson["weather"][0]["description"];
        weather.sunrise = weather.weatherJson["sys"]["sunrise"];
        weather.sunset = weather.weatherJson["sys"]["sunset"];

        convertUnixToTime(timeConvert(weather.sunrise));
        convertUnixToTime(timeConvert(weather.sunset));

        Serial.print("Temperature: ");
        Serial.println(weather.weatherJson["main"]["temp"]);

        Serial.print("Temperature Max: ");
        Serial.println(weather.weatherJson["main"]["temp_max"]);

        Serial.print("Temperature Min: ");
        Serial.println(weather.weatherJson["main"]["temp_min"]);

        Serial.print("Humidity: ");
        Serial.println(weather.weatherJson["main"]["humidity"]);

        Serial.print("Wind Speed: ");
        Serial.println(weather.weatherJson["wind"]["speed"]);

        Serial.print("Sunrise: ");
        Serial.println(weather.weatherJson["sys"]["sunrise"]);

        Serial.print("Sunset: ");
        Serial.println(weather.weatherJson["sys"]["sunset"]);

        Serial.print("currentWeatherId: ");
        Serial.println(weather.weatherJson["weather"][0]["id"]);

        Serial.print("currentWeatherTitle: ");
        Serial.println(weather.currentWeatherTitle);

        Serial.print("currentWeatherDescription: ");
        Serial.println(weather.currentWeatherDescription);
      }
      else
      {
        Serial.println("Weather - No Connection");
      }
    }
  }
}

void saveTimeCheck()
{
  if (globalTime.save > 0)
  {
    globalTime.save -= 1;
  }

  if (globalTime.save == 1)
  {
    globalTime.touchTime = millis();

    EEPROM.write(0, globals.mode);
    EEPROM.write(1, brightness.current);

    for (int i = 0; i <= globals.modeMax; i++)
    {
      EEPROM.write(2 + i, patternSettings.pattern[i]);
    }
    EEPROM.commit();
  }

  if (globals.runMode == 0)
  {
    if ((millis() - globalTime.touchTime) > globalTime.timeOut)
    {
      globals.runMode = 3;
    }
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

String httpGETRequest(const char *serverName)
{
  HTTPClient http;

  // Your IP address with path or Domain name with URL path
  http.begin(serverName);

  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload = "{}";

  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
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

void addGlitter(fract8 chanceOfGlitter)
{
  if (random8() < chanceOfGlitter)
  {
    patternSettings.leds[random16(NUM_LEDS)] += CRGB::White;
  }
}

void customColor(int r, int g, int b)
{
  fill_solid(patternSettings.leds, LEDS_IN_STRIP, CRGB(r, g, b));
}

void plasma(CRGBPalette16 currentPalette, TBlendType currentBlending)
{ // This is the heart of this program. Sure is short. . . and fast.

  int thisPhase = beatsin8(6, -64, 64); // Setting phase change for a couple of waves.
  int thatPhase = beatsin8(7, -64, 64);

  for (int k = 0; k < NUM_LEDS; k++)
  { // For each of the LED's in the strand, set a brightness based on a wave as follows:

    int colorIndex = cubicwave8((k * 23) + thisPhase) / 2 + cos8((k * 15) + thatPhase) / 2; // Create a wave and add a phase change and add another wave with its own phase change.. Hey, you can even change the frequencies if you wish.
    int thisBright = QSUBA(colorIndex, beatsin8(7, 0, 96));                                 // qsub gives it a bit of 'black' dead space by setting sets a minimum value. If colorIndex < current value of beatsin8(), then bright = 0. Otherwise, bright = colorIndex..

    patternSettings.leds[k] = ColorFromPalette(currentPalette, colorIndex, thisBright, currentBlending); // Let's now add the foreground colour.
  }
}
void beatwave(CRGBPalette16 currentPalette, TBlendType currentBlending)
{
  // https://github.com/atuline/FastLED-Demos/blob/master/beatwave/beatwave.ino

  uint8_t wave1 = beatsin8(9, 0, 255); // That's the same as beatsin8(9);
  uint8_t wave2 = beatsin8(8, 0, 255);
  uint8_t wave3 = beatsin8(7, 0, 255);
  uint8_t wave4 = beatsin8(6, 0, 255);

  for (int i = 0; i < NUM_LEDS; i++)
  {
    patternSettings.leds[i] = ColorFromPalette(currentPalette, i + wave1 + wave2 + wave3 + wave4, 255, currentBlending);
  }
}

void showStrip()
{
// #ifdef ADAFRUIT_NEOPIXEL_H
//   // NeoPixel
//   strip.show();
// #endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  FastLED.show();
#endif
}

void setPixel(int pixel, byte red, byte green, byte blue)
{

  // #ifdef ADAFRUIT_NEOPIXEL_H

  //   // NeoPixel

  //   strip.setPixelColor(pixel, strip.Color(red, green, blue));

  // #endif

#ifndef ADAFRUIT_NEOPIXEL_H

  // FastLED
  patternSettings.leds[pixel] = CRGB(red, green, blue);

  // patternSettings.leds[pixel].setRGB(red, green, blue);

  // patternSettings.leds[pixel].r = red;

  // patternSettings.leds[pixel].g = green;

  // patternSettings.leds[pixel].b = blue;

#endif
}
void setPixel(int pixel, CRGB color)
{

  // #ifdef ADAFRUIT_NEOPIXEL_H

  //   // NeoPixel

  //   strip.setPixelColor(pixel, strip.Color(red, green, blue));

  // #endif

#ifndef ADAFRUIT_NEOPIXEL_H

  // FastLED
  patternSettings.leds[pixel] = CRGB(color);

  // patternSettings.leds[pixel].setRGB(color);

#endif
}

void setAll(byte red, byte green, byte blue)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

void fadeLightBy(int pixel, int brightnes)
{

#ifndef ADAFRUIT_NEOPIXEL_H

  // FastLED

  patternSettings.leds[pixel].fadeLightBy(brightnes);
#endif
}

void fadeToBlack(int ledNo, byte fadeValue)
{
// #ifdef ADAFRUIT_NEOPIXEL_H
//   // NeoPixel
//   uint32_t oldColor;
//   uint8_t r, g, b;
//   int value;

//   oldColor = strip.getPixelColor(ledNo);
//   r = (oldColor & 0x00ff0000UL) >> 16;
//   g = (oldColor & 0x0000ff00UL) >> 8;
//   b = (oldColor & 0x000000ffUL);

//   r = (r <= 10) ? 0 : (int)r - (r * fadeValue / 256);
//   g = (g <= 10) ? 0 : (int)g - (g * fadeValue / 256);
//   b = (b <= 10) ? 0 : (int)b - (b * fadeValue / 256);

//   strip.setPixelColor(ledNo, r, g, b);
// #endif
#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  patternSettings.leds[ledNo].fadeToBlackBy(fadeValue);
#endif
}

float GetH_BouncingWithLimits(float _speed, float _hHigh, float _hLow)
{
  if (simplexNoise.h > _hHigh)
  {
    simplexNoise.h = _hHigh;
    globalLED.fadeDirection = 0;
  }
  if (simplexNoise.h < _hLow)
  {
    simplexNoise.h = _hLow;
    globalLED.fadeDirection = 1;
  }

  if (globalLED.fadeDirection == 1)
  {
    simplexNoise.h += _speed; // increment to make faster
  }
  if (globalLED.fadeDirection == 0)
  {
    simplexNoise.h -= _speed; // decrement to make faster
  }

  return simplexNoise.h;
}
float GetHTemp_BouncingWithLimits(float _speed, float _hHigh, float _hLow)
{
  if (simplexNoise.hTemp > _hHigh)
  {
    simplexNoise.hTemp = _hHigh;
    globalLED.fadeDirectionHTemp = 0;
  }
  if (simplexNoise.hTemp < _hLow)
  {
    simplexNoise.hTemp = _hLow;
    globalLED.fadeDirectionHTemp = 1;
  }

  if (globalLED.fadeDirectionHTemp == 1)
  {
    simplexNoise.hTemp += _speed; // increment to make faster
  }
  if (globalLED.fadeDirectionHTemp == 0)
  {
    simplexNoise.hTemp -= _speed; // decrement to make faster
  }

  return simplexNoise.hTemp;
}

void DetermineFadeDirection()
{
  if (simplexNoise.yoffset > simplexNoise.yoffsetMax)
  {
    globalLED.fadeDirection2 = 0;
  }
  if (simplexNoise.yoffset < 0)
  {
    globalLED.fadeDirection2 = 1;
  }
}

String websiteProcessor(const String &var)
{
  if (var == "BRIGHTNESS")
  {
    if (brightness.current == 0)
    {
      return "Off";
    }
    else if (brightness.current == 255)
    {
      return "Max";
    }
    else if (brightness.current > 200)
    {
      return "Bright";
    }
    else if (brightness.current > 160)
    {
      return "Half";
    }
    else if (brightness.current > 120)
    {
      return "Third";
    }
    else if (brightness.current > 80)
    {
      return "Quarter";
    }
    else if (brightness.current > 40)
    {
      return "Dim";
    }
    else if (brightness.current > 0)
    {
      return "Moody";
    }
  }

  if (var == "IP_ADDRESS")
  {
    return globals.ipAddress;
  }

  if (var == "CATEGORY_NAME")
  {
    return globalStrings.categoryNameOutString;
  }

  if (var == "FUNCTION_NAME")
  {
    return globalStrings.functionNameOutString;
  }

  if (var == "MODE")
  {
    return website.returnText;
  }

  return String();
}

void confettiCustom(int saturation, int value, int random)
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy(patternSettings.leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  patternSettings.leds[pos] += CHSV(patternSettings.gHue + random8(random), saturation, value);
}

void sinelonCustom(int saturation, int value, int speed, int fadeBy)
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy(patternSettings.leds, NUM_LEDS, fadeBy);
  int pos = beatsin16(speed, 0, NUM_LEDS - 1);
  patternSettings.leds[pos] += CHSV(patternSettings.gHue, saturation, value);
}

void u8g2_horizontal_line(uint8_t a)
{
  u8g2.drawHLine(0, a, 128);
}

/***********************************************************
  Simplex Noise Pattern (Rainbow Cloud Generator)
***********************************************************/
void SimplexNoisePatternInterpolated(float spaceInc, float timeInc, float yoffset, float xoffset)
{

  // Simplex noise for whole strip of LEDs.
  // (Well, it's simplex noise for set number of LEDs and cubic interpolation between those nodes.)

  // Calculate simplex noise for LEDs that are nodes:
  // Store raw values from simplex function (-0.347 to 0.347)
  //float simplexNoise.xoffset = 0.0;
  float xoffset_holder = simplexNoise.xoffset;

  for (int i = 0; i <= LEDS_IN_STRIP; i = i + simplexNoise.nodeSpacing)
  {
    simplexNoise.xoffset += simplexNoise.spaceInc;
    simplexNoise.ledArrayRed[i] = SimplexNoise(simplexNoise.xoffset, simplexNoise.yoffset, 0);
    simplexNoise.ledArrayGreen[i] = SimplexNoise(simplexNoise.xoffset, simplexNoise.yoffset, 1);
    simplexNoise.ledArrayBlue[i] = SimplexNoise(simplexNoise.xoffset, simplexNoise.yoffset, 2);
  }

  simplexNoise.xoffset = xoffset_holder;

  // Interpolate values for LEDs between nodes
  for (int i = 0; i < LEDS_IN_STRIP; i++)
  {
    int position_between_nodes = i % simplexNoise.nodeSpacing;
    int last_node, next_node;

    // If at node, skip
    if (position_between_nodes == 0)
    {
      // At node for simplex noise, do nothing but update which nodes we are between
      last_node = i;
      next_node = last_node + simplexNoise.nodeSpacing;
    }
    // Else between two nodes, so identify those nodes
    else
    {
      // And interpolate between the values at those nodes for red, green, and blue
      float t = float(position_between_nodes) / float(simplexNoise.nodeSpacing);
      float t_squaredx3 = 3 * t * t;
      float t_cubedx2 = 2 * t * t * t;
      simplexNoise.ledArrayRed[i] = simplexNoise.ledArrayRed[last_node] * (t_cubedx2 - t_squaredx3 + 1.0) + simplexNoise.ledArrayRed[next_node] * (-t_cubedx2 + t_squaredx3);
      simplexNoise.ledArrayGreen[i] = simplexNoise.ledArrayGreen[last_node] * (t_cubedx2 - t_squaredx3 + 1.0) + simplexNoise.ledArrayGreen[next_node] * (-t_cubedx2 + t_squaredx3);
      simplexNoise.ledArrayBlue[i] = simplexNoise.ledArrayBlue[last_node] * (t_cubedx2 - t_squaredx3 + 1.0) + simplexNoise.ledArrayBlue[next_node] * (-t_cubedx2 + t_squaredx3);
    }
  }

  // Convert values from raw noise to scaled r,g,b and feed to strip
  for (int i = 0; i < LEDS_IN_STRIP; i++)
  {
    int r = simplexNoise.ledArrayRed[i] * 734 + 16;
    int g = simplexNoise.ledArrayGreen[i] * 734 + 16;
    int b = simplexNoise.ledArrayBlue[i] * 734 + 16;

    if (r > 255)
    {
      r = 255;
    }
    else if (r < 0)
    {
      r = 0;
    } // Adds no time at all. Conclusion: constrain() sucks.

    if (g > 255)
    {
      g = 255;
    }
    else if (g < 0)
    {
      g = 0;
    }

    if (b > 255)
    {
      b = 255;
    }
    else if (b < 0)
    {
      b = 0;
    }
    //Convert to 24 bit output for WS2811

    patternSettings.leds[i] = CRGB(r, g, b);
  }

  if (simplexNoise.yoffset >= 16000)
  {
    simplexNoise.yoffset = -26000;
  }

  if (simplexNoise.yoffset <= -26000)
  {
    simplexNoise.yoffset = 16000;
  }

  if (simplexNoise.xoffset >= 16000)
  {
    simplexNoise.xoffset = -16000;
  }

  if (simplexNoise.xoffset <= -16000)
  {
    simplexNoise.xoffset = 16000;
  }
}

/*****************************************************************************/
// Simplex noise code:
// From an original algorythm by Ken Perlin.
// Returns a value in the range of about [-0.347 .. 0.347]
float SimplexNoise(float x, float y, float z)
{
  // Skew input space to relative coordinate in simplex cell
  simplexNoise.s = (x + y + z) * onethird;
  simplexNoise.g = fastfloor(x + simplexNoise.s);
  simplexNoise.j = fastfloor(y + simplexNoise.s);
  simplexNoise.k = fastfloor(z + simplexNoise.s);

  // Unskew cell origin back to (x, y , z) space
  simplexNoise.s = (simplexNoise.g + simplexNoise.j + simplexNoise.k) * onesixth;
  simplexNoise.u = x - simplexNoise.g + simplexNoise.s;
  simplexNoise.v = y - simplexNoise.j + simplexNoise.s;
  simplexNoise.w = z - simplexNoise.k + simplexNoise.s;

  simplexNoise.A[0] = simplexNoise.A[1] = simplexNoise.A[2] = 0;

  // For 3D case, the simplex shape is a slightly irregular tetrahedron.
  // Determine which simplex we're in
  int hi = simplexNoise.u >= simplexNoise.w ? simplexNoise.u >= simplexNoise.v ? 0 : 1 : simplexNoise.v >= simplexNoise.w ? 1 : 2;
  int lo = simplexNoise.u < simplexNoise.w ? simplexNoise.u < simplexNoise.v ? 0 : 1 : simplexNoise.v < simplexNoise.w ? 1 : 2;

  return k_fn(hi) + k_fn(3 - hi - lo) + k_fn(lo) + k_fn(0);
}

float k_fn(int a)
{
  simplexNoise.s = (simplexNoise.A[0] + simplexNoise.A[1] + simplexNoise.A[2]) * onesixth;
  float x = simplexNoise.u - simplexNoise.A[0] + simplexNoise.s;
  float y = simplexNoise.v - simplexNoise.A[1] + simplexNoise.s;
  float z = simplexNoise.w - simplexNoise.A[2] + simplexNoise.s;
  float t = 0.6f - x * x - y * y - z * z;
  int h = shuffle(simplexNoise.g + simplexNoise.A[0], simplexNoise.j + simplexNoise.A[1], simplexNoise.k + simplexNoise.A[2]);
  simplexNoise.A[a]++;
  if (t < 0)
    return 0;
  int b5 = h >> 5 & 1;
  int b4 = h >> 4 & 1;
  int b3 = h >> 3 & 1;
  int b2 = h >> 2 & 1;
  int b = h & 3;
  float p = b == 1 ? x : b == 2 ? y : z;
  float q = b == 1 ? y : b == 2 ? z : x;
  float r = b == 1 ? z : b == 2 ? x : y;
  p = b5 == b3 ? -p : p;
  q = b5 == b4 ? -q : q;
  r = b5 != (b4 ^ b3) ? -r : r;
  t *= t;
  return 8 * t * t * (p + (b == 0 ? q + r : b2 == 0 ? q : r));
}

int shuffle(int i, int j, int k)
{
  return b(i, j, k, 0) + b(j, k, i, 1) + b(k, i, j, 2) + b(i, j, k, 3) + b(j, k, i, 4) + b(k, i, j, 5) + b(i, j, k, 6) + b(j, k, i, 7);
}
int b(int i, int j, int k, int B)
{
  return T[b(i, B) << 2 | b(j, B) << 1 | b(k, B)];
}
int b(int N, int B)
{
  return N >> B & 1;
}

int fastfloor(float n)
{
  return n > 0 ? (int)n : (int)n - 1;
}

/***********************************************************
  hsv2rgb
  Function: Calculate RGB values for colors represented
    in Hue, Saturation, and Value (brightness).
***********************************************************/
void hsv2rgb(float H, float S, float V, int &R, int &G, int &B)
{
  int var_i;
  float var_1, var_2, var_3, var_h, var_r, var_g, var_b;
  if (S == 0) // HSV values = 0 ÷ 1
  {
    R = V * 255;
    G = V * 255;
    B = V * 255;
  }
  else
  {
    var_h = H * 6;
    if (var_h == 6)
      var_h = 0;        // H must be < 1
    var_i = int(var_h); // Or ... var_i = floor( var_h )
    var_1 = V * (1 - S);
    var_2 = V * (1 - S * (var_h - var_i));
    var_3 = V * (1 - S * (1 - (var_h - var_i)));

    if (var_i == 0)
    {
      var_r = V;
      var_g = var_3;
      var_b = var_1;
    }
    else if (var_i == 1)
    {
      var_r = var_2;
      var_g = V;
      var_b = var_1;
    }
    else if (var_i == 2)
    {
      var_r = var_1;
      var_g = V;
      var_b = var_3;
    }
    else if (var_i == 3)
    {
      var_r = var_1;
      var_g = var_2;
      var_b = V;
    }
    else if (var_i == 4)
    {
      var_r = var_3;
      var_g = var_1;
      var_b = V;
    }
    else
    {
      var_r = V;
      var_g = var_1;
      var_b = var_2;
    }

    // RGB results = 0 ÷ 255 (Production)
    R = (var_r)*255;
    G = (var_g)*255;
    B = (var_b)*255;
  }
}

void objectBounce(BounceModel *item1, u8g2_uint_t objectWidth, u8g2_uint_t objectHeight, const unsigned char object[])
{
  item1->y += item1->vy;
  item1->x += item1->vx;

  if (item1->y <= 0)
  {
    item1->vy = 1;
  }
  if (item1->y >= (VISUALIZER_Y - objectWidth))
  {
    item1->vy = -1;
  }

  if (item1->x <= 0)
  {
    item1->vx = 1;
  }
  if (item1->x >= (VISUALIZER_X - objectHeight))
  {
    item1->vx = -1;
  }

  u8g2.drawXBMP(item1->y, item1->x + 16,
                objectWidth, objectHeight, object);
}

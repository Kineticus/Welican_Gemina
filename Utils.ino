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
        // if (i <= 3)
        //   eqBands.tempBandValues[0] += (int)globals.vReal[i];
        // if (i > 3 && i <= 6)
        //   eqBands.tempBandValues[1] += (int)globals.vReal[i];
        // if (i > 6 && i <= 13)
        //   eqBands.tempBandValues[2] += (int)globals.vReal[i];
        // if (i > 13 && i <= 27)
        //   eqBands.tempBandValues[3] += (int)globals.vReal[i];
        // if (i > 27 && i <= 55)
        //   eqBands.tempBandValues[4] += (int)globals.vReal[i];
        // if (i > 55 && i <= 112)
        //   eqBands.tempBandValues[5] += (int)globals.vReal[i];
        // if (i > 112 && i <= 229)
        //   eqBands.tempBandValues[6] += (int)globals.vReal[i];
        // if (i > 229)
        //   eqBands.tempBandValues[7] += (int)globals.vReal[i];

        //4 bands, 12kHz top band
        if (i <= 13)
          eqBands.tempBandValues[0] += (int)globals.vReal[i];
        if (i > 13 && i <= 55)
          eqBands.tempBandValues[1] += (int)globals.vReal[i];
        if (i > 55 && i <= 112)
          eqBands.tempBandValues[2] += (int)globals.vReal[i];
        if (i > 112)
          eqBands.tempBandValues[3] += (int)globals.vReal[i];

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

      for (int ii = eqBands.averageSamples; ii > 0; ii--)
      {
        eqBands.bandAverages[i][ii] = eqBands.bandAverages[i][ii-1];
      }

        eqBands.bandAverages[i][0] = eqBands.tempBandValues[i];
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

    //autoConnect();

    updateTime();

    updateWeather(false);

    //We are only serving DNS requests to Soft AP clients
    if (globals.softAPEnable == 1)
    {
      dnsServer.processNextRequest();
    }

    devEnv.fftps++; //Debug, tracking loops per second

    //Serial.println(xPortGetFreeHeapSize()); //How much memory is left in the task heap? If out we get a panic with "Stack canary watchpoint triggered"
    vTaskDelay(1); //Give some time back to the scheduler. Normally this task never lets up. Use this to share resousrces better on assigned core.
  }
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
        globalTime.save = 80;

        //Reset touch timer
        globalTime.touchTime = millis();

        //And let the fade function know to start
        startSmoothOperator();

        //New random mode
        pickRandom();

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
  else if ((globals.tempValue == false) && (knob1.debounce > 0))
  {
    knob1.heldTime += 1;
  }

  if ((globals.tempValue == true) && (knob1.debounce > 0)) //No button press and there is debounce to reduce?
  {
    knob1.debounce -= 1;
  }
  else if ((globals.tempValue == true) && (knob1.debounce == 0))
  {
    knob1.heldTime = 0;
  }

  //Read knob 2 digital pin, button pulls pin low
  globals.tempValue = digitalRead(KNOB_2C);

  //If the button is pressed and no debounce
  if ((globals.tempValue == false) && (knob2.debounce == 0))
  {
    knob2.debounce = 3;
    knob2.click = 1;
    globalTime.touchTime = millis();
  }
  //If the button is pressed and debounce
  else if ((globals.tempValue == false) && (knob2.debounce > 0))
  {
    knob2.heldTime += 1;
  }
  //If no button press and debounce
  if ((globals.tempValue == true) && (knob2.debounce > 0))
  {
    knob2.debounce -= 1;
  }
  //If no button press and no debounce
  else if ((globals.tempValue == true) && (knob2.debounce == 0))
  {
    knob2.heldTime = 0;
  }

  /* This is the code to enable long hold of brightness to call the favorite menu
  if ((knob2.heldTime > 69) && (globals.mode != 5)) //Can't set a favorite of a favorite
  {
    //Save Favorite Menu
    knob2.heldTime = 0;
    globals.runMode = 1;         //enter Menu Mode
    globalMenu.currentMenu = 10; //Select the 10th menu, New Favorite
    //globalMenu.menu[10] = 0;
  }
  */

  //--PATTERN ENCODER--

  globals.tempValue = globals.encoder.getCount() - knob1.temp; //Read current knob position vs. last time we checked

  if (globals.runMode == 0)
  {
    while (globals.tempValue >= 4)
    { //Quadrature encoder sends 4 pulses for each physical detent. Anything less than that we ignore
      globals.tempValue -= 4;
      knob1.temp += 4;
      patternSettings.pattern[globals.mode] += 1;
      pickRandom();
      startSmoothOperator();
      //Reset touch timer
      globalTime.touchTime = millis();
      globalTime.save = 80;
    }
    while (globals.tempValue <= -4)
    {
      globals.tempValue += 4;
      knob1.temp -= 4;
      patternSettings.pattern[globals.mode] -= 1;
      pickRandom();
      startSmoothOperator();
      //Reset touch timer
      globalTime.touchTime = millis();
      globalTime.save = 80;
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
      globalTime.save = 80;
    }
    while (globals.tempValue <= -4)
    {
      globals.tempValue += 4;
      knob1.temp -= 4;
      globalMenu.menu[globalMenu.currentMenu] -= 1 * globalMenu.currentMenuMultiplier;
      globalTime.save = 80;
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
      //Reset touch timer
      globalTime.touchTime = millis();
    }
    while (globals.tempValue <= -4)
    {
      globals.tempValue += 4;
      knob1.temp -= 4;
      globals.runMode = -1;
      //Reset touch timer
      globalTime.touchTime = millis();
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

  if (globals.tempValue != 0)
  {
    if ((globals.runMode == 0) || (globals.runMode == 3))
    {
      //Determine "acceleration" based on change amount. Large change = fast turn of knob
      //There are 96 pulses per revolution

      if (abs(globals.tempValue) > 10) // 100% acceleration
      {
        globals.tempValue = globals.tempValue * 7;
      }
      else if (abs(globals.tempValue) > 8) // 75%
      {
        globals.tempValue = globals.tempValue * 5;
      }
      else if (abs(globals.tempValue) > 6) // 50%
      {
        globals.tempValue = globals.tempValue * 3;
      }
      else if (abs(globals.tempValue) > 3) // 25%  acceleration
      {
        globals.tempValue = globals.tempValue * 2;
      }
      else //No acceleration applied
      {
        globals.tempValue = globals.tempValue;
      }

      //Only adjust brightness while knob is not held down
      if(knob2.heldTime == 0)
      {
        //Add adjusted value to brightness in a new integer
        int tempInt = brightness.target + globals.tempValue;

        //Constrain the integer to byte values
        if (tempInt > 255)
        {
          tempInt = 255;
        }
        if (tempInt < 0)
        {
          tempInt= 0;
        }

        //set the current brightness to the constrained byte value
        brightness.target = tempInt;

        //Show the brightness indicator
        brightness.debounce = millis() + 1420;

        //Save the brightness setting 
        globalTime.save = 50;

        //Update last human interaction timer
        globalTime.touchTime = millis();
      }
      else
      {
        if (globals.tempValue > 1)
        {
          globals.tempValue = globals.tempValue * 2;
        }

        //Add adjusted value to pattern adjust in a new integer
        int tempInt = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]] + globals.tempValue;

        //Constrain the integer to byte values
        if (tempInt > 255)
        {
          tempInt = 255;
        }
        if (tempInt < 0)
        {
          tempInt= 0;
        }

        //set the current pattern adjust setting to the constrained byte value
        patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]] = tempInt;
        
        //show the pattern screen for a bit
        brightness.debounce2 = millis() + 1420;
        globalTime.save = 20;
        globalTime.touchTime = millis();
      }
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
}

void setGameMode()
{
  globals.runMode = 2;                                                 //game mode
  brightness.temp = brightness.current;                                //save brightness
  patternSettings.tempPattern = patternSettings.pattern[globals.mode]; //and program in case they get messed up

  switch (globalMenu.menu[1]) //Call reset code for whatever game we're about to run
  {
  case 0:
    fallios_reset();
    break;
  case 1:
    blockbreaker_reset();
    break;
  case 2:
    magic_reset();
    break;
  case 3:
    snake_reset();
    break;
  case 4:
    pong_reset();
    break;
  case 5:
    snake_reset();
    break;
  }
}

void pickRandom()
{
  patternSettings.randomPattern = random(1, globalMenu.patternMax[globals.mode]);
  globals.randomInterval = random(globals.randomMin, globals.randomMax);
  globals.randomTime = millis();
  startSmoothOperator();
}

void endGameMode()
{
  //Run update encoder to sync encoders
  updateEncoders();

  //Set values to right when game mode started in case they got dorked with
  brightness.current = brightness.temp;
  patternSettings.pattern[globals.mode] = patternSettings.tempPattern;

  //Don't want to see brightness indicator when we leave
  brightness.debounce = 0;

  //Set globals.runMode to -1 to reset system vars and runMode back to 0
  globals.runMode = -1;
}

String convertUnixToTime(time_t unixTime)
{
  struct tm ts;
  char buf[80];

  // Get current time
  //time(&t);

  // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
  ts = *localtime(&unixTime);
  // strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
  //strftime(buf, sizeof(buf), "%H:%M:%S %Z", &ts);
  strftime(buf, sizeof(buf), "%I:%M:%S %p", &ts);
  Serial.println("time stuff --------------");
  Serial.println(buf);
  return buf;
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

int RSSItoStrength(int RSSI)
{
  //RSSI range is 0 (best) to -120 (worst)
  int signalStrength = 0;

  if (RSSI > -50)
  {
    signalStrength = 4;
  }
  else if (RSSI > -75)
  {
    signalStrength = 3;
  }
  else if (RSSI > -100)
  {
    signalStrength = 2;
  }
  else
  {
    signalStrength = 1;
  }

  return signalStrength;
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

void putZipCode()
{
  EEPROM.put(90, globalMenu.menu[11]);
  EEPROM.commit();
}

void getZipCode()
{
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

void writeFavorites()
{
  EEPROM.write(100 + globalMenu.menu[globalMenu.currentMenu] * 2, patternSettings.pattern[globals.mode]); //the pattern we're on
  EEPROM.write(101 + (globalMenu.menu[globalMenu.currentMenu] * 2), globals.mode);                        //the mode we're on

  //Write the patternAdjust for the currently selected pattern
  EEPROM.write((300 + (5 * 100) + globalMenu.menu[globalMenu.currentMenu]), patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);


  EEPROM.commit(); //write it to memory

  //Copy over Pattern Adjust to that favorite slot
  patternSettings.patternAdjust[5][globalMenu.menu[globalMenu.currentMenu]] = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]];

  //Copy over Mode & pattern to that favorite slots
  patternSettings.favoriteMode[globalMenu.menu[globalMenu.currentMenu]] = globals.mode;                             //update running variables
  patternSettings.favoritePattern[globalMenu.menu[globalMenu.currentMenu]] = patternSettings.pattern[globals.mode]; //first updated in readFavorites

  //Copy over Pattern Adjust to that favorite slot
  //patternSettings.favoritePatternAdjust[globalMenu.menu[globalMenu.currentMenu]] = patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]];
  //globalTime.save = 3;
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
  //TESTING - Reset ALL MEMORY WITH THIS FUNCTION
  for (int i = 0; i < 2048; i++)
  {
    EEPROM.write(i, 0);
  }

  //JUST FAVORITES
  for (int i = 3; i < 50; i++)
  {
    //Set everything to deault Mode 0 Pattern 1;
    patternSettings.favoritePattern[i] = 1;
    patternSettings.favoriteMode[i] = 0;

    //Set everything to deault Mode 0 Pattern 1;
    EEPROM.write((100 + (i * 2)), 1);
    EEPROM.write((101 + (i * 2)), 0);
  }

  //Write it to memory
  EEPROM.commit();
}

void readNumberOfLEDs()
{
  //Set the # LEDs menu to what the value is
  globalMenu.menu[15] = EEPROM.read(50);

  //Get the Color Order
  globalLED.colorOrder = EEPROM.read(51);

  //Multiply by 5 to find NUM_LEDS
  NUM_LEDS = globalMenu.menu[15] * 5;

  //Finding weird issue when using over 100 where the last LED glitches? Doesn't seem to happen lower.
  if (NUM_LEDS > 99)
  {
    NUM_LEDS += 1;
  }

  //Make sure we are within tested range
  if (NUM_LEDS > 500)
  {
    NUM_LEDS = 500;
  }
  else if (NUM_LEDS < 5)
  {
    NUM_LEDS = 5;
  }

  //Recalculate spacing
  simplexNoise.nodeSpacing = (NUM_LEDS / LEDS_FOR_SIMPLEX);
}

void saveNumberOfLEDs()
{
  EEPROM.write(50, globalMenu.menu[15]);
  EEPROM.write(51, globalLED.colorOrder);
  EEPROM.commit();
  ESP.restart();
}

String dateOrdinal()
{
  String ordinal = "th";

  switch(globalTime.currentDate)
  {
    case 1:
      ordinal = "st";
      break;
    case 2:
      ordinal = "nd";
      break;
    case 3:
      ordinal = "rd";
      break;
    case 21:
      ordinal = "st";
      break;
    case 22:
      ordinal = "nd";
      break;
    case 23:
      ordinal = "rd";
      break;
    case 31:
      ordinal = "st";
      break;
  }

  return ordinal;
}

void updateTime()
{
  if (globalTime.currentHour == 100)
  {
    if (WiFi.status() == WL_CONNECTED)
    {
      configTime(3600 * globals.timeZone, 0, globals.ntpServer, NULL, NULL);

      setenv("TZ", "EST5EDT,M3.2.0,M11.1.0", 1);

      updateTimeProcess();
    }
  }
  EVERY_N_MILLISECONDS(60000)
  {
    //Only update time when in screen saver mode, causes input lags
    if (globals.runMode == 3)
    {
      updateTimeProcess(); //Performance issue culprit
    }
  }
}

void updateTimeProcess()
{
  getLocalTime(&timeinfo);                   //Update time struct with new data
  globalTime.currentDay = timeinfo.tm_wday;  //Update day (0 = Sunday, 6 = Saturday)
  globalTime.currentHour = timeinfo.tm_hour; //Update hour
  globalTime.currentDate = timeinfo.tm_mday; //Update day of the Month
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

void autoConnect()
{
  if ((WiFi.status() == 4) && (globals.networkTries < 4))
  {
    //Try to connect a few times if not connected
    EVERY_N_MILLISECONDS(10000)
    {
      WiFi.disconnect();
      globals.networkTries++;
      //WiFi.enableSTA(true);
      WiFi.begin();
    }
  }
}

void getWeather()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    weatherSettings.zipCode = globalMenu.menu[11];
    String serverPath = "http://api.openweathermap.org/data/2.5/weather?zip=" + weatherSettings.zipCode + "," + weatherSettings.countryCode + "&units=imperial&APPID=" + globals.openWeatherMapApiKey;

    //Daily Forcasts: https://api.openweathermap.org/data/2.5/onecall?lat=27.79&lon=-82.68&units=imperial&exclude=current,minutely,hourly,alerts&appid=8f40cb693f2032badf06d4e432e1dfa6

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

    weather.currentTemperature = String((int)weather.weatherJson["main"]["temp"]);
    weather.currentTemperatureMax = String((int)weather.weatherJson["main"]["temp_max"]);
    weather.currentTemperatureMin = String((int)weather.weatherJson["main"]["temp_min"]);
    weather.currentHumidity = String((int)weather.weatherJson["main"]["humidity"]);
    weather.currentWindSpeed = String((int)weather.weatherJson["wind"]["speed"]);
    weather.currentWeatherId = String((int)weather.weatherJson["weather"][0]["id"]);
    weather.currentWeatherTitle = weather.weatherJson["weather"][0]["main"];
    weather.currentWeatherDescription = weather.weatherJson["weather"][0]["description"];
    //weather.sunrise = (int)weather.weatherJson["sys"]["sunrise"]; // + (3600 * globals.timeZone);
    //weather.sunset = (int)weather.weatherJson["sys"]["sunset"]; // + (3600 * globals.timeZone);

    weather.sunrise = convertUnixToTime((int)weather.weatherJson["sys"]["sunrise"]);
    weather.sunset = convertUnixToTime((int)weather.weatherJson["sys"]["sunset"]);

    //weather.sunrise = convertUnixToTime(timeConvert(weather.sunrise));
    //weather.sunset = convertUnixToTime(timeConvert(weather.sunset));

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
void updateWeather(bool force)
{
  if ((force == true) && (millis() > 10000))
  {
    if ((millis() - weatherSettings.weatherTimerDelay) > weatherSettings.weatherUpdateInterval)
    {
      Serial.println("FORCED NORMAL WEATHER CHECK");
      getWeather();
      weatherSettings.weatherTimerDelay = millis();
    }
  }
  else
  {
    if (globals.runMode == 3)
    {
      //Normal run check
      if  ((millis() - weatherSettings.weatherTimerDelay) > weatherSettings.weatherUpdateInterval)
      {
        Serial.println("NORMAL WEATHER CHECK");
        getWeather();
        weatherSettings.weatherTimerDelay = millis();
      }

      //Initial run check
      if ((weatherSettings.weatherUpdateInitial != 0) && ((millis() - weatherSettings.weatherUpdateInitial) > 0) && (WiFi.status() == WL_CONNECTED))
      {
        Serial.println("INITIAL WEATHER CHECK");
        getWeather();

        //Disable further checks
        weatherSettings.weatherUpdateInitial = 0;
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
    EEPROM.write(0, globals.mode);
    EEPROM.write(1, brightness.current);

    for (int i = 0; i <= globals.modeMax; i++)
    {
      EEPROM.write(2 + i, patternSettings.pattern[i]);
    }

    //Write the patternAdjust for the currently selected pattern
    EEPROM.write((300 + (globals.mode * 100) + patternSettings.pattern[globals.mode]), patternSettings.patternAdjust[globals.mode][patternSettings.pattern[globals.mode]]);

    EEPROM.commit(); //EEPROM commit should not be called while showStrip is running
  }

  if (globals.runMode == 0)
  {
    if (globalTime.timeOut != 0) //Make sure we want to enter screen saver mode
    {
      if ((millis() - globalTime.touchTime) > globalTime.timeOut)
      {
        globals.runMode = 3;
      }
    }
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

void startBreathing()
{
  //future toggle of breathing indicator vs static
  if (devEnv.breathing == 1)
  {
    patternSettings.breath = (exp(sin(millis() / 4200.0 * PI)) - 0.36787944) * 108.0;
    patternSettings.breath = patternSettings.breath / 2;
    if (patternSettings.breath <= 4)
    {
      patternSettings.breath = 4;
    }
  }
  else
  {
    patternSettings.breath = 4;
  }
}

void readPatternSettings()
{
  //Read the pattern setting for each mode
  for (int i = 0; i <= globals.modeMax; i++)
  {
    patternSettings.pattern[i] = EEPROM.read(2 + i);

    //check for out of range data
    if (patternSettings.pattern[i] > globalMenu.patternMax[i])
    {
      patternSettings.pattern[i] = 0;
    }

    for (int ii = 0; ii <= globalMenu.patternMax[i]; ii++)
    {
      patternSettings.patternAdjust[i][ii] = EEPROM.read(300 + (i * 100) + ii);
      //Serial.print(300 + (i * 100) + ii);
      //Serial.print(" - ");
      //Serial.println(patternSettings.patternAdjust[i][ii]);
    }
  }


  //Read the adjust value for each pattern
  //
  //globalMenu.patternMax[i]

  //globals.modeMax
}

void seedThings()
{
  //Seed variables
  for (int i = 0; i < MAX_STARS; i++)
  {
    ball.x[i] = random(0, VISUALIZER_X);
    ball.xx[i] = random(1, 4);
    ball.y[i] = random(0, VISUALIZER_Y);
    ball.yy[i] = random(1, 4);
    ball.z[i] = random(1, 4);
  }
}

void openSpiffFile(String fileLocation)
{
  Serial.println("Opening File: ");
  Serial.println(fileLocation);

  File file = SPIFFS.open(fileLocation);

  if (!file)
  {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.println("File Content:");
  char buffer[64];
  while (file.available())
  {
    int len = file.readBytesUntil('\n', buffer, sizeof(buffer) - 1);
    buffer[len] = 0;
    Serial.println(buffer);
  }

  file.close();
}
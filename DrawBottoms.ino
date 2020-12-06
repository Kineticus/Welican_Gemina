void drawDiscEQ()
{
  globals.temp[0] = eqBands.bandValues[1] / AMPLITUDE;
  globals.temp[0] -= 7;
  if (globals.temp[0] < 2)
  {
    globals.temp[0] = 2;
  }
  if (globals.temp[0] > 20)
  {
    globals.temp[0] = 20;
  }
  u8g2.drawDisc(106, 22, globals.temp[0], U8G2_DRAW_ALL);
}

void drawDiscSectionsEQ()
{
  globals.temp[0] = eqBands.bandValues[0] / AMPLITUDE;
  globals.temp[0] -= 7;
  if (globals.temp[0] < 0)
  {
    globals.temp[0] = 0;
  }
  if (globals.temp[0] > 12)
  {
    globals.temp[0] = 12;
  }
  u8g2.drawDisc(106, 42, globals.temp[0], U8G2_DRAW_LOWER_LEFT);

  globals.temp[1] = eqBands.bandValues[1] / AMPLITUDE;
  globals.temp[1] -= 7;
  if (globals.temp[1] < 0)
  {
    globals.temp[1] = 0;
  }
  if (globals.temp[1] > 12)
  {
    globals.temp[1] = 12;
  }
  u8g2.drawDisc(106, 42, globals.temp[1], U8G2_DRAW_UPPER_RIGHT);
}

void drawEQ()
{
  u8g2.setDrawColor(1);
  patternSettings.pos = 16;
  int min = 0;
  int max = 80;

  for (int i = 0; i < NUM_BANDS; i++)
  {
    globals.temp[i] = eqBands.bandValues[i] / AMPLITUDE;
    globals.temp[i] -= 7;
    if (globals.temp[i] < min)
    {
      globals.temp[i] = min;
    }
    if (globals.temp[i] > max)
    {
      globals.temp[i] = max;
    }

    u8g2.drawBox(0, patternSettings.pos + (8 * i), globals.temp[i], 7);
    globals.temp[i] = eqBands.peak[i] / AMPLITUDE;
    u8g2.drawBox(globals.temp[i], patternSettings.pos, 1, 7);
  }
}

void drawCircleEQ()
{
  globals.temp[0] = eqBands.bandValues[2] / AMPLITUDE;
  globals.temp[0] -= 7;
  if (globals.temp[0] < 5)
  {
    globals.temp[0] = 5;
  }
  if (globals.temp[0] > 20)
  {
    globals.temp[0] = 20;
  }
  u8g2.drawCircle(106, 42, globals.temp[0], U8G2_DRAW_ALL);
}

void drawIPAddress()
{
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(20, 30);

  if (WiFi.status() == WL_CONNECTED)
  {
    //Convert WiFi.localIP() from 4 bytes to 1 nice pretty string
    globals.ipAddress = String() + WiFi.localIP()[0] + "." + WiFi.localIP()[1] + "." + WiFi.localIP()[2] + "." + WiFi.localIP()[3];
    globals.ipAddress = WiFi.localIP().toString();
    u8g2.print(globals.ipAddress);

    u8g2.setCursor(64, 50);
    //u8g2.print("Connected");

    if (globalTime.currentHour != 100) //Default setting is 100, so we know time is set
    {
      //Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
      u8g2.print(globalTime.currentHour);
      u8g2.print(":");
      if (globalTime.currentMinute < 10)
      {
        u8g2.print("0");
      }
      u8g2.print(globalTime.currentMinute);
    }
    else //If time is not set yet have some fun
    {
      u8g2.print("4:20");
      globalTime.currentPM = 1;
    }

    if (globalTime.currentPM == 1)
    {
      u8g2.print(" p");
    }
    else
    {
      u8g2.print(" a");
    }
  }
  else
  {
    u8g2.print("Not Connected");
  }
}

void gravityWell()
{
  for (int i = 0; i < MAX_STARS; i++)
  {
    if (ball.xx[i] > -7)
    {
      ball.xx[i] -= 1;
    }

    ball.y[i] += ball.yy[i];
    ball.x[i] += ball.xx[i];

    if (ball.x[i] < 0)
    {
      if (ball.xx[i] == -1)
      {
        ball.xx[i] = 1;
      }
      else
      {
        ball.xx[i] = abs(ball.xx[i]) - 1;
      }
      ball.x[i] = 0;
    }

    if (ball.x[i] < 0)
    {
      ball.xx[i] = abs(ball.xx[i]);
    }

    if (((ball.y[i] > VISUALIZER_Y) || (ball.y[i] < 0)) || ((ball.yy[i] == 0) && (ball.x[i] <= 0)))
    {
      ball.y[i] = VISUALIZER_Y / 2;
      ball.x[i] = 0;
      ball.yy[i] = random(-4, 4);
      ball.xx[i] = random(4, 10);
      ball.z[i] = random(1, 5);
    }

    u8g2.drawDisc(ball.y[i], (VISUALIZER_X - ball.x[i]) + (14 - ball.z[i]), ball.z[i], U8G2_DRAW_ALL);
  }
}

void movingTriangles()
{
  //Calculate Points on a Circle
  //point is in Radians, range is 0 - 2pi (1pi = 180*)
  t1.x1 = t1.x + (t1.radius * sin(t1.point1)) + .5;
  t1.y1 = t1.y + (t1.radius * cos(t1.point1)) + .5;

  t1.x2 = t1.x + (t1.radius * sin(t1.point2)) + .5;
  t1.y2 = t1.y + (t1.radius * cos(t1.point2)) + .5;

  t1.x3 = t1.x + (t1.radius * sin(t1.point3)) + .5;
  t1.y3 = t1.y + (t1.radius * cos(t1.point3)) + .5;

  //Triangle
  //u8g2.drawTriangle(t1.x1,t1.y1, t1.x2,t1.y2, t1.x3,t1.y3);

  //Dots
  //u8g2.drawDisc(t1.x1, t1.y1, 2, U8G2_DRAW_ALL);
  //u8g2.drawDisc(t1.x2, t1.y2, 2, U8G2_DRAW_ALL);
  //u8g2.drawDisc(t1.x3, t1.y3, 2, U8G2_DRAW_ALL);

  //Circle
  u8g2.drawCircle(t1.x, t1.y, t1.radius, U8G2_DRAW_ALL);

  //Lines
  u8g2.drawLine(t1.x1, t1.y1, t1.x2, t1.y2);
  u8g2.drawLine(t1.x2, t1.y2, t1.x3, t1.y3);
  u8g2.drawLine(t1.x3, t1.y3, t1.x1, t1.y1);

  //Increase rad of each point a little
  t1.point1 -= 0.02;
  t1.point2 -= 0.02;
  t1.point3 -= 0.02;

  if (t1.point1 > 6.28)
  {
    t1.point1 -= 6.28;
  }
  if (t1.point2 > 6.28)
  {
    t1.point2 -= 6.28;
  }
  if (t1.point3 > 6.28)
  {
    t1.point3 -= 6.28;
  }

  if (t1.point1 < 0)
  {
    t1.point1 += 6.28;
  }
  if (t1.point2 < 0)
  {
    t1.point2 += 6.28;
  }
  if (t1.point3 < 0)
  {
    t1.point3 += 6.28;
  }
}

void movingCircles()
{
  for (int i = 0; i < 8; i++)
  {
    ball.y[i] += ball.z[i];
    if (ball.y[i] > VISUALIZER_Y)
    {
      ball.y[i] = 0;
      ball.x[i] = random(0, VISUALIZER_X);
      ball.yy[i] = random(1, 4);
    }
    u8g2.drawDisc(ball.y[i], ball.x[i] + 18, 2, U8G2_DRAW_ALL);
  }
}

void dvdBounce()
{
  objectBounce(&bounceModel1, DVD_WIDTH, DVD_HEIGHT, DVD);
}

void starBounce()
{
  objectBounce(&bounceModel1, STAR_WIDTH, STAR_HEIGHT, STAR_SHAPE);
  objectBounce(&bounceModel2, STAR_WIDTH, STAR_HEIGHT, STAR_SHAPE);
  objectBounce(&bounceModel3, STAR_WIDTH, STAR_HEIGHT, STAR_SHAPE);
  objectBounce(&bounceModel4, STAR_WIDTH, STAR_HEIGHT, STAR_SHAPE);
  objectBounce(&bounceModel5, STAR_WIDTH, STAR_HEIGHT, STAR_SHAPE);
  objectBounce(&bounceModel6, STAR_WIDTH, STAR_HEIGHT, STAR_SHAPE);
  objectBounce(&bounceModel7, STAR_WIDTH, STAR_HEIGHT, STAR_SHAPE);
  objectBounce(&bounceModel8, STAR_WIDTH, STAR_HEIGHT, STAR_SHAPE);
  objectBounce(&bounceModel9, STAR_WIDTH, STAR_HEIGHT, STAR_SHAPE);
  objectBounce(&bounceModel10, STAR_WIDTH, STAR_HEIGHT, STAR_SHAPE);
}

void lavaLamp(int Scale, byte Threshold, int OffsetX, int OffsetY, int OffsetZ)
{
  u8g2.setDrawColor(2);

  for (int y = 0; y <= SCREEN_HEIGHT; y++)
  {
    for (int x = 0; x <= SCREEN_WIDTH; x++)
    {
      //uint8_t 	inoise8 (uint16_t x, uint16_t y, uint16_t z)
      if (inoise8((x * Scale) + OffsetX, (y * Scale) + OffsetY, OffsetZ) > Threshold)
      {
        u8g2.drawPixel(x, y);
      }
    }
  }
}

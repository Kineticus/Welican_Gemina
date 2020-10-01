void drawDiscEQ()
{
  globals.temp[0] = bandValues[1] / AMPLITUDE;
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
  globals.temp[0] = bandValues[0] / AMPLITUDE;
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

  globals.temp[1] = bandValues[1] / AMPLITUDE;
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
  int pos = 16;
  int min = 0;
  int max = 80;

  globals.temp[0] = bandValues[0] / AMPLITUDE;
  globals.temp[0] -= 7;
  if (globals.temp[0] < min)
  {
    globals.temp[0] = min;
  }
  if (globals.temp[0] > max)
  {
    globals.temp[0] = max;
  }
  u8g2.setDrawColor(1);
  u8g2.drawBox(0, pos, globals.temp[0], 7);
  globals.temp[2] = peak[0] / AMPLITUDE;
  u8g2.drawBox(globals.temp[2], pos, 1, 7);

  globals.temp[1] = bandValues[1] / AMPLITUDE;
  globals.temp[1] -= 7;
  if (globals.temp[1] < min)
  {
    globals.temp[1] = min;
  }
  if (globals.temp[1] > max)
  {
    globals.temp[1] = max;
  }
  u8g2.drawBox(0, pos + 8, globals.temp[1], 7);
  globals.temp[2] = peak[1] / AMPLITUDE;
  u8g2.drawBox(globals.temp[2], pos + 8, 1, 7);

  globals.temp[2] = bandValues[3] / AMPLITUDE;
  globals.temp[2] -= 7;
  if (globals.temp[2] < min)
  {
    globals.temp[2] = min;
  }
  if (globals.temp[2] > max)
  {
    globals.temp[2] = max;
  }
  u8g2.drawBox(0, pos + 16, globals.temp[2], 7);
  globals.temp[2] = peak[3] / AMPLITUDE;
  u8g2.drawBox(globals.temp[2], pos + 16, 1, 7);

  globals.temp[2] = bandValues[4] / AMPLITUDE;
  globals.temp[2] -= 7;
  if (globals.temp[2] < min)
  {
    globals.temp[2] = min;
  }
  if (globals.temp[2] > max)
  {
    globals.temp[2] = max;
  }
  u8g2.drawBox(0, pos + 24, globals.temp[2], 7);

  globals.temp[2] = peak[4] / AMPLITUDE;
  u8g2.drawBox(globals.temp[2], pos + 24, 1, 7);

  globals.temp[2] = bandValues[5] / AMPLITUDE;
  globals.temp[2] -= 7;
  if (globals.temp[2] < min)
  {
    globals.temp[2] = min;
  }
  if (globals.temp[2] > max)
  {
    globals.temp[2] = max;
  }
  u8g2.drawBox(0, pos + 32, globals.temp[2], 7);
  globals.temp[2] = peak[5] / AMPLITUDE;
  u8g2.drawBox(globals.temp[2], pos + 32, 1, 7);

  globals.temp[2] = bandValues[6] / AMPLITUDE;
  globals.temp[2] -= 7;
  if (globals.temp[2] < min)
  {
    globals.temp[2] = min;
  }
  if (globals.temp[2] > max)
  {
    globals.temp[2] = max;
  }
  u8g2.drawBox(0, pos + 40, globals.temp[2], 7);
  globals.temp[2] = peak[6] / AMPLITUDE;
  u8g2.drawBox(globals.temp[2], pos + 40, 1, 7);
}

void drawCircleEQ()
{
  globals.temp[0] = bandValues[2] / AMPLITUDE;
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
    String LocalIP = String() + WiFi.localIP()[0] + "." + WiFi.localIP()[1] + "." + WiFi.localIP()[2] + "." + WiFi.localIP()[3];
    u8g2.print(LocalIP);

    u8g2.setCursor(10, 50);
    u8g2.print(weather.currentWeatherDescription);

    // switch(globalTime.currentDay)
    // {
    //   case 0:
    //     u8g2.print("Sunday");
    //     break;
    //   case 1:
    //     u8g2.print("Monday");
    //     break;
    //   case 2:
    //     u8g2.print("Tuesday");
    //     break;
    //   case 3:
    //     u8g2.print("Wednesday");
    //     break;
    //   case 4:
    //     u8g2.print("Thursday");
    //     break;
    //   case 5:
    //     u8g2.print("Friday");
    //     break;
    //   case 6:
    //     u8g2.print("Saturday");
    //     break;
    // }

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
    if (star.xx[i] > -7)
    {
      star.xx[i] -= 1;
    }

    star.y[i] += star.yy[i];
    star.x[i] += star.xx[i];

    if (star.x[i] < 0)
    {
      if (star.xx[i] == -1)
      {
        star.xx[i] = 1;
      }
      else
      {
        star.xx[i] = abs(star.xx[i]) - 1;
      }
      star.x[i] = 0;
    }

    if (star.x[i] < 0)
    {
      star.xx[i] = abs(star.xx[i]);
    }

    if (((star.y[i] > VISUALIZER_Y) || (star.y[i] < 0)) || ((star.yy[i] == 0) && (star.x[i] <= 0))) // || (star.x[i] > VISUALIZER_X) || (star.x[i] < 0)
    {
      //star.y[i] = random(0, VISUALIZER_Y);
      //star.x[i] = random(0, VISUALIZER_X);
      star.y[i] = VISUALIZER_Y / 2;
      star.x[i] = 0;
      star.yy[i] = random(-4, 4);
      star.xx[i] = random(4, 10);
      star.z[i] = random(1, 5);
    }

    u8g2.drawDisc(star.y[i], (VISUALIZER_X - star.x[i]) + (14 - star.z[i]), star.z[i], U8G2_DRAW_ALL);
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
    star.y[i] += star.z[i];
    if (star.y[i] > VISUALIZER_Y)
    {
      star.y[i] = 0;
      star.x[i] = random(0, VISUALIZER_X);
      star.yy[i] = random(1, 4);
    }
    u8g2.drawDisc(star.y[i], star.x[i] + 18, 2, U8G2_DRAW_ALL);
  }
}

void dvdBounce()
{
  dvdBounce_y += dvdBounce_vy;
  dvdBounce_x += dvdBounce_vx;

  if (dvdBounce_y <= 0)
  {
    dvdBounce_vy = 1;
  }
  if (dvdBounce_y >= (VISUALIZER_Y - DVD_width))
  {
    dvdBounce_vy = -1;
  }

  if (dvdBounce_x <= 0)
  {
    dvdBounce_vx = 1;
  }
  if (dvdBounce_x >= (VISUALIZER_X - DVD_height))
  {
    dvdBounce_vx = -1;
  }

  //u8g2.drawDisc(dvdBounce_y, dvdBounce_x + 18, 2, U8G2_DRAW_ALL);
  u8g2.drawXBMP(dvdBounce_y, dvdBounce_x + 16, DVD_width, DVD_height, DVD);
}

void starBounce()
{
  dvdBounce_y += dvdBounce_vy;
  dvdBounce_x += dvdBounce_vx;

  if (dvdBounce_y <= 0)
  {
    dvdBounce_vy = 1;
  }
  if (dvdBounce_y >= (VISUALIZER_Y - STAR_WIDTH))
  {
    dvdBounce_vy = -1;
  }

  if (dvdBounce_x <= 0)
  {
    dvdBounce_vx = 1;
  }
  if (dvdBounce_x >= (VISUALIZER_X - STAR_HEIGHT))
  {
    dvdBounce_vx = -1;
  }

  dvdBounce2_y += dvdBounce2_vy;
  dvdBounce2_x += dvdBounce2_vx;

  if (dvdBounce2_y <= 0)
  {
    dvdBounce2_vy = 1;
  }
  if (dvdBounce2_y >= (VISUALIZER_Y - STAR_WIDTH))
  {
    dvdBounce2_vy = -1;
  }

  if (dvdBounce2_x <= 0)
  {
    dvdBounce2_vx = 1;
  }
  if (dvdBounce2_x >= (VISUALIZER_X - STAR_HEIGHT))
  {
    dvdBounce2_vx = -1;
  }

  dvdBounce3_y += dvdBounce3_vy;
  dvdBounce3_x += dvdBounce3_vx;

  if (dvdBounce3_y <= 0)
  {
    dvdBounce3_vy = 1;
  }
  if (dvdBounce3_y >= (VISUALIZER_Y - STAR_WIDTH))
  {
    dvdBounce3_vy = -1;
  }

  if (dvdBounce3_x <= 0)
  {
    dvdBounce3_vx = 1;
  }
  if (dvdBounce3_x >= (VISUALIZER_X - STAR_HEIGHT))
  {
    dvdBounce3_vx = -1;
  }

  u8g2.drawXBMP(dvdBounce_y, dvdBounce_x + 16, STAR_WIDTH, STAR_HEIGHT, starshape);
  u8g2.drawXBMP(dvdBounce2_y, dvdBounce2_x + 16, STAR_WIDTH, STAR_HEIGHT, starshape);
  u8g2.drawXBMP(dvdBounce3_y, dvdBounce3_x + 16, STAR_WIDTH, STAR_HEIGHT, starshape);
}

void drawDiscEQ()
{
  temp1 = bandValues[1] / AMPLITUDE;
  temp1 -= 7;
  if (temp1 < 2)
  {
    temp1 = 2;
  }
  if (temp1 > 20)
  {
    temp1 = 20;
  }
  u8g2.drawDisc(106, 22, temp1, U8G2_DRAW_ALL);
}

void drawDiscSectionsEQ()
{
  temp1 = bandValues[0] / AMPLITUDE;
  temp1 -= 7;
  if (temp1 < 0)
  {
    temp1 = 0;
  }
  if (temp1 > 12)
  {
    temp1 = 12;
  }
  u8g2.drawDisc(106, 42, temp1, U8G2_DRAW_LOWER_LEFT);

  temp2 = bandValues[1] / AMPLITUDE;
  temp2 -= 7;
  if (temp2 < 0)
  {
    temp2 = 0;
  }
  if (temp2 > 12)
  {
    temp2 = 12;
  }
  u8g2.drawDisc(106, 42, temp2, U8G2_DRAW_UPPER_RIGHT);
}

void drawEQ()
{
  int pos = 16;
  int min = 0;
  int max = 80;

  temp1 = bandValues[0] / AMPLITUDE;
  temp1 -= 7;
  if (temp1 < min)
  {
    temp1 = min;
  }
  if (temp1 > max)
  {
    temp1 = max;
  }
  u8g2.setDrawColor(1);
  u8g2.drawBox(0, pos, temp1, 7);
  temp3 = peak[0] / AMPLITUDE;
  u8g2.drawBox(temp3, pos, 1, 7);

  temp2 = bandValues[1] / AMPLITUDE;
  temp2 -= 7;
  if (temp2 < min)
  {
    temp2 = min;
  }
  if (temp2 > max)
  {
    temp2 = max;
  }
  u8g2.drawBox(0, pos + 8, temp2, 7);
  temp3 = peak[1] / AMPLITUDE;
  u8g2.drawBox(temp3, pos + 8, 1, 7);

  temp3 = bandValues[3] / AMPLITUDE;
  temp3 -= 7;
  if (temp3 < min)
  {
    temp3 = min;
  }
  if (temp3 > max)
  {
    temp3 = max;
  }
  u8g2.drawBox(0, pos + 16, temp3, 7);
  temp3 = peak[3] / AMPLITUDE;
  u8g2.drawBox(temp3, pos + 16, 1, 7);

  temp3 = bandValues[4] / AMPLITUDE;
  temp3 -= 7;
  if (temp3 < min)
  {
    temp3 = min;
  }
  if (temp3 > max)
  {
    temp3 = max;
  }
  u8g2.drawBox(0, pos + 24, temp3, 7);

  temp3 = peak[4] / AMPLITUDE;
  u8g2.drawBox(temp3, pos + 24, 1, 7);

  temp3 = bandValues[5] / AMPLITUDE;
  temp3 -= 7;
  if (temp3 < min)
  {
    temp3 = min;
  }
  if (temp3 > max)
  {
    temp3 = max;
  }
  u8g2.drawBox(0, pos + 32, temp3, 7);
  temp3 = peak[5] / AMPLITUDE;
  u8g2.drawBox(temp3, pos + 32, 1, 7);

  temp3 = bandValues[6] / AMPLITUDE;
  temp3 -= 7;
  if (temp3 < min)
  {
    temp3 = min;
  }
  if (temp3 > max)
  {
    temp3 = max;
  }
  u8g2.drawBox(0, pos + 40, temp3, 7);
  temp3 = peak[6] / AMPLITUDE;
  u8g2.drawBox(temp3, pos + 40, 1, 7);
}

void drawCircleEQ()
{
  temp1 = bandValues[2] / AMPLITUDE;
  temp1 -= 7;
  if (temp1 < 5)
  {
    temp1 = 5;
  }
  if (temp1 > 20)
  {
    temp1 = 20;
  }
  u8g2.drawCircle(106, 42, temp1, U8G2_DRAW_ALL);
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
  for (int i = 0; i < maxStars; i++)
  {
    if (star_xx[i] > -7)
    {
      star_xx[i] -= 1;
    }

    star_y[i] += star_yy[i];
    star_x[i] += star_xx[i];

    if (star_x[i] < 0)
    {
      if (star_xx[i] == -1)
      {
        star_xx[i] = 1;
      }
      else
      {
        star_xx[i] = abs(star_xx[i]) - 1;
      }
      star_x[i] = 0;
    }

    if (star_x[i] < 0)
    {
      star_xx[i] = abs(star_xx[i]);
    }

    if (((star_y[i] > visualizer_y) || (star_y[i] < 0)) || ((star_yy[i] == 0) && (star_x[i] <= 0))) // || (star_x[i] > visualizer_x) || (star_x[i] < 0)
    {
      //star_y[i] = random(0, visualizer_y);
      //star_x[i] = random(0, visualizer_x);
      star_y[i] = visualizer_y / 2;
      star_x[i] = 0;
      star_yy[i] = random(-4, 4);
      star_xx[i] = random(4, 10);
      star_z[i] = random(1, 5);
    }

    u8g2.drawDisc(star_y[i], (visualizer_x - star_x[i]) + (14 - star_z[i]), star_z[i], U8G2_DRAW_ALL);
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
    star_y[i] += star_z[i];
    if (star_y[i] > visualizer_y)
    {
      star_y[i] = 0;
      star_x[i] = random(0, visualizer_x);
      star_yy[i] = random(1, 4);
    }
    u8g2.drawDisc(star_y[i], star_x[i] + 18, 2, U8G2_DRAW_ALL);
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
  if (dvdBounce_y >= (visualizer_y - DVD_width))
  {
    dvdBounce_vy = -1;
  }

  if (dvdBounce_x <= 0)
  {
    dvdBounce_vx = 1;
  }
  if (dvdBounce_x >= (visualizer_x - DVD_height))
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
  if (dvdBounce_y >= (visualizer_y - star_width))
  {
    dvdBounce_vy = -1;
  }

  if (dvdBounce_x <= 0)
  {
    dvdBounce_vx = 1;
  }
  if (dvdBounce_x >= (visualizer_x - star_height))
  {
    dvdBounce_vx = -1;
  }

  dvdBounce2_y += dvdBounce2_vy;
  dvdBounce2_x += dvdBounce2_vx;

  if (dvdBounce2_y <= 0)
  {
    dvdBounce2_vy = 1;
  }
  if (dvdBounce2_y >= (visualizer_y - star_width))
  {
    dvdBounce2_vy = -1;
  }

  if (dvdBounce2_x <= 0)
  {
    dvdBounce2_vx = 1;
  }
  if (dvdBounce2_x >= (visualizer_x - star_height))
  {
    dvdBounce2_vx = -1;
  }

  dvdBounce3_y += dvdBounce3_vy;
  dvdBounce3_x += dvdBounce3_vx;

  if (dvdBounce3_y <= 0)
  {
    dvdBounce3_vy = 1;
  }
  if (dvdBounce3_y >= (visualizer_y - star_width))
  {
    dvdBounce3_vy = -1;
  }

  if (dvdBounce3_x <= 0)
  {
    dvdBounce3_vx = 1;
  }
  if (dvdBounce3_x >= (visualizer_x - star_height))
  {
    dvdBounce3_vx = -1;
  }

  u8g2.drawXBMP(dvdBounce_y, dvdBounce_x + 16, star_width, star_height, star);
  u8g2.drawXBMP(dvdBounce2_y, dvdBounce2_x + 16, star_width, star_height, star);
  u8g2.drawXBMP(dvdBounce3_y, dvdBounce3_x + 16, star_width, star_height, star);
}

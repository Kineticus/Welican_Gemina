void drawDiscEQ() {
  int temp1 = MSGEQ7.get(1)/64;
  temp1 -= 7;
  if (temp1 < 2){
    temp1 = 2;
  }
  if (temp1 > 20){
    temp1 = 20;
  }
  u8g2.drawDisc(106, 22, temp1, U8G2_DRAW_ALL);
}

void drawDiscSectionsEQ() {
  int temp1 = MSGEQ7.get(1)/64;
  temp1 -= 7;
  if (temp1 < 0){
    temp1 = 0;
  }
  if (temp1 > 12){
    temp1 = 12;
  }
  u8g2.drawDisc(106, 42, temp1, U8G2_DRAW_LOWER_LEFT);

  int temp2 = MSGEQ7.get(4)/64;
  temp2 -= 7;
  if (temp2 < 0){
    temp2 = 0;
  }
  if (temp2 > 12){
    temp2 = 12;
  }
  u8g2.drawDisc(106, 42, temp2, U8G2_DRAW_UPPER_RIGHT);
}

void drawEQ() {
  int pos = 32;
  int min = 0;
  int max = 80;

  int temp1 = MSGEQ7.get(0)/32;
  temp1 -= 7;
  if (temp1 < min){
    temp1 = min;
  }
  if (temp1 > max){
    temp1 = max;
  }
  u8g2.setDrawColor(1);
  u8g2.drawBox(0,pos,temp1,7);

  int temp2 = MSGEQ7.get(3)/32;
  temp2 -= 7;
  if (temp2 < min){
    temp2 = min;
  }
  if (temp2 > max){
    temp2 = max;
  }
  u8g2.drawBox(0,pos+8,temp2,7);

  int temp3 = MSGEQ7.get(5)/32;
  temp3 -= 7;
  if (temp3 < min){
    temp3 = min;
  }
  if (temp3 > max){
    temp3 = max;
  }
  u8g2.drawBox(0,pos+16,temp3,7);
}

void drawCircleEQ() {
  int temp1 = MSGEQ7.get(2)/64;
  temp1 -= 7;
  if (temp1 < 5){
    temp1 = 5;
  }
  if (temp1 > 20){
    temp1 = 20;
  }
  u8g2.drawCircle(106, 42, temp1, U8G2_DRAW_ALL);
}

void gravityWell() {
  for (int i = 0; i < maxStars; i ++)
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
      } else
      {
        star_xx[i] = abs(star_xx[i]) -1;
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


    u8g2.drawDisc(star_y[i], (visualizer_x - star_x[i]) + (14 - star_z[i] ), star_z[i], U8G2_DRAW_ALL);
  }
}

void movingCircles() {
  for (int i = 0; i < 8; i ++)
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

void dvdBounce() {
  dvdBounce_y += dvdBounce_vy;
  dvdBounce_x += dvdBounce_vx;

  if (dvdBounce_y <= 0) {
    dvdBounce_vy = 1;
  }
  if (dvdBounce_y >= (visualizer_y - DVD_width)) {
    dvdBounce_vy = -1;
  }

  if (dvdBounce_x <= 0) {
    dvdBounce_vx = 1;
  }
  if (dvdBounce_x >= (visualizer_x - DVD_height)) {
    dvdBounce_vx = -1;
  }

  //u8g2.drawDisc(dvdBounce_y, dvdBounce_x + 18, 2, U8G2_DRAW_ALL);
  u8g2.drawXBMP(dvdBounce_y,dvdBounce_x + 16,DVD_width, DVD_height,DVD);
}

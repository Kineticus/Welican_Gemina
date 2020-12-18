
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

  u8g2.drawXBMP(item1->y, item1->x + 18,
                objectWidth, objectHeight, object);
}

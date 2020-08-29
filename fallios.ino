void fallios()
{
    if ((playerX > 128) || (playerX < 0))
    {
        playerX = 64;
        gameMode = 0;
    }

    u8g2.drawDisc(playerX, playerY, 2, U8G2_DRAW_ALL);

}

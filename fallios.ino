void fallios()
{ 
    u8g2.setCursor(0, screen_height);
    u8g2.print(fallios_score);

    u8g2.setCursor(screen_width - 30, screen_height);
    u8g2.print(fallios_score_top);

    for (int i = 1; i < screen_height + 1; i++)
    {
        tunnel_1[i-1] = tunnel_1[i];
        tunnel_2[i-1] = tunnel_2[i];

        u8g2.drawPixel(tunnel_1[i-1], i-1);
        u8g2.drawPixel(tunnel_2[i-1], i-1);
    }

    u8g2.drawDisc(playerX, playerY, 2, U8G2_DRAW_ALL);

    yoffset += .00420;
    motion = SimplexNoise(xoffset,yoffset,0) * 420;

    if (motion > motionHistory)
    {
        tunnel_1[screen_height] += 1;
    }
    if (motion < motionHistory)
    {
        tunnel_1[screen_height] -= 1;
    }

    if (tunnel_1[screen_height] <= 0)
    {
        tunnel_1[screen_height] = 0;
    }
    
    if ((tunnel_1[screen_height] + tunnelWidth) > screen_width)
    {
        tunnel_1[screen_height] = screen_width - tunnelWidth;
    }

    tunnel_2[screen_height] = tunnel_1[screen_height] + tunnelWidth;  


    motionHistory = motion;

    if ((playerX > tunnel_2[8] - 3) || (playerX < tunnel_1[8] + 3))
    {
        u8g2.setCursor(4, screen_height / 2);
        u8g2.print("G A M E  O V E R !!!");
        if (fallios_score > fallios_score_top)
        {
            fallios_score_top = fallios_score;
            u8g2.setCursor(8, screen_height / 3);
            u8g2.print("New High Score!!!");
            //break score into 2 bytes as EEPROM is 1 byte per space
            uint8_t xlow = fallios_score_top & 0xff;
            uint8_t xhigh = (fallios_score_top >> 8);

            EEPROM.write(20, xlow);
            EEPROM.write(21, xhigh);
            EEPROM.commit();
        }
        u8g2.sendBuffer();
        delay(5000);
        fallios_reset();
        gameMode = 0;
    }
    fallios_score += 1;
}

void fallios_reset()
{
    fallios_score = 0;
    playerX = 64;
    playerY = 8;
    motion = 0;
    motionHistory = 0;
    tunnelWidth = screen_width / 2;

    for (int i = 0; i < screen_height + 1; i++)
    {
        tunnel_1[i] = screen_width / 4;
        tunnel_2[i] = (screen_width / 4) + tunnelWidth;
    }
}

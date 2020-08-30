void fallios()
{ 
    //Display current score
    u8g2.setCursor(0, screen_height);
    u8g2.print(fallios_score);

    //Display high score
    u8g2.setCursor(screen_width - 30, screen_height);
    u8g2.print(fallios_score_top);

    //Build barriers, repeating once for each row of screen height
    for (int i = 1; i < screen_height + 1; i++)
    {
        //Shift array value down one
        tunnel_1[i-1] = tunnel_1[i];
        tunnel_2[i-1] = tunnel_2[i];

        //draw pixel at array value
        u8g2.drawPixel(tunnel_1[i-1], i-1);
        u8g2.drawPixel(tunnel_2[i-1], i-1);
    }

    //Draw the plauer
    u8g2.drawDisc(playerX, playerY, 2, U8G2_DRAW_ALL);

    //increment simplex noise for tunnel generatioj
    tunnelGenerator += .015;
    motion = SimplexNoise(tunnelGenerator,yoffset,0) * 420;

    //Has simplex noise has gone up since last time? move tunnel right
    if (motion > motionHistory)
    {
        tunnel_1[screen_height] += 1;
    }

    //Has simplex noise has gone down since last time? move tunnel left
    if (motion < motionHistory)
    {
        tunnel_1[screen_height] -= 1;
    }

    //Lower boundry check, can't go off screen to left
    if (tunnel_1[screen_height] <= 0)
    {
        tunnel_1[screen_height] = 0;
    }
    
    //Upper boundry check, can't go off screen to left, including current tunnel width
    if ((tunnel_1[screen_height] + tunnelWidth) > screen_width)
    {
        tunnel_1[screen_height] = screen_width - tunnelWidth;
    }

    //Calculate right wall boundry based on current width
    tunnel_2[screen_height] = tunnel_1[screen_height] + tunnelWidth;  

    //Store the current simplex noise point to compare next loop
    motionHistory = motion;

    //Collision detection, needs padding as player object is more than 1 pixel wide
    if ((playerX > tunnel_2[playerY] - 3) || (playerX < tunnel_1[playerY] + 3))
    {
        //Place the cursor and draw some game over message
        u8g2.setCursor(8, screen_height / 1.5);
        u8g2.print("G A M E  O V E R !!!");

        //Did we beat the top score?
        if (fallios_score > fallios_score_top)
        {
            //Update top score to new high score
            fallios_score_top = fallios_score;

            //Place the cursor and draw a high score message
            u8g2.setCursor(12, screen_height / 2);
            u8g2.print("New High Score !!!");

            //Break score into 2 bytes as EEPROM is 1 byte per space. Score is a (16 bit) unsigned integer
            uint8_t xlow = fallios_score_top & 0xff;
            uint8_t xhigh = (fallios_score_top >> 8);

            //Save the 16 bit unsigned integer into two bytes of EEPROM
            EEPROM.write(20, xlow);
            EEPROM.write(21, xhigh);

            //Commit to memory
            EEPROM.commit();
        }

        //Update the screen as we are about to delay and main loop contains screen update
        u8g2.sendBuffer();

        //Wait 5 seconds to see how you died and the score
        delay(5000);

        //Sync encoders, restore original pattern/brightness,end game mode
        endGameMode();
    }

    //We didn't collide? Add a point to the board
    fallios_score += 1;
}

void fallios_reset()
{
    //Current score is back to 0
    fallios_score = 0;

    //Player to the middle of the screen
    playerX = screen_width /2;

    //And not far from the top
    playerY = 8;

    //No motion here
    motion = 0;
    motionHistory = 0;

    //Wide tunnel width
    tunnelWidth = screen_width / 2;

    //Reset wall arrays into centered straight lines using current width
    for (int i = 0; i < screen_height + 1; i++)
    {
        tunnel_1[i] = screen_width / 4;
        tunnel_2[i] = (screen_width / 4) + tunnelWidth;
    }
}

/**************************************************************

Fallios! The greatest game ever!

Brian Schimke, 2020
**************************************************************/

void fallios_game()
{
    //Display current score
    //u8g2.setFont(u8g2_font_profont12_mf);
    //u8g2.setCursor(0, SCREEN_HEIGHT);
    //u8g2.print(fallios.score);

    //Display high score
    //u8g2.setCursor(SCREEN_WIDTH - 30, SCREEN_HEIGHT);
    //u8g2.print(fallios.scoreTop);

    if (fallios.scoreMarkerStep > 0)
    {
        fallios.scoreMarkerStep -= fallios.speed;
        fallios_scoreMarker(fallios.scoreMarkerStep, fallios.scoreMarkerSide);
    }

    if (((fallios.score + 70) % 250) == 0)
    {
        fallios.scoreMarkerStep = 80;

        //Figure out which side has more room to show the score on
        if (fallios.tunnel1[70] > (128 - fallios.tunnel2[70]))
        {   
            fallios.scoreMarkerSide = 0;
        }
        else
        {
            fallios.scoreMarkerSide = 1;
        }
    }

    for (int ii = 0; ii < fallios.speed; ii++)
    {
        //Build barriers, repeating once for each row of screen height
        for (int i = 1; i <= SCREEN_HEIGHT + 10; i++)
        {
            fallios.tunnel1[i - 1] = fallios.tunnel1[i];
            fallios.tunnel2[i - 1] = fallios.tunnel2[i];
        }

        //increment simplex noise for tunnel generation
        fallios.tunnelGenerator += .015;
        fallios.motion = SimplexNoise(fallios.tunnelGenerator, simplexNoise.yoffset, 0) * 420;

        //Has simplex noise has gone up since last time? move tunnel right
        if (fallios.motion > fallios.motionHistory)
        {
            fallios.tunnel1[SCREEN_HEIGHT + 10] += 1;
        }
        
        //Has simplex noise has gone down since last time? move tunnel left
        if (fallios.motion < fallios.motionHistory)
        {
            fallios.tunnel1[SCREEN_HEIGHT + 10] -= 1;
        }

        //Lower boundry check, can't go off screen to left
        if (fallios.tunnel1[SCREEN_HEIGHT + 10] <= 0)
        {
            fallios.tunnel1[SCREEN_HEIGHT + 10] = 0;
        }

        //Upper boundry check, can't go off screen to right, including current tunnel width
        if ((fallios.tunnel1[SCREEN_HEIGHT + 10] + fallios.tunnelWidth) > SCREEN_WIDTH)
        {
            fallios.tunnel1[SCREEN_HEIGHT + 10] = SCREEN_WIDTH - fallios.tunnelWidth;
        }

        //Calculate right wall boundry based on current width
        fallios.tunnel2[SCREEN_HEIGHT + 10] = fallios.tunnel1[SCREEN_HEIGHT + 10] + fallios.tunnelWidth;

        //Store the current simplex noise point to compare next loop
        fallios.motionHistory = fallios.motion;
    }

    //draw pixel at array value
    for (int i = 0; i <= SCREEN_HEIGHT + 1; i++)
    {
        u8g2.drawPixel(fallios.tunnel1[i], i);
        u8g2.drawPixel(fallios.tunnel2[i], i);
    }

    //Combine encoder inputs
    player.X += player.Y;
    player.Y = 0;

    //Draw the player.
    u8g2.drawDisc(player.X, fallios.Y, 2, U8G2_DRAW_ALL);

    //Collision detection, needs padding as player. object is more than 1 pixel wide
    if ((player.X > fallios.tunnel2[fallios.Y] - 3) || (player.X < fallios.tunnel1[fallios.Y] + 3))
    {
        //Place the cursor and draw some game over message
        u8g2.setFont(u8g2_font_profont12_mf);
        u8g2.setCursor(8, SCREEN_HEIGHT / 1.5);
        u8g2.print("G A M E  O V E R !!!");
        u8g2.setCursor(50, SCREEN_HEIGHT - 10);
        u8g2.print(fallios.score);

        //Did we beat the top score?
        if (fallios.score > fallios.scoreTop)
        {
            //Update top score to new high score
            fallios.scoreTop = fallios.score;

            //Place the cursor and draw a high score message
            u8g2.setCursor(12, SCREEN_HEIGHT / 2);
            u8g2.print("New High Score !!!");

            //Write Integer (4 bytes) to EEPROM
            EEPROM.put(20, fallios.scoreTop);
            
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
    fallios.score += fallios.speed;

    //for difficulty tracking
    fallios.tunnelTracker += 1;

    if (fallios.tunnelTracker > 100)
    {
        if (fallios.tunnelWidth > 20)
        {
            fallios.tunnelWidth -= 1;    
        }

        fallios.tunnelTracker = 0;
    }
}

void fallios_scoreMarker(byte scoreStep, byte scoreSide)
{
    //Draw the lines on either side of the tunnel walls
    if (scoreStep < 63 + fallios.speed)
    {
        u8g2.drawHLine(0, scoreStep - fallios.speed, fallios.tunnel1[scoreStep]);
        u8g2.drawHLine(fallios.tunnel2[scoreStep], scoreStep - fallios.speed, SCREEN_WIDTH);
    }

    //Figure out which side to show the score on
    if (scoreSide == 0)
    {
        u8g2.setCursor(0, scoreStep - 1 - fallios.speed);
    }
    else
    {
        u8g2.setCursor(110, scoreStep - 1 - fallios.speed);
    }

    //Print the score
    u8g2.setFont(u8g2_font_blipfest_07_tr);
    u8g2.print(fallios.score + scoreStep - 10);
}

void fallios_reset()
{
    //Current score is back to 0
    fallios.score = -70;

    //player. to the middle of the screen
    player.X = SCREEN_WIDTH / 2;
    player.Y = 0;

    //And not far from the top
    fallios.Y = 8;

    //No motion here
    fallios.motion = 0;
    fallios.motionHistory = 0;

    //Get rid of markers
    fallios.scoreMarkerStep = 0;
    
    //Wide tunnel width
    fallios.tunnelWidth = SCREEN_WIDTH / 2;

    //Reset wall arrays into centered straight lines using current width
    for (int i = 0; i <= SCREEN_HEIGHT + 10; i++)
    {
        fallios.tunnel1[i] = SCREEN_WIDTH / 4;
        fallios.tunnel2[i] = (SCREEN_WIDTH / 4) + fallios.tunnelWidth;
    }
}

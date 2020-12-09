/**************************************************************

Fallios! The greatest game ever!

Brian Schimke, 2020
**************************************************************/

void fallios_game()
{
    //Display current score
    u8g2.setFont(u8g2_font_profont12_mf);
    u8g2.setCursor(0, SCREEN_HEIGHT);
    u8g2.print(fallios.score);

    //Display high score
    u8g2.setCursor(SCREEN_WIDTH - 30, SCREEN_HEIGHT);
    u8g2.print(fallios.scoreTop);
    updateUserData("games/fallios/highscore", fallios.scoreTop);

    //Build barriers, repeating once for each row of screen height
    for (int i = 1; i < SCREEN_HEIGHT + 1; i++)
    {
        //Shift array value down one
        fallios.tunnel1[i - 1] = fallios.tunnel1[i];
        fallios.tunnel2[i - 1] = fallios.tunnel2[i];

        //draw pixel at array value
        u8g2.drawPixel(fallios.tunnel1[i - 1], i - 1);
        u8g2.drawPixel(fallios.tunnel2[i - 1], i - 1);
    }

    player.X += player.Y;
    player.Y = 0;

    //Draw the player.
    u8g2.drawDisc(player.X, fallios.Y, 2, U8G2_DRAW_ALL);

    //increment simplex noise for tunnel generation
    fallios.tunnelGenerator += .015;
    fallios.motion = SimplexNoise(fallios.tunnelGenerator, simplexNoise.yoffset, 0) * 420;

    //Has simplex noise has gone up since last time? move tunnel right
    if (fallios.motion > fallios.motionHistory)
    {
        fallios.tunnel1[SCREEN_HEIGHT] += 1;
    }

    //Has simplex noise has gone down since last time? move tunnel left
    if (fallios.motion < fallios.motionHistory)
    {
        fallios.tunnel1[SCREEN_HEIGHT] -= 1;
    }

    //Lower boundry check, can't go off screen to left
    if (fallios.tunnel1[SCREEN_HEIGHT] <= 0)
    {
        fallios.tunnel1[SCREEN_HEIGHT] = 0;
    }

    //Upper boundry check, can't go off screen to right, including current tunnel width
    if ((fallios.tunnel1[SCREEN_HEIGHT] + fallios.tunnelWidth) > SCREEN_WIDTH)
    {
        fallios.tunnel1[SCREEN_HEIGHT] = SCREEN_WIDTH - fallios.tunnelWidth;
    }

    //Calculate right wall boundry based on current width
    fallios.tunnel2[SCREEN_HEIGHT] = fallios.tunnel1[SCREEN_HEIGHT] + fallios.tunnelWidth;

    //Store the current simplex noise point to compare next loop
    fallios.motionHistory = fallios.motion;

    //Collision detection, needs padding as player. object is more than 1 pixel wide
    if ((player.X > fallios.tunnel2[fallios.Y] - 3) || (player.X < fallios.tunnel1[fallios.Y] + 3))
    {
        //Place the cursor and draw some game over message
        u8g2.setCursor(8, SCREEN_HEIGHT / 1.5);
        u8g2.print("G A M E  O V E R !!!");

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
    fallios.score += 1;

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

void fallios_reset()
{
    //Current score is back to 0
    fallios.score = 0;

    //player. to the middle of the screen
    player.X = SCREEN_WIDTH / 2;
    player.Y = 0;

    //And not far from the top
    fallios.Y = 8;

    //No motion here
    fallios.motion = 0;
    fallios.motionHistory = 0;

    //Wide tunnel width
    fallios.tunnelWidth = SCREEN_WIDTH / 2;

    //Reset wall arrays into centered straight lines using current width
    for (int i = 0; i < SCREEN_HEIGHT + 1; i++)
    {
        fallios.tunnel1[i] = SCREEN_WIDTH / 4;
        fallios.tunnel2[i] = (SCREEN_WIDTH / 4) + fallios.tunnelWidth;
    }
}

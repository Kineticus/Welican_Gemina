/**************************************************************

Block Breaker! The greatest game ever!

Brian Schimke, 2020
**************************************************************/

void blockbreaker()
{
    //Make sure we have the right font and color
    u8g2.setFont(u8g2_font_profont12_mf);
    u8g2.setDrawColor(1);

    //Draw the borders
    u8g2.drawVLine(0, 0, screen_height);
    u8g2.drawVLine(screen_width, 0, screen_height);
    u8g2.drawHLine(0, 0, screen_width);

    if (blockbreaker_messageTimer > 0)
    {
        switch (blockbreaker_message)
        {
        case 1:
            u8g2.setCursor(5, (screen_height / 1.5));
            u8g2.print("! N I C E  S A V E !");
            break;
        case 2:
            u8g2.setCursor((screen_width / 2) - 10, screen_height / 1.5);
            u8g2.print(":(");
            break;
        }

        blockbreaker_messageTimer = blockbreaker_messageTimer - 1;
    }

    //Add input from the other knob and clear it
    playerX += playerY;
    playerY = 0;

    //Make sure we're in range
    if (playerX < 0)
    {
        playerX = 0;
    }
    if (playerX > (screen_width - blockbreaker_paddleWidth))
    {
        playerX = screen_width - blockbreaker_paddleWidth;
    }

    //Draw the paddle
    u8g2.drawBox(playerX, screen_height - blockbreaker_paddleHeight, blockbreaker_paddleWidth, 4);

    //Draw the ball
    u8g2.drawDisc(blockbreaker_ballX, blockbreaker_ballY, 2, U8G2_DRAW_ALL);

    //Are we running the game?
    if (blockbreaker_running == 1)
    {
        //Change ball position by velocities
        blockbreaker_ballX += blockbreaker_ballXvel;
        blockbreaker_ballY += blockbreaker_ballYvel;
    }
    else
    {
        u8g2.setCursor(screen_width / 7, (screen_height / 1.3));
        u8g2.print("! C L I C K !");

        //A we waiting for a click to start?
        if ((knob1.click == 1) || (knob2.click == 1))
        {
            blockbreaker_running = 1;
        }
    }

    //Did we hit the wall left wall?
    if (blockbreaker_ballX <= (blockbreaker_ballWidth / 2))
    {
        blockbreaker_ballXvel = 1;
    }

    //Did we hit the right wall?
    if (blockbreaker_ballX >= (screen_width - (blockbreaker_ballWidth / 2)))
    {
        blockbreaker_ballXvel = -1;
    }

    //Did we hit the ceiling?
    if ((blockbreaker_ballY - (blockbreaker_ballWidth / 2)) <= 0)
    {
        blockbreaker_ballYvel = 1;
    }

    //Did we hit the paddle height?
    if (blockbreaker_ballY == (screen_height - blockbreaker_paddleHeight - (blockbreaker_ballWidth / 2)))
    {
        if (((blockbreaker_ballX + (blockbreaker_ballWidth / 2)) < playerX) || (blockbreaker_ballX > (playerX + blockbreaker_paddleWidth + (blockbreaker_ballWidth / 2))))
        {
        }
        else if (blockbreaker_ballYvel > 0)
        {
            blockbreaker_ballYvel = -1; //Hit the paddle! Bounce the ball
            blockbreaker_score++;
        }
    }

    //2nd Chance - Did we hit the paddle height?
    if (blockbreaker_ballY == (screen_height - blockbreaker_paddleHeight - (blockbreaker_ballWidth / 2) + 2))
    {
        if (((blockbreaker_ballX + (blockbreaker_ballWidth / 2)) < playerX) || (blockbreaker_ballX > (playerX + blockbreaker_paddleWidth + (blockbreaker_ballWidth / 2))))
        {
            //This is game over condition area
            blockbreaker_message = 2;
            blockbreaker_messageTimer = 24;
        }
        else
        {
            blockbreaker_ballYvel = -1; //Hit the paddle! Bounce the ball
            blockbreaker_message = 1;
            blockbreaker_messageTimer = 24;
            blockbreaker_score++;
        }
    }

    if ((blockbreaker_ballY - 10) > screen_height)
    {
        //Place the cursor and draw some game over message
        u8g2.setCursor(4, screen_height / 3);
        u8g2.print("G A M E  O V E R !!!");

        //Draw the score?
        u8g2.setCursor(35, (screen_height / 1.5));
        u8g2.print("Score: ");
        u8g2.setCursor(75, (screen_height / 1.5));
        u8g2.print(blockbreaker_score);

        //Send display out
        u8g2.sendBuffer();
        delay(5000);
        endGameMode();
    }
}

void blockbreaker_reset()
{
    //Current score is back to 0
    blockbreaker_score = 0;

    blockbreaker_message = 0;
    blockbreaker_messageTimer = 0;

    blockbreaker_ballY = screen_height / 2;
    blockbreaker_ballX = screen_width / 2;
    blockbreaker_ballXvel = -1;
    blockbreaker_ballYvel = 1;

    //Player to the middle of the screen
    playerX = screen_width / 2;
    playerY = 0;

    //And at the bottom
    blockbreaker_paddleHeight = 2;
}

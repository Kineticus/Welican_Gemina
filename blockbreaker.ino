/**************************************************************

Block Breaker! The greatest game ever!

Brian Schimke, 2020
**************************************************************/

void blockbreaker_game()
{
    //Make sure we have the right font and color
    u8g2.setFont(u8g2_font_profont12_mf);
    u8g2.setDrawColor(1);

    //Draw the borders
    u8g2.drawVLine(0, 0, screen_height);
    u8g2.drawVLine(screen_width, 0, screen_height);
    u8g2.drawHLine(0, 0, screen_width);

    if (blockBreaker.messageTimer > 0)
    {
        switch (blockBreaker.message)
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

        blockBreaker.messageTimer = blockBreaker.messageTimer - 1;
    }

    //Add input from the other knob and clear it
    playerX += playerY;
    playerY = 0;

    //Make sure we're in range
    if (playerX < 0)
    {
        playerX = 0;
    }
    if (playerX > (screen_width - blockBreaker.paddleWidth))
    {
        playerX = screen_width - blockBreaker.paddleWidth;
    }

    //Draw the paddle
    u8g2.drawBox(playerX, screen_height - blockBreaker.paddleHeight, blockBreaker.paddleWidth, 4);

    //Draw the ball
    u8g2.drawDisc(blockBreaker.ballX, blockBreaker.ballY, 2, U8G2_DRAW_ALL);

    //Are we running the game?
    if (blockBreaker.running == 1)
    {
        //Change ball position by velocities
        blockBreaker.ballX += blockBreaker.ballXvel;
        blockBreaker.ballY += blockBreaker.ballYvel;
    }
    else
    {
        u8g2.setCursor(screen_width / 7, (screen_height / 1.3));
        u8g2.print("! C L I C K !");

        //A we waiting for a click to start?
        if ((knob1.click == 1) || (knob2.click == 1))
        {
            blockBreaker.running = 1;
        }
    }

    //Did we hit the wall left wall?
    if (blockBreaker.ballX <= (blockBreaker.ballWidth / 2))
    {
        blockBreaker.ballXvel = 1;
    }

    //Did we hit the right wall?
    if (blockBreaker.ballX >= (screen_width - (blockBreaker.ballWidth / 2)))
    {
        blockBreaker.ballXvel = -1;
    }

    //Did we hit the ceiling?
    if ((blockBreaker.ballY - (blockBreaker.ballWidth / 2)) <= 0)
    {
        blockBreaker.ballYvel = 1;
    }

    //Did we hit the paddle height?
    if (blockBreaker.ballY == (screen_height - blockBreaker.paddleHeight - (blockBreaker.ballWidth / 2)))
    {
        if (((blockBreaker.ballX + (blockBreaker.ballWidth / 2)) < playerX) || (blockBreaker.ballX > (playerX + blockBreaker.paddleWidth + (blockBreaker.ballWidth / 2))))
        {
        }
        else if (blockBreaker.ballYvel > 0)
        {
            blockBreaker.ballYvel = -1; //Hit the paddle! Bounce the ball
            blockBreaker.score++;
        }
    }

    //2nd Chance - Did we hit the paddle height?
    if (blockBreaker.ballY == (screen_height - blockBreaker.paddleHeight - (blockBreaker.ballWidth / 2) + 2))
    {
        if (((blockBreaker.ballX + (blockBreaker.ballWidth / 2)) < playerX) || (blockBreaker.ballX > (playerX + blockBreaker.paddleWidth + (blockBreaker.ballWidth / 2))))
        {
            //This is game over condition area
            blockBreaker.message = 2;
            blockBreaker.messageTimer = 24;
        }
        else
        {
            blockBreaker.ballYvel = -1; //Hit the paddle! Bounce the ball
            blockBreaker.message = 1;
            blockBreaker.messageTimer = 24;
            blockBreaker.score++;
        }
    }

    if ((blockBreaker.ballY - 10) > screen_height)
    {
        //Place the cursor and draw some game over message
        u8g2.setCursor(4, screen_height / 3);
        u8g2.print("G A M E  O V E R !!!");

        //Draw the score?
        u8g2.setCursor(35, (screen_height / 1.5));
        u8g2.print("Score: ");
        u8g2.setCursor(75, (screen_height / 1.5));
        u8g2.print(blockBreaker.score);

        //Send display out
        u8g2.sendBuffer();
        delay(5000);
        endGameMode();
    }
}

void blockbreaker_reset()
{
    //Current score is back to 0
    blockBreaker.score = 0;

    blockBreaker.message = 0;
    blockBreaker.messageTimer = 0;

    blockBreaker.ballY = screen_height / 2;
    blockBreaker.ballX = screen_width / 2;
    blockBreaker.ballXvel = -1;
    blockBreaker.ballYvel = 1;

    //Player to the middle of the screen
    playerX = screen_width / 2;
    playerY = 0;

    //And at the bottom
    blockBreaker.paddleHeight = 2;
}

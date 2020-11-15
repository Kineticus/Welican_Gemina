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
    u8g2.drawVLine(0, 0, SCREEN_HEIGHT);
    u8g2.drawVLine(SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    u8g2.drawHLine(0, 0, SCREEN_WIDTH);

    if (blockBreaker.messageTimer > 0)
    {
        switch (blockBreaker.message)
        {
        case 1:
            u8g2.setCursor(5, (SCREEN_HEIGHT / 1.5));
            u8g2.print("! N I C E  S A V E !");
            break;
        case 2:
            u8g2.setCursor((SCREEN_WIDTH / 2) - 10, SCREEN_HEIGHT / 1.5);
            u8g2.print(":(");
            break;
        }

        blockBreaker.messageTimer = blockBreaker.messageTimer - 1;
    }

    //Add input from the other knob and clear it
    player.X += player.Y;
    player.Y = 0;

    //Make sure we're in range
    if (player.X < 0)
    {
        player.X = 0;
    }
    if (player.X > (SCREEN_WIDTH - blockBreaker.paddleWidth))
    {
        player.X = SCREEN_WIDTH - blockBreaker.paddleWidth;
    }

    //Draw the blocks
    for (int i = 0; i < 40; i++)
    {
        if (blockBreaker.block[i].Health != 0)
        {
            u8g2.drawBox(blockBreaker.block[i].X, blockBreaker.block[i].Y, blockBreaker.blockWidth, blockBreaker.blockHeight);
            //u8g2.drawBox(player.X, SCREEN_HEIGHT - blockBreaker.paddleHeight, blockBreaker.paddleWidth, 4);
        }
    }

    //Draw the paddle
    u8g2.drawBox(player.X, SCREEN_HEIGHT - blockBreaker.paddleHeight, blockBreaker.paddleWidth, 4);

    //Are we running the game?
    if (blockBreaker.running == 1)
    {
        //Change ball position by velocities
        blockBreaker.ballX += blockBreaker.ballXvel;
        blockBreaker.ballY += blockBreaker.ballYvel;
    }
    else
    {
        u8g2.setCursor(SCREEN_WIDTH / 7, (SCREEN_HEIGHT / 1.3));
        u8g2.print("! C L I C K !");

        //Ball on paddle
        blockBreaker.ballY = SCREEN_HEIGHT - (blockBreaker.paddleHeight + (blockBreaker.ballWidth / 2) + 1);
        blockBreaker.ballX = player.X + (blockBreaker.paddleWidth /2);

        //A we waiting for a click to start?
        if ((knob1.click == 1) || (knob2.click == 1))
        {
            blockBreaker.running = 1;
        }
    }

    //Draw the ball
    u8g2.drawDisc(blockBreaker.ballX, blockBreaker.ballY, 2, U8G2_DRAW_ALL);

    //Did we hit a block? Check every block
    for (int i = 0; i < 40; i++)
    {
        //Is the block "alive"
        if (blockBreaker.block[i].Health != 0)
        {
            //What direction are we going?
            
            //Going Right
            if (blockBreaker.ballXvel >= 0)
            {
                if ((blockBreaker.ballY - (blockBreaker.ballWidth / 2) >= blockBreaker.block[i].Y) && (blockBreaker.ballY - (blockBreaker.ballWidth / 2) <= blockBreaker.block[i].Y + blockBreaker.blockHeight))
                {
                    if (blockBreaker.ballX + (blockBreaker.ballWidth /2) == blockBreaker.block[i].X)
                    {
                        blockBreaker.ballXvel *= -1;
                        blockBreaker.block[i].Health -= 1;
                        blockBreaker.score++;
                    }
                }
            }

            
            //Going Left
            if (blockBreaker.ballXvel <= 0)
            {
                if ((blockBreaker.ballY + (blockBreaker.ballWidth / 2) >= blockBreaker.block[i].Y) && (blockBreaker.ballY - (blockBreaker.ballWidth / 2) <= blockBreaker.block[i].Y + blockBreaker.blockHeight))
                {
                    if (blockBreaker.ballX + (blockBreaker.ballWidth /2) == blockBreaker.block[i].X + blockBreaker.blockWidth)
                    {
                        blockBreaker.ballXvel *= -1;
                        blockBreaker.block[i].Health -= 1;
                        blockBreaker.score++;
                    }
                }
            }
            
            //Going Down
            if (blockBreaker.ballYvel >= 0)
            {
                if ((blockBreaker.ballX + (blockBreaker.ballWidth / 2) >= blockBreaker.block[i].X) && (blockBreaker.ballX + (blockBreaker.ballWidth / 2) <= blockBreaker.block[i].X + blockBreaker.blockWidth))
                {
                    if (blockBreaker.ballY + (blockBreaker.ballWidth / 2) == blockBreaker.block[i].Y)
                    {
                        blockBreaker.ballYvel *= -1;
                        blockBreaker.block[i].Health -= 1;
                        blockBreaker.score++;
                    } 
                }
            }

            //Going Up
            if (blockBreaker.ballYvel <= 0)
            {
                if ((blockBreaker.ballX + (blockBreaker.ballWidth / 2) >= blockBreaker.block[i].X) && (blockBreaker.ballX + (blockBreaker.ballWidth / 2) <= blockBreaker.block[i].X + blockBreaker.blockWidth))
                {
                    if (blockBreaker.ballY - (blockBreaker.ballWidth / 2) == blockBreaker.block[i].Y  + blockBreaker.blockHeight)
                    {
                        blockBreaker.ballYvel *= -1;
                        blockBreaker.block[i].Health -= 1;
                        blockBreaker.score++;
                    } 
                }
            }
            
        }
    }

    //Did we hit the wall left wall?
    if (blockBreaker.ballX <= (blockBreaker.ballWidth / 2))
    {
        blockBreaker.ballXvel = 1;
    }

    //Did we hit the right wall?
    if (blockBreaker.ballX >= (SCREEN_WIDTH - (blockBreaker.ballWidth / 2)))
    {
        blockBreaker.ballXvel = -1;
    }

    //Did we hit the ceiling?
    if ((blockBreaker.ballY - (blockBreaker.ballWidth / 2)) <= 0)
    {
        blockBreaker.ballYvel = 1;
    }

    //Did we hit the paddle height?
    if (blockBreaker.ballY == (SCREEN_HEIGHT - blockBreaker.paddleHeight - (blockBreaker.ballWidth / 2)))
    {
        if (((blockBreaker.ballX + (blockBreaker.ballWidth / 2)) < player.X) || (blockBreaker.ballX > (player.X + blockBreaker.paddleWidth + (blockBreaker.ballWidth / 2))))
        {
        }
        else if (blockBreaker.ballYvel > 0)
        {
            blockBreaker.ballYvel *= -1; //Hit the paddle! Bounce the ball
        }
    }

    //2nd Chance - Did we hit the paddle height?
    if (blockBreaker.ballY == (SCREEN_HEIGHT - blockBreaker.paddleHeight - (blockBreaker.ballWidth / 2) + 2))
    {
        if (((blockBreaker.ballX + (blockBreaker.ballWidth / 2)) < player.X) || (blockBreaker.ballX > (player.X + blockBreaker.paddleWidth + (blockBreaker.ballWidth / 2))))
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

    if ((blockBreaker.ballY - 10) > SCREEN_HEIGHT)
    {
        //Place the cursor and draw some game over message
        u8g2.setCursor(4, SCREEN_HEIGHT - 8);
        u8g2.print("G A M E  O V E R !!!");

        //Draw the score?
        u8g2.setCursor(35, (SCREEN_HEIGHT / 1.5));
        u8g2.print("Score: ");
        u8g2.setCursor(75, (SCREEN_HEIGHT / 1.5));
        u8g2.print(blockBreaker.score);

        //Send display out
        u8g2.sendBuffer();
        delay(5000);
        endGameMode();
    }
}

void blockbreaker_setBlocks()
{
    for (int i = 0; i < 4; i++)
    {
        for (int ii = 0; ii < 10; ii++)
        {
            blockBreaker.block[(i * 10) + ii].X = ii * (blockBreaker.blockWidth + 2) + 5;
            blockBreaker.block[(i * 10) + ii].Y = i * (blockBreaker.blockHeight + 2) + 3;
            blockBreaker.block[(i * 10) + ii].Health = 1;
        }
    }
}

void blockbreaker_reset()
{
    //Not running
    blockBreaker.running = 0;

    //Current score is back to 0
    blockBreaker.score = 0;

    blockBreaker.message = 0;
    blockBreaker.messageTimer = 0;

    blockBreaker.ballXvel = 1;
    blockBreaker.ballYvel = -1;

    //player. to the middle of the screen
    player.X = SCREEN_WIDTH / 2;
    player.Y = 0;

    //And at the bottom
    blockBreaker.paddleHeight = 2;

    //Reset block layout
    blockbreaker_setBlocks();
}

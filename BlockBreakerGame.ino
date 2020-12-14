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
    for (int i = 0; i < 70; i++)
    {
        if (blockBreaker.block[i].Health == 0)
        {
            //Draw nothing in there is no health
        }
        else if (blockBreaker.block[i].Health < 254)
        {
            u8g2.drawBox(blockBreaker.block[i].X, blockBreaker.block[i].Y, blockBreaker.blockWidth, blockBreaker.blockHeight);
            //u8g2.drawBox(player.X, SCREEN_HEIGHT - blockBreaker.paddleHeight, blockBreaker.paddleWidth, 4);
        }
        else if (blockBreaker.block[i].Health == 255)
        {
            u8g2.drawFrame(blockBreaker.block[i].X, blockBreaker.block[i].Y, blockBreaker.blockWidth, blockBreaker.blockHeight);
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
        //u8g2.print("! C L I C K !");

        //Ball on paddle
        blockBreaker.ballY = SCREEN_HEIGHT - (blockBreaker.paddleHeight + (blockBreaker.ballWidth / 2) + 1);
        blockBreaker.ballX = player.X + (blockBreaker.paddleWidth /2) + 5; //+5 is small left offset

        //A we waiting for a click to start?
        if ((knob1.click == 1) || (knob2.click == 1))
        {
            blockBreaker.running = 1;
        }
    }

    //Draw the ball
    u8g2.drawDisc(int(blockBreaker.ballX), int(blockBreaker.ballY), (blockBreaker.ballWidth / 2), U8G2_DRAW_ALL);


    byte blockGone = 0;
    int blockCount = 0;

    //Did we hit a block? Check every block
    for (int i = 0; i < 70; i++)
    {
        //Is the block "alive"?
        if (blockBreaker.block[i].Health != 0)
        {
            //There is a block here!
            blockGone = 0;

            //What direction are we going?
            //Going Up
            if ((blockBreaker.ballYvel <= 0) && (blockGone == 0))
            {
                //Check Width (X) match, Left Side && Right Side of block
                if ((blockBreaker.ballX + (blockBreaker.ballWidth / 2) >= blockBreaker.block[i].X) && (blockBreaker.ballX - (blockBreaker.ballWidth / 2) <= blockBreaker.block[i].X + blockBreaker.blockWidth))
                {
                    //Check Height (Y) match, Bottom && Top
                    if ((blockBreaker.ballY - (blockBreaker.ballWidth / 2) >= blockBreaker.block[i].Y + (blockBreaker.blockHeight / 2)) && (blockBreaker.ballY <= blockBreaker.block[i].Y + blockBreaker.blockHeight + (blockBreaker.ballWidth / 2)))
                    {
                        //Bounce the ball
                        blockBreaker.ballYvel *= -1;
                        
                        //Skip to the end of block checking as this one is gone already
                        blockGone = 1;

                        if (blockBreaker.block[i].Health != 255)
                        {
                            blockBreaker.block[i].Health -= 1;
                        }

                        //Blink the Status LED and give the player a point
                        if (blockBreaker.block[i].Health == 0)
                        {                          
                            blockBreaker.score++;
                            ledcWrite(STATUS_LED, 4095);
                        }
                    } 
                }
            }

            //Going Right
            if ((blockBreaker.ballXvel > 0) && (blockGone == 0))
            {
                if ((blockBreaker.ballY - (blockBreaker.ballWidth / 2) >= blockBreaker.block[i].Y) && (blockBreaker.ballY - (blockBreaker.ballWidth / 2) <= blockBreaker.block[i].Y + blockBreaker.blockHeight))
                {
                    if ((blockBreaker.ballX + (blockBreaker.ballWidth / 2) >= blockBreaker.block[i].X) && (blockBreaker.ballX <= blockBreaker.block[i].X + (blockBreaker.blockWidth / 2)))
                    {
                        blockBreaker.ballXvel *= -1;
                        
                        //Skip to the end of block checking as this one is gone already
                        blockGone = 1;

                        if (blockBreaker.block[i].Health != 255)
                        {
                            blockBreaker.block[i].Health -= 1;
                        }

                        //Blink the Status LED and give the player a point
                        if (blockBreaker.block[i].Health == 0)
                        {                          
                            blockBreaker.score++;
                            ledcWrite(STATUS_LED, 4095);
                        }
                    }
                }
            }

            //Going Left
            if ((blockBreaker.ballXvel < 0) && (blockGone == 0))
            {
                if ((blockBreaker.ballY + (blockBreaker.ballWidth / 2) >= blockBreaker.block[i].Y) && (blockBreaker.ballY - (blockBreaker.ballWidth / 2) <= blockBreaker.block[i].Y + blockBreaker.blockHeight))
                {
                    if ((blockBreaker.ballX - (blockBreaker.ballWidth / 2) <= blockBreaker.block[i].X + blockBreaker.blockWidth) && (blockBreaker.ballX >= blockBreaker.block[i].X - (blockBreaker.blockWidth / 2)))
                    {
                        blockBreaker.ballXvel *= -1;
                        
                        //Skip to the end of block checking as this one is gone already
                        blockGone = 1;

                        if (blockBreaker.block[i].Health != 255)
                        {
                            blockBreaker.block[i].Health -= 1;
                        }

                        //Blink the Status LED and give the player a point
                        if (blockBreaker.block[i].Health == 0)
                        {                          
                            blockBreaker.score++;
                            ledcWrite(STATUS_LED, 4095);
                        }
                    }
                }
            }

            //Going Down
            if ((blockBreaker.ballYvel >= 0) && (blockGone == 0))
            {
                if ((blockBreaker.ballX + (blockBreaker.ballWidth / 2) >= blockBreaker.block[i].X) && (blockBreaker.ballX - (blockBreaker.ballWidth / 2) <= blockBreaker.block[i].X + blockBreaker.blockWidth))
                {
                    if ((blockBreaker.ballY + (blockBreaker.ballWidth / 2) >= blockBreaker.block[i].Y) && (blockBreaker.ballY - (blockBreaker.ballWidth / 2) <= blockBreaker.block[i].Y + (blockBreaker.blockHeight / 3)))
                    {
                        blockBreaker.ballYvel *= -1;

                        //Skip to the end of block checking as this one is gone already
                        blockGone = 1;

                        if (blockBreaker.block[i].Health != 255)
                        {
                            blockBreaker.block[i].Health -= 1;
                        }

                        //Blink the Status LED and give the player a point
                        if (blockBreaker.block[i].Health == 0)
                        {                          
                            blockBreaker.score++;
                            ledcWrite(STATUS_LED, 4095);
                        }
                    } 
                }
            }

            //Add to Blocks Left count if it's not a wall
            if (blockBreaker.block[i].Health != 255) 
            {
                blockCount += 1;     
            }
        }
    }

    if (blockCount == 0)
    {
        //Advance level
        blockBreaker.level ++;

        u8g2.setCursor(4, SCREEN_HEIGHT - 8);
        u8g2.print(" N E X T  L E V E L ");
        u8g2.setCursor(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        u8g2.print(blockBreaker.level);
        u8g2.sendBuffer();
        delay(5000);

        //Not running, give user a break
        blockBreaker.running = 0;
        
        //Reset blocks with new level layout
        blockbreaker_setBlocks(blockBreaker.level);
    }

    //Did we hit the wall left wall?
    if ((blockBreaker.ballX <= (blockBreaker.ballWidth / 2)) && blockBreaker.ballXvel < 0)
    {
        blockBreaker.ballXvel *= -1;
    }

    //Did we hit the right wall?
    if ((blockBreaker.ballX >= (SCREEN_WIDTH - (blockBreaker.ballWidth / 2))) && blockBreaker.ballXvel > 0)
    {
        blockBreaker.ballXvel *= -1;
    }

    //Did we hit the ceiling?
    if ((blockBreaker.ballY - (blockBreaker.ballWidth / 2)) <= 0)
    {
        blockBreaker.ballYvel *= -1;
    }

    //Did we hit the paddle height?
    if (blockBreaker.ballY == (SCREEN_HEIGHT - blockBreaker.paddleHeight - (blockBreaker.ballWidth / 2)))
    {
        if (((blockBreaker.ballX + (blockBreaker.ballWidth / 2)) < player.X) || (blockBreaker.ballX > (player.X + blockBreaker.paddleWidth + (blockBreaker.ballWidth / 2))))
        {
        }
        else if (blockBreaker.ballYvel > 0)
        {
            int paddleAngle = (player.X + (blockBreaker.paddleWidth / 2)) - blockBreaker.ballX;

            
            if (paddleAngle <=-5)
            {
                blockBreaker.ballXvel = 2;
                blockBreaker.ballYvel = -.5;
                
            }
            if (paddleAngle >=-4 && paddleAngle <=-3)
            {
                blockBreaker.ballXvel = 1;
                blockBreaker.ballYvel = -1;
            }
            if (paddleAngle >=-2 && paddleAngle <=-1)
            {
                blockBreaker.ballXvel = .5;
                blockBreaker.ballYvel = -1.5;
            }
             if (paddleAngle >=0 && paddleAngle <=0)
            {
                blockBreaker.ballXvel = 0;
                blockBreaker.ballYvel = -1;
            }
            if (paddleAngle >=1 && paddleAngle <=2)
            {
                blockBreaker.ballXvel = -.5;
                blockBreaker.ballYvel = -1.5;
            }
            if (paddleAngle >=3 && paddleAngle <=4)
            {
                blockBreaker.ballXvel = -1;
                blockBreaker.ballYvel = -1;
            }
            if (paddleAngle >=5)
            {
                blockBreaker.ballXvel = -2;
                blockBreaker.ballYvel = -.5;
            }          
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
            blockBreaker.ballYvel *= -1; //Hit the paddle! Bounce the ball
            blockBreaker.message = 1;
            blockBreaker.messageTimer = 24;
        }
    }

    if ((blockBreaker.ballY - 10) > SCREEN_HEIGHT)
    {
        //Place the cursor and draw some game over message
        u8g2.setCursor(4, SCREEN_HEIGHT - 8);
        u8g2.print("G A M E  O V E R !!!");

        //Draw the ?
        u8g2.setCursor(35, (SCREEN_HEIGHT / 1.5));
        u8g2.print(": ");
        u8g2.setCursor(75, (SCREEN_HEIGHT / 1.5));
        u8g2.print(blockBreaker.);

        //Send display out
        u8g2.sendBuffer();
        delay(5000);
        endGameMode();
    }
}

void blockbreaker_setBlocks(byte level)
{
    for (int i = 0; i < 70; i++)
    {
        blockBreaker.block[i].Health = 0;
    }

    //Reset ball velocity
    blockBreaker.ballXvel = 1;
    blockBreaker.ballYvel = -1;

    Serial.println("Block [i]: X, Y, Health");
    switch (level)
    {
        case 0:
        {
            Serial.println("**** LEVEL 1 ****");
            blockBreaker.blockWidth = 20;
            blockBreaker.blockHeight = 10;
            blockBreaker.paddleWidth = 25;
            blockBreaker.ballWidth = 6;
            for (int i = 0; i < 3; i++)
            {
                //for (int ii = 0; ii < 10; ii++)
                for (int ii = 0; ii < 5; ii++)
                {
                    byte iii = (i * 10) + ii;
                    
                    blockBreaker.block[iii].X = ii * (blockBreaker.blockWidth + 4) + 5;
                    blockBreaker.block[iii].Y = i * (blockBreaker.blockHeight + 4) + 3;
                    blockBreaker.block[iii].Health = 1;

                    /*
                    if (iii % 2)
                    {
                        blockBreaker.block[iii].Health = 255;
                    }
                    else
                    {
                        blockBreaker.block[iii].Health = 1;
                    }
                    */

                    Serial.print("Block ");
                    Serial.print(iii);
                    Serial.print(": ");
                    Serial.print(blockBreaker.block[iii].X);
                    Serial.print(",");
                    Serial.print(blockBreaker.block[iii].Y);
                    Serial.print(",");
                    Serial.println(blockBreaker.block[iii].Health);
                }
            }
        }
        break;
        case 1:
        {
            blockBreaker.blockWidth = 15;
            blockBreaker.blockHeight = 8;
            blockBreaker.paddleWidth = 16;
            blockBreaker.ballWidth = 4;
            for (int i = 0; i < 3; i++)
            {
                for (int ii = 0; ii < 7; ii++)
                {
                    blockBreaker.block[(i * 10) + ii].X = ii * (blockBreaker.blockWidth + 2) + 5;
                    blockBreaker.block[(i * 10) + ii].Y = i * (blockBreaker.blockHeight + 2) + 3;
                    blockBreaker.block[(i * 10) + ii].Health = 1;
                }
            }
        }
        break;
        case 2:
        {
            blockBreaker.blockWidth = 10;
            blockBreaker.blockHeight = 5;
            blockBreaker.paddleWidth = 16;
            blockBreaker.ballWidth = 4;
            for (int i = 0; i < 3; i++)
            {
                for (int ii = 0; ii < 10; ii++)
                {
                    blockBreaker.block[(i * 10) + ii].X = ii * (blockBreaker.blockWidth + 2) + 5;
                    blockBreaker.block[(i * 10) + ii].Y = i * (blockBreaker.blockHeight + 2) + 3;
                    blockBreaker.block[(i * 10) + ii].Health = 1;
                }
            }
        }
        break;
        case 3:
        {
            for (int i = 0; i < 5; i++)
            {
                for (int ii = 0; ii < 10; ii++)
                {
                    blockBreaker.block[(i * 10) + ii].X = ii * (blockBreaker.blockWidth + 2) + 5;
                    blockBreaker.block[(i * 10) + ii].Y = i * (blockBreaker.blockHeight + 2) + 3;
                    blockBreaker.block[(i * 10) + ii].Health = 1;
                }
            }
        }
        break;
        case 4:
        {
            for (int i = 0; i < 7; i++)
            {
                for (int ii = 0; ii < 10; ii++)
                {
                    blockBreaker.block[(i * 10) + ii].X = ii * (blockBreaker.blockWidth + 2) + 5;
                    blockBreaker.block[(i * 10) + ii].Y = i * (blockBreaker.blockHeight + 2) + 3;
                    blockBreaker.block[(i * 10) + ii].Health = 1;
                }
            }
        }
        break;
    }
}

void blockbreaker_reset()
{
    //Not running
    blockBreaker.running = 0;

    //Current  is back to 0
    blockBreaker. = 0;

    blockBreaker.message = 0;
    blockBreaker.messageTimer = 0;

    blockBreaker.ballXvel = 1;
    blockBreaker.ballYvel = -1;

    //player. to the middle of the screen
    player.X = SCREEN_WIDTH / 2;
    player.Y = 0;

    //And at the bottom
    blockBreaker.paddleHeight = 2;

    //Level back to 0
    blockBreaker.level = 0;

    //Reset block layout
    blockbreaker_setBlocks(blockBreaker.level);
}

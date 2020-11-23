/**************************************************************

Pong! The greatest game ever!

Brian Schimke, 2020
**************************************************************/

void pong_game()
{   
    //Detect click



    //Increment tick counter
    pong.tick++;

    //See if it's game over
    byte ballsLeft = 0;
    for(int i = 0; i < 20; i++)
    {
        if (pong.ball[i].active == true)
        {
            ballsLeft ++;
        }
    }

    //Make sure we have the right font and color
    u8g2.setFont(u8g2_font_profont12_mf);
    u8g2.setDrawColor(1);

    //Draw the score
    u8g2.setCursor((SCREEN_WIDTH / 2) - 20, 12);
    u8g2.print(pong.score1);

    u8g2.setCursor((SCREEN_WIDTH / 2) + 20, 12);
    u8g2.print(pong.score2);

    //Draw the borders
    u8g2.drawHLine(0, 0, SCREEN_WIDTH);
    u8g2.drawHLine(0, SCREEN_HEIGHT, SCREEN_WIDTH);

    //Draw divider
    for(int i = pong.spacing / 2; i < SCREEN_HEIGHT - (pong.spacing / 2); i += pong.spacing * 2)
    {
        u8g2.drawVLine(SCREEN_WIDTH / 2, i, pong.spacing);
    }

    //Make sure we're in range
    if (player.X <= pong.paddleWidth1)
    {
        player.X = pong.paddleWidth1;
    }
    if (player.X >= SCREEN_HEIGHT - 1)
    {
        player.X = SCREEN_HEIGHT - 1;
    }
    
    if (player.Y <= pong.paddleWidth2 + 1)
    {
        player.Y = pong.paddleWidth2 + 1;
    }
    if (player.Y >= SCREEN_HEIGHT)
    {
        player.Y = SCREEN_HEIGHT;
    }

    //Draw the paddles
    u8g2.drawBox((SCREEN_WIDTH + 1) - pong.paddleHeight1, SCREEN_HEIGHT - player.X, pong.paddleHeight1, pong.paddleWidth1);
    u8g2.drawBox(0, player.Y - pong.paddleWidth2, pong.paddleHeight2, pong.paddleWidth2);

    //Ball movement
    if (pong.tick > pong.speed)
    {
        for(int i = 0; i < 20; i++)
        {
            if (pong.ball[i].active == true)
            {
                //Add velocities
                pong.ball[i].x += pong.ball[i].velX;
                pong.ball[i].y += pong.ball[i].velY;

                //Check screen border
                if (pong.ball[i].y >= SCREEN_HEIGHT - pong.ball[i].size - 1)
                {
                    pong.ball[i].velY *= -1;
                    pong.ball[i].y = SCREEN_HEIGHT - pong.ball[i].size - 1;
                }

                if (pong.ball[i].y <= 1 + pong.ball[i].size)
                {
                    pong.ball[i].velY *= -1;
                    pong.ball[i].y = pong.ball[i].size + 1;
                }

                //Paddle impacts
                if ((pong.ball[i].x + pong.ball[i].size >= SCREEN_WIDTH - pong.paddleHeight1) && (pong.ball[i].x + pong.ball[i].size <= SCREEN_WIDTH - pong.paddleHeight1 + pong.ball[i].velX * 2))
                {   
                    //Check Y
                    if ((pong.ball[i].y + pong.ball[i].size >= SCREEN_HEIGHT - player.X) && (pong.ball[i].y - pong.ball[i].size < SCREEN_HEIGHT - player.X + pong.paddleWidth1)) 
                    {
                        pong.ball[i].velX *= -1;
                        //pong.ball[i].x = SCREEN_WIDTH - pong.paddleHeight1 - pong.ball[i].size; //+1
                        Serial.print("1o = ");
                        int offset = SCREEN_HEIGHT - player.X - pong.ball[i].y + (pong.paddleWidth1 / 2);
                        Serial.println(offset);
                        Serial.print("velvX, Y = ");
                        pong.ball[i].velY = offset * - 1;
                        if (abs(offset) > 1)
                        {
                            pong.ball[i].velY = (offset / 2) * - 1;
                        }
                        //pong.ball[i].velX = abs((offset - (pong.paddleWidth1 / 2) + 1) / 2) * - 1;
                        if ((pong.ball[i].velY > 1) || (pong.ball[i].velY < -1))
                        {
                            pong.ball[i].velX = offset / pong.ball[i].velY;
                        }
                        else
                        {
                            pong.ball[i].velX = -2;
                        }
                        
                        Serial.print(pong.ball[i].velX);
                        Serial.print(" ");
                        Serial.println(pong.ball[i].velY);
                    }
                }

                if ((pong.ball[i].x - pong.ball[i].size <= pong.paddleHeight2) && (pong.ball[i].x - pong.ball[i].size >= pong.paddleHeight2 + pong.ball[i].velX * 2))
                {
                    //Check Y
                    if ((pong.ball[i].y - pong.ball[i].size < player.Y) && (pong.ball[i].y + pong.ball[i].size >= player.Y - pong.paddleWidth2)) 
                    {    
                        pong.ball[i].velX *= -1;
                        //pong.ball[i].x = pong.ball[i].size + pong.paddleHeight2; //-1
                        Serial.print("2o = ");
                        int offset = pong.ball[i].y - player.Y + (pong.paddleWidth2 / 2);
                        Serial.println(offset); //- (pong.paddleWidth2 / 2));
                        Serial.print("velX, Y = ");
                        pong.ball[i].velY = offset;
                        if (abs(offset) > 1)
                        {
                            pong.ball[i].velY = offset / 2;
                        }
                        //pong.ball[i].velX = abs((offset - (pong.paddleWidth2 / 2) + 1) / 2); //suspect
                        if ((pong.ball[i].velY > 1) || (pong.ball[i].velY < -1))
                        {
                            pong.ball[i].velX = offset / pong.ball[i].velY;
                        }
                        else
                        {
                            pong.ball[i].velX = 2;
                        }
                        
                        Serial.print(pong.ball[i].velX);
                        Serial.print(" ");
                        Serial.println(pong.ball[i].velY);
                    }
                }

                //Check for scores
                if (pong.ball[i].x < 0 - pong.ball[i].size)
                {
                    pong.ball[i].active = false;
                    pong.score2++;
                    pong.recent = 2;
                }


                if (pong.ball[i].x > SCREEN_WIDTH + pong.ball[i].size)
                {
                    pong.ball[i].active = false;
                    pong.score1++;
                    pong.recent = 1;
                }
            }
        }

        pong.tick = 0;
    }

    //Draw the ball(s)
    for(int i = 0; i < 20; i++)
    {
        if (pong.ball[i].active == true)
        {
            u8g2.drawDisc(pong.ball[i].x, pong.ball[i].y, pong.ball[i].size, U8G2_DRAW_ALL);
        }
    }

    //Are no balls left active?
    if (ballsLeft == 0)
    {
        //Check the score to see if anyone just won
        if ((pong.score1 >= pong.scoreToWin) || (pong.score2 >= pong.scoreToWin))
        {
            pong_gameOver();
        }
        else  //they didn't, so spawn a new ball
        {
            pong.ball[0].active = true;
            pong.ball[0].x = SCREEN_WIDTH / 2;
            //pong.ball[0].y = SCREEN_HEIGHT / 2;
            pong.ball[0].y = random(10, SCREEN_HEIGHT - 10);
            pong.ball[0].size = 2;
            if (pong.recent == 1)
            {
                pong.ball[0].velX = -1;
            }
            else
            {
                pong.ball[0].velX = 1;
            }
           
            //pong.ball[0].velX = random(0, 2);
            //pong.ball[i].velY = random(0, 5);
            pong.ball[0].velY = 0;
        }
    }


}

void pong_gameOver()
{
    //Place the cursor and draw some game over message
    u8g2.setCursor(4, SCREEN_HEIGHT - 8);
    u8g2.print("G A M E  O V E R !!!");

    //Send display out
    u8g2.sendBuffer();
    delay(5000);
    endGameMode();
}

void pong_reset()
{
    player.X = (SCREEN_HEIGHT / 2) + (pong.paddleWidth1 / 2) + 1; //
    player.Y = (SCREEN_HEIGHT / 2) + (pong.paddleWidth2 / 2); //
    pong.score1 = 0;
    pong.score2 = 0;
    pong.speed = 0;
    pong.tick = 0;
    pong.recent = 0;

    for(int i = 0; i < 20; i++)
    {
        pong.ball[i].x = SCREEN_WIDTH / 2;
        pong.ball[i].y = SCREEN_HEIGHT / 2;
        pong.ball[i].size = 2;
        pong.ball[i].active = false;
        pong.ball[i].velX = random(1, 2);
        //pong.ball[i].velY = random(0, 5);
        pong.ball[i].velY = 0;
    }

    pong.ball[0].active = true;
}
/**************************************************************

Snake! The greatest game ever!

Brian Schimke, 2020
**************************************************************/

void snake_game()
{
    //Only increment game when ticks reach set speed. 0 = as fast as possible
    snake.tick++;
    
    //Add input from the other knob and clear it
    player.X += player.Y;
    player.Y = 0;

    //Make sure we didn't goo to far, OPTIONAL, prevents spinning into yourself
    if ((player.X - snake.oldX) > snake.sensitivity)
    {
        player.X = snake.oldX + snake.sensitivity;
    }
    else if ((player.X - snake.oldX) < -snake.sensitivity)
    {
        player.X = snake.oldX - snake.sensitivity;
    }

    //Make sure we're in range
    if (player.X < 0)
    {
        player.X += 32;
    }
    if (player.X > 31)
    {
        player.X -= 32;
    }

    //Cache old payer position  
    snake.oldX = player.X;

    //Currently binning the angle into 8 groups. Hope to use actual angle eventually
    if (player.X < 4)
    {
        snake.angle = 0;
    }
    else if (player.X < 8)
    {
        snake.angle = .8;
    }
    else if (player.X < 12)
    {
        snake.angle = 1.6;
    }
    else if (player.X < 16)
    {
        snake.angle = 2.4;
    }
    else if (player.X < 20)
    {
        snake.angle = 3.2;
    }
    else if (player.X < 24)
    {
        snake.angle = 4;
    }
    else if (player.X < 28)
    {
        snake.angle = 4.8;
    }
    else if (player.X < 32)
    {
        snake.angle = 5.6;
    }

    //bool snake_hitSomething = false;

    if (snake.tick > snake.speed)
    {
        //Reset tick count
        snake.tick = 0;
        
        //Shift the snake
        for (int i = 0; i < snake.num; i++)
        {
            snake.segment[i].x = snake.segment[i+1].x;
            snake.segment[i].y = snake.segment[i+1].y;
        }
        
        //Calculate 1 point on circle
        snake.segment[snake.num].x += (1 * sin(-snake.angle)) + .5;
        snake.segment[snake.num].y += (1 * cos(-snake.angle)) + .5;

        //Check to see if we've hit something
        //snake_hitSomething = snake_checkCollisions();
    }
    else
    {
        //Draw the pending snake head
        u8g2.drawPixel(snake.segment[snake.num].x + (1 * sin(-snake.angle)) + .5, snake.segment[snake.num].y + (1 * cos(-snake.angle)) + .5);
    }
    
    //Draw borders
    u8g2.drawVLine(0, 0, SCREEN_HEIGHT);
    u8g2.drawVLine(SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    u8g2.drawHLine(0, 0, SCREEN_WIDTH);
    u8g2.drawHLine(0, SCREEN_HEIGHT, SCREEN_WIDTH + 1);

    //Draw the snake
    for (int i = 0; i <= snake.num; i++)
    {
        u8g2.drawPixel(snake.segment[i].x, snake.segment[i].y);
    }

    //Draw apples and check for bites
    snake_manageOrchard();
    

    //Run our collision checks
    if (snake_checkCollisions())
    {
        snake_gameOver();
    }
}

void snake_manageOrchard()
{
    //Random chance to spawn apple
    if (random(0, snake.appleRate) == 1)
    {   
        //Look through max apples
        for (int i = 0; i < snake.maxApples; i++)
        {
            //Find one that is not active
            if(snake.apple[i].active == false)
            {
                //enable it!
                snake.apple[i].active = true;
                snake.apple[i].x = random(3, SCREEN_WIDTH - 3);
                snake.apple[i].y = random(3, SCREEN_HEIGHT - 3);
                snake.apple[i].size = random(1, snake.maxAppleSize);

                //Make sure it isn't on the snake. If so, try again
                while (snake_checkBlock(snake.apple[i].x,snake.apple[i].y))
                {
                    snake.apple[i].x = random(3, SCREEN_WIDTH - 3);
                    snake.apple[i].y = random(3, SCREEN_HEIGHT - 3);
                }
                
                //Meet exit condition for loop
                i = snake.maxApples;
            }
        }
    }

    //Look through all apples
    for (int i = 0; i <= snake.maxApples; i++)
    {
        //Find ones that are active
        if(snake.apple[i].active == true)
        {
            //Draw them
            u8g2.drawDisc(snake.apple[i].x, snake.apple[i].y, snake.apple[i].size, U8G2_DRAW_ALL);

            //See if they are being eaten, taking into account size
            if ((snake.segment[snake.num].x >= snake.apple[i].x - snake.apple[i].size) && (snake.segment[snake.num].x <= snake.apple[i].x + snake.apple[i].size))
            {
                if ((snake.segment[snake.num].y >= snake.apple[i].y - snake.apple[i].size) && (snake.segment[snake.num].y <= snake.apple[i].y + snake.apple[i].size))  
                {
                    //Eat the apple
                    snake.apple[i].active = false;

                    //Calculate how much to grow
                    int extraLength = snake.apple[i].size * snake.lengthMultiplier;

                    //Can't grow more than the current snake length at once
                    if (extraLength > snake.num)
                    {
                        extraLength = snake.num - 1;
                    }

                    //Score = size
                    snake.score += snake.apple[i].size * snake.scoreMultiplier;

                    //Shift snake up
                    for (int ii = snake.num; ii > 0; ii--)
                    {
                        snake.segment[ii + extraLength].x = snake.segment[ii].x;
                        snake.segment[ii + extraLength].y = snake.segment[ii].y;
                    }

                    //Extra length = size
                    snake.num += extraLength;
                }
            }
        }
    }
}

bool snake_checkCollisions()
{   
    bool hitSomething = false;

    //Top and Bottom border collision
    if ((snake.segment[snake.num].y <= 0) || (snake.segment[snake.num].y >= 63))
    {
        hitSomething = true;
    }
    
    //Left and Right border collision
    if ((snake.segment[snake.num].x <= 0) || (snake.segment[snake.num].x >= 127))
    {
        hitSomething = true;
    }

    //Snake eating itself
    if (snake_checkBlock(snake.segment[snake.num].x, snake.segment[snake.num].y))
    {
        hitSomething = true;
    }

    //Check for diagonal pass DR
    if ((snake.segment[snake.num].x == snake.segment[snake.num - 1].x + 1) && (snake.segment[snake.num].y == snake.segment[snake.num - 1].y + 1))
    {
        //Check for first matching block
        if (snake_checkBlock(snake.segment[snake.num].x - 1, snake.segment[snake.num].y))
        {
            if (snake_checkBlock(snake.segment[snake.num].x, snake.segment[snake.num].y - 1))
            {
                hitSomething = true;
            }
        }
    }

    //Check for diagonal pass UL
    if ((snake.segment[snake.num].x == snake.segment[snake.num - 1].x - 1) && (snake.segment[snake.num].y == snake.segment[snake.num - 1].y - 1))
    {
        //Check for first matching block
        if (snake_checkBlock(snake.segment[snake.num].x + 1, snake.segment[snake.num].y))
        {
            if (snake_checkBlock(snake.segment[snake.num].x, snake.segment[snake.num].y + 1))
            {
                hitSomething = true;
            }
        }
    }

    //Check for diagonal pass UR
    if ((snake.segment[snake.num].x == snake.segment[snake.num - 1].x - 1) && (snake.segment[snake.num].y == snake.segment[snake.num - 1].y + 1))
    {
        //Check for first matching block
        if (snake_checkBlock(snake.segment[snake.num].x - 1, snake.segment[snake.num].y))
        {
            if (snake_checkBlock(snake.segment[snake.num].x, snake.segment[snake.num].y + 1))
            {
               hitSomething = true;
            }
        }
    }

    //Check for diagonal pass DL
    if ((snake.segment[snake.num].x == snake.segment[snake.num - 1].x + 1) && (snake.segment[snake.num].y == snake.segment[snake.num - 1].y - 1))
    {
        //Check for first matching block
        if (snake_checkBlock(snake.segment[snake.num].x + 1, snake.segment[snake.num].y))
        {
            if (snake_checkBlock(snake.segment[snake.num].x, snake.segment[snake.num].y - 1))
            {
               hitSomething = true;
            }
        }
    }

    return hitSomething; 
}

bool snake_checkBlock(int blockCheckX, int blockCheckY)
{
    bool hitTheBlock = false;

    for (int i = 0; i < snake.num - 1; i++)
    {
        if ((snake.segment[i].x == blockCheckX) && (snake.segment[i].y == blockCheckY))
        {
            hitTheBlock = true;
        }
    }

    return hitTheBlock;
}

void snake_gameOver()
{
    //Place the cursor and draw some game over message
    u8g2.setCursor(4, SCREEN_HEIGHT - 8);
    u8g2.print("G A M E  O V E R !!!");

    //Draw the score
    u8g2.setCursor(35, (SCREEN_HEIGHT / 1.5));
    u8g2.print("Score: ");
    u8g2.setCursor(75, (SCREEN_HEIGHT / 1.5));
    u8g2.print(snake.score);

    //Send display out
    u8g2.sendBuffer();
    delay(5000);
    endGameMode();
}

void snake_reset()
{
    snake.num = 10;
    snake.speed = 3;
    snake.score = 0;
    snake.scoreMultiplier = 8;
    snake.lengthMultiplier = 8;
    snake.maxApples = 2;
    snake.appleRate = 100;
    
    //Set knobs to desired states
    player.X = 24;
    player.Y = 0;
    snake.oldX = player.X;

    //Calculate snake points
    for (int i = 0; i <= snake.num; i++)
    {
        snake.segment[i].x = 10 + i;
        snake.segment[i].y = 32;
    }
    
    //Clear apples
    for (int i = 0; i <= 10; i++)
    {
        snake.apple[i].active = false;
    }
}
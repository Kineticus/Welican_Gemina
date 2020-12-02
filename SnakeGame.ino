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

    
    //Check for apple bites, player 1
    snake_checkBites1();

    //Draw apples and manage spawning of new ones
    snake_manageOrchard();
    

    //Run our collision checks
    if (snake_checkCollisions1())
    {
        snake_gameOver();
    }
}

void snake2_game()
{
    //Only increment game when ticks reach set speed. 0 = as fast as possible
    snake.tick++;
    
    //Make sure we didn't goo to far, OPTIONAL, prevents spinning into yourself
    if ((player.X - snake.oldX) > snake.sensitivity)
    {
        player.X = snake.oldX + snake.sensitivity;
    }
    else if ((player.X - snake.oldX) < -snake.sensitivity)
    {
        player.X = snake.oldX - snake.sensitivity;
    }

    //And for P2
    if ((player.Y - snake.oldY) > snake.sensitivity)
    {
        player.Y = snake.oldY + snake.sensitivity;
    }
    else if ((player.Y - snake.oldY) < -snake.sensitivity)
    {
        player.Y = snake.oldY - snake.sensitivity;
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

    //For P2 as well
    if (player.Y < 0)
    {
        player.Y += 32;
    }
    if (player.Y > 31)
    {
        player.Y -= 32;
    }

    //Cache old payer positions  
    snake.oldX = player.X;
    snake.oldY = player.Y;

    //Convert integer knob value to floating radian
    snake.angle = snake_adjustAngle(player.X);
    snake.angle2 = snake_adjustAngle(player.Y);

    //bool snake_hitSomething = false;

    if (snake.tick > snake.speed)
    {
        //Reset tick count
        snake.tick = 0;
        
        //Shift the snakes
        for (int i = 0; i < snake.num; i++)
        {
            snake.segment[i].x = snake.segment[i+1].x;
            snake.segment[i].y = snake.segment[i+1].y;
        }

        for (int i = 0; i < snake.num2; i++)
        {
            snake.segment2[i].x = snake.segment2[i+1].x;
            snake.segment2[i].y = snake.segment2[i+1].y;
        }
        
        //Calculate 1 point on circle
        snake.segment[snake.num].x += (1 * sin(-snake.angle)) + .5;
        snake.segment[snake.num].y += (1 * cos(-snake.angle)) + .5;

        snake.segment2[snake.num2].x += (1 * sin(-snake.angle2)) + .5;
        snake.segment2[snake.num2].y += (1 * cos(-snake.angle2)) + .5;

        //Check to see if we've hit something
        //snake_hitSomething = snake_checkCollisions();
    }
    else
    {
        //Draw the pending snake heads
        u8g2.drawPixel(snake.segment[snake.num].x + (1 * sin(-snake.angle)) + .5, snake.segment[snake.num].y + (1 * cos(-snake.angle)) + .5);
        u8g2.drawPixel(snake.segment2[snake.num2].x + (1 * sin(-snake.angle2)) + .5, snake.segment2[snake.num2].y + (1 * cos(-snake.angle2)) + .5);
    }
    
    //Draw borders
    u8g2.drawVLine(0, 0, SCREEN_HEIGHT);
    u8g2.drawVLine(SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    u8g2.drawHLine(0, 0, SCREEN_WIDTH);
    u8g2.drawHLine(0, SCREEN_HEIGHT, SCREEN_WIDTH + 1);

    //Draw the snakes
    for (int i = 0; i <= snake.num; i++)
    {
        u8g2.drawPixel(snake.segment[i].x, snake.segment[i].y);
    }

    for (int i = 0; i <= snake.num2; i++)
    {
        u8g2.drawPixel(snake.segment2[i].x, snake.segment2[i].y);
    }

    //Check for apple bites
    snake_checkBites1();
    snake_checkBites2();

    //Draw apples and manage spawning of new ones
    snake_manageOrchard();
    

    //Run our collision checks
    if (snake_checkCollisions1())
    {
        snake_gameOver();
    }

    if (snake_checkCollisions2())
    {
        snake_gameOver();
    }

    if (snake_checkCollisions2into1())
    {
        snake_gameOver();
    }

    if (snake_checkCollisions1into2())
    {
        snake_gameOver();
    }
}

float snake_adjustAngle(int snakeAngle)
{
    float newAngle = 0;

    //Currently binning the angle into 8 groups. Hope to use actual angle eventually
    if (snakeAngle < 4)
    {
        newAngle = 0;
    }
    else if (snakeAngle < 8)
    {
        newAngle = .8;
    }
    else if (snakeAngle < 12)
    {
        newAngle = 1.6;
    }
    else if (snakeAngle < 16)
    {
        newAngle = 2.4;
    }
    else if (snakeAngle < 20)
    {
        newAngle = 3.2;
    }
    else if (snakeAngle < 24)
    {
        newAngle = 4;
    }
    else if (snakeAngle < 28)
    {
        newAngle = 4.8;
    }
    else if (snakeAngle < 32)
    {
        newAngle = 5.6;
    }

    return newAngle;
}

void snake_checkBites2()
{
    //Look through all apples
    for (int i = 0; i <= snake.maxApples; i++)
    {
        //Find ones that are active
        if(snake.apple[i].active == true)
        {
            //See if they are being eaten, taking into account size
            if ((snake.segment2[snake.num2].x >= snake.apple[i].x - snake.apple[i].size) && (snake.segment2[snake.num2].x <= snake.apple[i].x + snake.apple[i].size))
            {
                if ((snake.segment2[snake.num2].y >= snake.apple[i].y - snake.apple[i].size) && (snake.segment2[snake.num2].y <= snake.apple[i].y + snake.apple[i].size))  
                {
                    //Eat the apple
                    snake.apple[i].active = false;

                    //Calculate how much to grow
                    int extraLength = snake.apple[i].size * snake.lengthMultiplier;

                    //Can't grow more than the current snake length at once
                    if (extraLength > snake.num2)
                    {
                        extraLength = snake.num2 - 1;
                    }

                    //Score = size
                    snake.score2 += snake.apple[i].size * snake.scoreMultiplier;

                    //Shift snake up
                    for (int ii = snake.num2; ii > 0; ii--)
                    {
                        snake.segment2[ii + extraLength].x = snake.segment2[ii].x;
                        snake.segment2[ii + extraLength].y = snake.segment2[ii].y;
                    }

                    //Extra length = size
                    snake.num2 += extraLength;
                }
            }
        }
    }
}

void snake_checkBites1()
{
    //Look through all apples
    for (int i = 0; i <= snake.maxApples; i++)
    {
        //Find ones that are active
        if(snake.apple[i].active == true)
        {
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
        }
    }
}

bool snake_checkCollisions1()
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

bool snake_checkCollisions1into2()
{   
    bool hitSomething = false;

    //Snake 1 eating 2
    if (snake_checkBlock2(snake.segment[snake.num].x, snake.segment[snake.num].y))
    {
        hitSomething = true;
    }

    //Check for diagonal pass DR
    if ((snake.segment[snake.num].x == snake.segment[snake.num - 1].x + 1) && (snake.segment[snake.num].y == snake.segment[snake.num - 1].y + 1))
    {
        //Check for first matching block
        if (snake_checkBlock2(snake.segment[snake.num].x - 1, snake.segment[snake.num].y))
        {
            if (snake_checkBlock2(snake.segment[snake.num].x, snake.segment[snake.num].y - 1))
            {
                hitSomething = true;
            }
        }
    }

    //Check for diagonal pass UL
    if ((snake.segment[snake.num].x == snake.segment[snake.num - 1].x - 1) && (snake.segment[snake.num].y == snake.segment[snake.num - 1].y - 1))
    {
        //Check for first matching block
        if (snake_checkBlock2(snake.segment[snake.num].x + 1, snake.segment[snake.num].y))
        {
            if (snake_checkBlock2(snake.segment[snake.num].x, snake.segment[snake.num].y + 1))
            {
                hitSomething = true;
            }
        }
    }

    //Check for diagonal pass UR
    if ((snake.segment[snake.num].x == snake.segment[snake.num - 1].x - 1) && (snake.segment[snake.num].y == snake.segment[snake.num - 1].y + 1))
    {
        //Check for first matching block
        if (snake_checkBlock2(snake.segment[snake.num].x - 1, snake.segment[snake.num].y))
        {
            if (snake_checkBlock2(snake.segment[snake.num].x, snake.segment[snake.num].y + 1))
            {
               hitSomething = true;
            }
        }
    }

    //Check for diagonal pass DL
    if ((snake.segment[snake.num].x == snake.segment[snake.num - 1].x + 1) && (snake.segment[snake.num].y == snake.segment[snake.num - 1].y - 1))
    {
        //Check for first matching block
        if (snake_checkBlock2(snake.segment[snake.num].x + 1, snake.segment[snake.num].y))
        {
            if (snake_checkBlock2(snake.segment[snake.num].x, snake.segment[snake.num].y - 1))
            {
               hitSomething = true;
            }
        }
    }

    return hitSomething; 
}

bool snake_checkCollisions2into1()
{   
    bool hitSomething = false;

    //Snake 2 eating 1
    if (snake_checkBlock(snake.segment2[snake.num2].x, snake.segment2[snake.num2].y))
    {
        //Serial.println("2 into 1 - Eating");
        hitSomething = true;
    }

    //Check for diagonal pass DR
    if ((snake.segment2[snake.num2].x == snake.segment2[snake.num2 - 1].x + 1) && (snake.segment2[snake.num2].y == snake.segment2[snake.num2 - 1].y + 1))
    {
        //Check for first matching block
        if (snake_checkBlock(snake.segment2[snake.num2].x - 1, snake.segment2[snake.num2].y))
        {
            if (snake_checkBlock(snake.segment2[snake.num2].x, snake.segment2[snake.num2].y - 1))
            {
                //Serial.println("2 into 1 - DR");
                hitSomething = true;
            }
        }
    }

    //Check for diagonal pass UL
    if ((snake.segment2[snake.num2].x == snake.segment2[snake.num2 - 1].x - 1) && (snake.segment2[snake.num2].y == snake.segment2[snake.num2 - 1].y - 1))
    {
        //Check for first matching block
        if (snake_checkBlock(snake.segment2[snake.num2].x + 1, snake.segment2[snake.num2].y))
        {
            if (snake_checkBlock(snake.segment2[snake.num2].x, snake.segment2[snake.num2].y + 1))
            {
                //Serial.println("2 into 1 - UL");
                hitSomething = true;
            }
        }
    }

    //Check for diagonal pass UR
    if ((snake.segment2[snake.num2].x == snake.segment2[snake.num2 - 1].x - 1) && (snake.segment2[snake.num2].y == snake.segment2[snake.num2 - 1].y + 1))
    {
        //Check for first matching block
        if (snake_checkBlock(snake.segment2[snake.num2].x - 1, snake.segment2[snake.num2].y))
        {
            if (snake_checkBlock(snake.segment2[snake.num2].x, snake.segment2[snake.num2].y + 1))
            {
                //Serial.println("2 into 1 - UR");
                hitSomething = true;
            }
        }
    }

    //Check for diagonal pass DL
    if ((snake.segment2[snake.num2].x == snake.segment2[snake.num2 - 1].x + 1) && (snake.segment2[snake.num2].y == snake.segment2[snake.num2 - 1].y - 1))
    {
        //Check for first matching block
        if (snake_checkBlock(snake.segment2[snake.num2].x + 1, snake.segment2[snake.num2].y))
        {
            if (snake_checkBlock(snake.segment2[snake.num2].x, snake.segment2[snake.num2].y - 1))
            {
                //Serial.println("2 into 1 - DL");
                hitSomething = true;
            }
        }
    }

    return hitSomething; 
}

bool snake_checkCollisions2()
{   
    bool hitSomething = false;

    //Top and Bottom border collision
    if ((snake.segment2[snake.num2].y <= 0) || (snake.segment2[snake.num2].y >= 63))
    {
        hitSomething = true;
    }
    
    //Left and Right border collision
    if ((snake.segment2[snake.num2].x <= 0) || (snake.segment2[snake.num2].x >= 127))
    {
        hitSomething = true;
    }

    //Snake eating itself
    if (snake_checkBlock2(snake.segment2[snake.num2].x, snake.segment2[snake.num2].y))
    {
        hitSomething = true;
    }

    //Check for diagonal pass DR
    if ((snake.segment2[snake.num2].x == snake.segment2[snake.num2 - 1].x + 1) && (snake.segment2[snake.num2].y == snake.segment2[snake.num2 - 1].y + 1))
    {
        //Check for first matching block
        if (snake_checkBlock2(snake.segment2[snake.num2].x - 1, snake.segment2[snake.num2].y))
        {
            if (snake_checkBlock2(snake.segment2[snake.num2].x, snake.segment2[snake.num2].y - 1))
            {
                hitSomething = true;
            }
        }
    }

    //Check for diagonal pass UL
    if ((snake.segment2[snake.num2].x == snake.segment2[snake.num2 - 1].x - 1) && (snake.segment2[snake.num2].y == snake.segment2[snake.num2 - 1].y - 1))
    {
        //Check for first matching block
        if (snake_checkBlock2(snake.segment2[snake.num2].x + 1, snake.segment2[snake.num2].y))
        {
            if (snake_checkBlock2(snake.segment2[snake.num2].x, snake.segment2[snake.num2].y + 1))
            {
                hitSomething = true;
            }
        }
    }

    //Check for diagonal pass UR
    if ((snake.segment2[snake.num2].x == snake.segment2[snake.num2 - 1].x - 1) && (snake.segment2[snake.num2].y == snake.segment2[snake.num2 - 1].y + 1))
    {
        //Check for first matching block
        if (snake_checkBlock2(snake.segment2[snake.num2].x - 1, snake.segment2[snake.num2].y))
        {
            if (snake_checkBlock2(snake.segment2[snake.num2].x, snake.segment2[snake.num2].y + 1))
            {
               hitSomething = true;
            }
        }
    }

    //Check for diagonal pass DL
    if ((snake.segment2[snake.num2].x == snake.segment2[snake.num2 - 1].x + 1) && (snake.segment2[snake.num2].y == snake.segment2[snake.num2 - 1].y - 1))
    {
        //Check for first matching block
        if (snake_checkBlock2(snake.segment2[snake.num2].x + 1, snake.segment2[snake.num2].y))
        {
            if (snake_checkBlock2(snake.segment2[snake.num2].x, snake.segment2[snake.num2].y - 1))
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

bool snake_checkBlock2(int blockCheckX, int blockCheckY)
{
    bool hitTheBlock = false;

    for (int i = 0; i < snake.num2 - 1; i++)
    {
        if ((snake.segment2[i].x == blockCheckX) && (snake.segment2[i].y == blockCheckY))
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
    snake.num2 = 10;
    snake.speed = 3;
    snake.score = 0;
    snake.score2 = 0;
    snake.scoreMultiplier = 8;
    snake.lengthMultiplier = 8;
    snake.maxApples = 2;
    snake.appleRate = 100;
    
    //Set knobs to desired states
    player.X = 12;
    player.Y = 24;
    snake.oldX = player.X;
    snake.oldY = player.Y;

        
    //Calculate snake points
    for (int i = 0; i <= snake.num; i++)
    {
        snake.segment[i].x = SCREEN_WIDTH - i - 10;
        snake.segment[i].y = 32;
    }
    
    //Calculate snake points P2
    for (int i = 0; i <= snake.num2; i++)
    {
        snake.segment2[i].x = 10 + i;
        snake.segment2[i].y = 32;
    }

    //Clear apples
    for (int i = 0; i <= 10; i++)
    {
        snake.apple[i].active = false;
    }
}

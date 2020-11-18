/**************************************************************

Snake! The greatest game ever!

Brian Schimke, 2020
**************************************************************/

void snake_game()
{
    //Add input from the other knob and clear it
    player.X += player.Y;
    player.Y = 0;

    //Make sure we're in range
    if (player.X < 0)
    {
        player.X += 32;
    }
    if (player.X > (31))
    {
        player.X -= 32;
    }

    snake.angle = player.X * - .196;

    //Calculate 1 point on circle
    snake.Xa = snake.X + (6 * sin(snake.angle)) + .5;
    snake.Ya = snake.Y + (6 * cos(snake.angle)) + .5;

    //Draw a line
    u8g2.drawLine(snake.Xa, snake.Ya, snake.X, snake.Y);

    //Calculate Vector Direction
    snake.X += sin(snake.angle) / 5.0;
    snake.Y += cos(snake.angle) / 5.0;

    //Exit on click for testing purposes
    if ((knob1.click == 1) || (knob2.click == 1))
    {
        endGameMode();
    }

}

void snake_reset()
{

}

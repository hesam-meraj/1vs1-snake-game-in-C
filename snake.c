#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <time.h>
#include <string.h>

// gameboard function
void gameboard(int screen_witdh, int screen_height)
{
    for (int x = 0; x <= screen_witdh + 1; x++)
    {
        mvaddch(0, x, '~');                 // top
        mvaddch(screen_height + 1, x, '~'); // bottom
    }

    // draw vertical borders
    for (int y = 0; y <= screen_height + 1; y++)
    {
        mvaddch(y, 0, '#');                // left
        mvaddch(y, screen_witdh + 1, '#'); // right
    }
}





// handle_input function
void handle_input(int pressed, int *dx, int *dy)
{
    if (pressed == KEY_LEFT && *dx != 1) {
        *dx = -1; *dy = 0;
    }
    else if (pressed == KEY_RIGHT && *dx != -1) {
        *dx = 1; *dy = 0;
    }
    else if (pressed == KEY_UP && *dy != 1) {
        *dx = 0; *dy = -1;
    }
    else if (pressed == KEY_DOWN && *dy != -1) {
        *dx = 0; *dy = 1;
    }
}


int main()
{

    while (1)
    {
        int screen_witdh = 40;
        int screen_height = 20;

        // initialize the screen
        WINDOW *win = initscr();
        keypad(win, true);
        nodelay(win, true);
        // hide cursor
        curs_set(0);
        // game setting
        bool gameover = false;

        // snake__1 position
        int score_player1 = 0;
        int snake_posx = 1;
        int snake_posy = 1;
        // direction
        int snake_dirx = 1;
        int snake_diry = 0;


        // snake__2 postion
        int score_player2 = 0;
        int snake2_posx = screen_witdh - 5;
        int snake2_posy = 1;
        // direction
        int snake2_dirx = -1;
        int snake2_diry = 0;






        // food posiotion
        int food_posx = rand() % screen_witdh;
        int food_posy = rand() % screen_height;

        // body 1
        int body_x[500];
        int body_y[500];
        int snake_length = 10; // starts with head only
        // body 2


        int body2_x[500];
        int body2_y[500];
        int snake2_length = 10; // starts with head only



        while (!gameover)
        {
            int pressed = wgetch(win);

            // user input for snake 2
            if (pressed == KEY_LEFT)
            {
                if (snake_dirx == 1)
                    continue;
                snake_dirx = -1;
                snake_diry = 0;
            }
            if (pressed == KEY_RIGHT)
            {
                if (snake_dirx == -1)
                    continue;
                snake_dirx = 1;
                snake_diry = 0;
            }
            if (pressed == KEY_UP)
            {
                if (snake_diry == 1)
                    continue;
                snake_dirx = 0;
                snake_diry = -1;
            }
            if (pressed == KEY_DOWN)
            {
                if (snake_diry == -1)
                    continue;
                snake_dirx = 0;
                snake_diry = 1;
            }
            // second snake ............ 
            if (pressed == 'a')
            {
                if (snake2_dirx == 1)
                    continue;
                snake2_dirx = -1;
                snake2_diry = 0;
            }
            if (pressed == 'd')
            {
                if (snake2_dirx == -1)
                    continue;
                snake2_dirx = 1;
                snake2_diry = 0;
            }
            if (pressed == 'w')
            {
                if (snake2_diry == 1)
                    continue;
                snake2_dirx = 0;
                snake2_diry = -1;
            }
            if (pressed == 's')
            {
                if (snake2_diry == -1)
                    continue;
                snake2_dirx = 0;
                snake2_diry = 1;
            }
            // escape button
            if (pressed == 'e')
            {
                break;
            }

            
            // change in posistion
            int next_x = snake_posx + snake_dirx;
            int next_y = snake_posy + snake_diry;
            // self
            int next2_x = snake2_posx + snake2_dirx;
            int next2_y = snake2_posy + snake2_diry;
            

            // first snake
            for (int i = 0; i < snake_length; i++)
            {
                if (body_x[i] == next_x && body_y[i] == next_y)
                {
                    gameover = true;
                    break;
                }
            }

            if (next_x == screen_witdh + 1 ||
                next_x == 0 ||
                next_y == 0 ||
                next_y == screen_height + 1)
            {
                gameover = true;
                continue;
            }
            else
            {
                snake_posx += snake_dirx;
                snake_posy += snake_diry;
            }


            // second snake
            for (int i = 0; i < snake2_length; i++)
            {
                if (body2_x[i] == next2_x && body2_y[i] == next2_y)
                {
                    gameover = true;
                    break;
                }
            }

            if (next2_x == screen_witdh + 1 ||
                next2_x == 0 ||
                next2_y == 0 ||
                next2_y == screen_height + 1)
            {
                gameover = true;
                continue;
            }
            else
            {
                snake2_posx += snake2_dirx;
                snake2_posy += snake2_diry;
            }


            // first snake
            // update last (new head) position
            // shift body

            if (snake_length >= 2)
            {
                for (int i = 0; i < snake_length - 1; i++)
                {
                    body_x[i] = body_x[i + 1];
                    body_y[i] = body_y[i + 1];
                }
            }
            body_x[snake_length - 1] = snake_posx;
            body_y[snake_length - 1] = snake_posy;

            // first snake
            // update last (new head) position
            // shift body

            if (snake2_length >= 2)
            {
                for (int i = 0; i < snake2_length - 1; i++)
                {
                    body2_x[i] = body2_x[i + 1];
                    body2_y[i] = body2_y[i + 1];
                }
            }
            body2_x[snake2_length - 1] = snake2_posx;
            body2_y[snake2_length - 1] = snake2_posy;


            erase();
            // gameboard
            gameboard(screen_witdh, screen_height);

            // drawing the body and head of the snake1
            for (int i = 0; i < snake_length - 1; i++)
            {
                mvaddstr(body_y[i], body_x[i], "o"); // body
            }
            mvaddstr(body_y[snake_length - 1], body_x[snake_length - 1], "O"); // head

            mvaddstr(food_posy, food_posx, "&");
            if (food_posx == snake_posx && food_posy == snake_posy)
            {
                food_posx = (rand() % (screen_witdh - 1) + 1);
                food_posy = (rand() % (screen_height - 1) + 1);
                score_player1 += 1;

                if (snake_length < 500)
                {
                    body_x[snake_length] = snake_posx;
                    body_y[snake_length] = snake_posy;
                    snake_length += 1; // prevent overflow
                }
            }
            
            
            // drawing the body and head of the snake2
            for (int i = 0; i < snake2_length - 1; i++)
            {
                mvaddstr(body2_y[i], body2_x[i], "x"); // body
            }
            mvaddstr(body2_y[snake2_length - 1], body2_x[snake2_length - 1], "X"); // head

            mvaddstr(food_posy, food_posx, "&");
            if (food_posx == snake2_posx && food_posy == snake2_posy)
            {
                food_posx = (rand() % (screen_witdh - 1) + 1);
                food_posy = (rand() % (screen_height - 1) + 1);
                score_player2 += 1;

                if (snake2_length < 500)
                {
                    body2_x[snake2_length] = snake2_posx;
                    body2_y[snake2_length] = snake2_posy;
                    snake2_length += 1; // prevent overflow
                }
            }

            usleep(100000);

            mvprintw(screen_height + 3, 0, "Score Player 1: %d", score_player1);
            mvprintw(screen_height + 4, 0, "Press e to exit the game!");
        }

        erase();
        mvprintw(screen_height / 2, screen_witdh / 2 - 5, "GAME OVER!");
        mvprintw(screen_height / 2 + 1, screen_witdh / 2 - 12, "Press 'g' to restart or 'e' to exit.");
        refresh();
        nodelay(win, false); // wait for keypress

        // cleaning the left overs of the game before
        for (int i = 0; i < 500; i++)
        {
            body_x[i] = 0;
            body_y[i] = 0;
            body2_x[i] = 0;
            body2_y[i] = 0;
        }

        int restart_key;
        do
        {
            restart_key = wgetch(win);
        } while (restart_key != 'g' && restart_key != 'e');

        if (restart_key == 'e')
            break;
    }
    endwin();

    return 0;
}
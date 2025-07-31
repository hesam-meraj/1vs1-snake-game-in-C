#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <time.h>
#include <string.h>


int main() {

    int screen_witdh= 40;
    int screen_height = 20;

    // initialize the screen 
    WINDOW *win = initscr();
    keypad(win, true);
    nodelay(win, true);
    //hide cursor
   
    curs_set(0);
    // snake position
    int score_player1 = 0;

    int snake_posx = 0;
    int snake_posy = 0;
    // food posiotion

    int food_posx = rand() % screen_witdh;
    int food_posy = rand() % screen_height;
    // direction
    int snake_dirx = 1;
    int snake_diry = 0;

    // body 
    int body_x[500];
    int body_y[500];
    int snake_length = 1; // starts with head only


    while (1)
    {
        int pressed = wgetch(win);

        // user input for snake 2
        if (pressed == KEY_LEFT){
            if(snake_dirx == 1) continue;
            snake_dirx = -1; snake_diry = 0;}
        if (pressed == KEY_RIGHT){
            if(snake_dirx == -1) continue;
            snake_dirx = 1; snake_diry = 0;}
        if (pressed == KEY_UP){
            if(snake_diry == 1) continue;
            snake_dirx = 0; snake_diry = -1;}
        if (pressed == KEY_DOWN){
            if(snake_diry == -1) continue;
            snake_dirx = 0; snake_diry = 1;}
        // escape button
        if (pressed == 'e'){break;}
     

        // change in posistion
        snake_posx += snake_dirx;
        snake_posy += snake_diry;

        
        
        // update last (new head) position

        
        // shift body

        if (snake_length >= 2) {
            for (int i = 0; i < snake_length - 1; i++) {
                body_x[i] = body_x[i + 1];
                body_y[i] = body_y[i + 1];
            }
        }
        body_x[snake_length - 1] = snake_posx;
        body_y[snake_length - 1] = snake_posy;




        
        
        erase();
        for (int i = 0; i < snake_length - 1; i++) {
            mvaddstr(body_y[i], body_x[i], "o"); // body
        }
        mvaddstr(body_y[snake_length - 1], body_x[snake_length - 1], "O"); // head

        
        mvaddstr(food_posy , food_posx, "&");
        if (food_posx == snake_posx && food_posy == snake_posy)
        {
            food_posx = rand() % screen_witdh;
            food_posy = rand() % screen_height;
            score_player1 += 1;
            if (snake_length < 100) snake_length += 1; // prevent overflow


            
        }
        

        usleep(100000);


    }
    
    
    endwin();
    
    return 0;
}
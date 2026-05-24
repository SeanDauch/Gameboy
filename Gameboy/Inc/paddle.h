#ifndef _paddle_h
    #define _paddle_h

    typedef struct{
        int x;
        int y;

        int length;

        int last_y_pos;
    }paddle;

    void print_paddle(paddle* game_paddle, char color);
    paddle paddle_init(int center_x, int center_y, int length);
    void move_paddle(paddle* game_paddle, int speed);
#endif
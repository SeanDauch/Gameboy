#ifndef _paddle_h
    #define _paddle_h

    typedef struct{
        int x;
        int y;

        int length;
    }paddle;

    paddle paddle_init(int center_x, int center_y, int length);
    void move_paddle(paddle* game_paddle, int speed);
#endif
#ifndef _game_h
    #define _game_h

    #include "ball.h"
    #include "paddle.h"

    typedef struct pong_game{
        ball game_ball;

        paddle p1_paddle;
        paddle p2_paddle;
    }pong_game;

    pong_game game_init(int ball_size, int paddle_length);
    void play_game(pong_game* my_game);
#endif
#ifndef _game_h
    #define _game_h

    #include "ball.h"
    #include "paddle.h"

    typedef struct game{
        ball* game_ball;

        paddle* p1_paddle;
        paddle* p2_paddle;
    }game;

    game game_init(int ball_size, int paddle_length);
    void play_game(game* my_game);
#endif
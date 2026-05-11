#ifndef _ball_h
    #define _ball_h

    typedef struct{
        int top_left_x;
        int top_left_y;

        int bot_right_x;
        int bot_right_y;

        int velocity_x;
        int velocity_y;
    }ball;

    typedef struct game game; 

    void move_ball(game* game_game);

    ball bouncing_ball_init(int ball_center_x, int ball_center_y, int sizeof_ball);

#endif
#include "ball.h"
#include "ILI9341_driver.h"
#include "main.h"

void print_ball(ball* game_ball, char color){

    draw_Square(game_ball->top_left_y,
        game_ball->bot_right_y,
        game_ball->top_left_x,
        game_ball->bot_right_x,
        color
    );
}

// returns pointer
ball bouncing_ball_init(int ball_center_x, int ball_center_y, int ball_size){

    ball game_ball = {
        ball_center_x - ball_size, // top left x
        ball_center_y - ball_size, // top left y
        ball_center_x + ball_size, // bot right x
        ball_center_y + ball_size, // bot right y
        3, 3
    };

    print_ball(&game_ball, 'b');

    return game_ball;
}

void ball_bounce_edge(ball* game_ball){
    if(game_ball->top_left_x <= 0){ // check left
        game_ball -> velocity_x *= -1;
    } 
    
    if(game_ball->top_left_y <= 0){ // check top
        game_ball -> velocity_y *= -1;
    }
    
    if(game_ball->bot_right_x >= max_rows){ // check right
        game_ball -> velocity_x *= -1;
    }
    
    if(game_ball->bot_right_y >= max_cols){ // check bottom
        game_ball -> velocity_y *= -1;
    }
}

void move_ball(ball* game_ball){

    // erase old ball
    print_ball(game_ball, 'w');

    // shift ball over
    game_ball->top_left_x += game_ball->velocity_x;
    game_ball->bot_right_x += game_ball->velocity_x;

    game_ball->top_left_y += game_ball->velocity_y;
    game_ball->bot_right_y += game_ball->velocity_y;

    ball_bounce_edge(game_ball);

    print_ball(game_ball, 'b');
}
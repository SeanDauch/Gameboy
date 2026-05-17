#include "ball.h"
#include "ILI9341_driver.h"
#include "main.h"
#include "adc_drivers.h"

#include <stdlib.h>

void print_ball(ball* game_ball, char color){
    //fill_screen('w');// ! delete
    draw_Square(game_ball->top_left_y,
        game_ball->bot_right_y,
        game_ball->top_left_x,
        game_ball->bot_right_x,
        color
    );
    //fill_screen('b');// ! delete
}

// returns pointer
ball bouncing_ball_init(int ball_center_x, int ball_center_y, int ball_size){

    int velo_y = 0;
    int velo_x = 0;
    int random = 0;

    srand(adc_regular_conversion());
    random = rand() % 4;

    switch (random){
    case 0:
        velo_x = 1;
        velo_y = 1;
        break;

    case 1:
        velo_x = -1;
        velo_y = 1;
        break;

    case 2:
        velo_x = -1;
        velo_y = -1;
        break;

    case 3:
        velo_x = 1;
        velo_y = -1;
        break;
    }
    



    ball game_ball = {
        ball_center_x - ball_size, // top left x
        ball_center_y - ball_size, // top left y
        ball_center_x + ball_size, // bot right x
        ball_center_y + ball_size, // bot right y
        velo_x, velo_y
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

    print_ball(game_ball, 'b');
}
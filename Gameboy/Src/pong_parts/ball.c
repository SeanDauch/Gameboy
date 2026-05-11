#include "ball.h"
#include "ILI9341_driver.h"
#include "main.h"
#include "paddle.h"
#include "pong.h"

void print_ball(ball* game_ball, char color){

    draw_Square(game_ball->top_left_x,
        game_ball->bot_right_x,
        game_ball->top_left_y,
        game_ball->bot_right_y,
        color
    );
}

// returns pointer
ball bouncing_ball_init(int ball_center_row, int ball_center_col, int ball_size){

    ball game_ball = {
        ball_center_row - ball_size, // top left x
        ball_center_col - ball_size, // top left y
        ball_center_row + ball_size, // bot right x
        ball_center_col + ball_size, // bot right y
        1, 1
    };

    print_ball(&game_ball, 'b');

    return game_ball;
}

void ball_bounds(game* game_game){
    if(game_game->game_ball->top_left_x == game_game->p1_paddle->x && 
        (game_game->game_ball->top_left_y <= (game_game->p1_paddle->y + game_game->p1_paddle->length) && 
        game_game->game_ball->bot_right_y >= (game_game->p1_paddle->y - game_game->p1_paddle->length))){ // check left paddle

        game_game->game_ball -> velocity_x *= -1;
    } 
    
    if(game_game->game_ball->top_left_y <= 0){ // check top
        game_game->game_ball -> velocity_y *= -1;

    }
    
    if(game_game->game_ball->bot_right_x == game_game->p2_paddle->x && 
        (game_game->game_ball->top_left_y <= (game_game->p2_paddle->y + game_game->p2_paddle->length) && 
        game_game->game_ball->bot_right_y >= (game_game->p2_paddle->y - game_game->p2_paddle->length))){ // check right

        game_game->game_ball -> velocity_x *= -1;
    }
    
    if(game_game->game_ball->bot_right_y >= max_rows){ // check bottom
        game_game->game_ball -> velocity_y *= -1;
    }
}

void move_ball(game* game_game){

    // erase old ball
    print_ball(game_game->game_ball, 'w');

    // shift ball over
    game_game->game_ball->top_left_x += game_game->game_ball->velocity_x;
    game_game->game_ball->bot_right_x += game_game->game_ball->velocity_x;
    
    game_game->game_ball->top_left_y += game_game->game_ball->velocity_y;
    game_game->game_ball->bot_right_y += game_game->game_ball->velocity_y;

    ball_bounds(game_game);

    print_ball(game_game->game_ball, 'b');
}
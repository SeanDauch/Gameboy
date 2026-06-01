#include "ILI9341_driver.h"
#include "main.h"
#include "paddle.h"

void print_paddle(paddle* game_paddle, char color){

    draw_Square(
        game_paddle -> y - game_paddle -> length,
        game_paddle -> y + game_paddle -> length,

        // give the paddle a little girth
        game_paddle -> x-2,
        game_paddle -> x+2,

        color
    );
}

paddle paddle_init(int center_x, int center_y, int length){
    paddle game_paddle = {center_x, center_y, length, center_x};

    print_paddle(&game_paddle, sprite_color);

    return game_paddle;
} 

void move_paddle(paddle* game_paddle, int speed){

    // erase old paddle
    print_paddle(game_paddle, background_color);

    // set last_y_pos
    game_paddle->last_y_pos = game_paddle->y;

    // shift paddle over
    game_paddle->y += speed;

    if(game_paddle->y + game_paddle->length > max_cols){ // bottom
        game_paddle->y = max_cols - game_paddle->length;

    }else if(game_paddle->y - game_paddle->length < 0){ // top
        game_paddle->y =  game_paddle->length;
    }

    print_paddle(game_paddle, sprite_color);
}
#include "ILI9341_driver.h"
#include "main.h"
#include "paddle.h"

void print_paddle(paddle* game_paddle, char color){
    draw_Square(
        game_paddle -> y - game_paddle -> length,
        game_paddle -> y + game_paddle -> length,

        game_paddle -> x,
        game_paddle -> x,

        color
    );
}

paddle paddle_init(int center_x, int center_y, int length){
    paddle game_paddle = {center_x, center_y, length};

    print_paddle(&game_paddle, 'b');

    return game_paddle;
} 

void move_paddle(paddle* game_paddle, int speed){
    // erase old paddle
    print_paddle(game_paddle, 'w');

    // shift paddle over
    game_paddle->y += speed;

    if(game_paddle->y + game_paddle->length > max_cols){ // bottom
        game_paddle->y = max_cols - game_paddle->length;

    }else if(game_paddle->y - game_paddle->length < 0){ // top
        game_paddle->y =  game_paddle->length;
    }

    print_paddle(game_paddle, 'b');
}
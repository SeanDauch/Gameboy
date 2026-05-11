#include "pong.h"
#include "main.h"
#include "Delay.h"
#include "ILI9341_driver.h"
#include "ball.h"
#include "paddle.h"
#include <stdint.h>

#define RCC_AHB1ENR *((volatile uint32_t*) (0x40023830))
#define GPIOA_MODER *((volatile uint32_t*) (0x40020000))
#define GPIOA_PUPDR *((volatile uint32_t*) (0x4002000C))
#define GPIOA_IDR *((volatile uint32_t*) (0x40020010))

#define paddle_speed 1

game game_init(int ball_size, int paddle_length){
    paddle p1 = paddle_init(10, max_cols/2, paddle_length);
    paddle p2 = paddle_init(max_rows - 10, max_cols/2, paddle_length);

    ball game_ball = bouncing_ball_init(max_rows/2, max_cols/2, 10);

    game my_game = {&game_ball, &p1, &p2};

    RCC_AHB1ENR |= 1<<0;
    GPIOA_MODER &= ~((3 << 20) | (3 << 22) | (3 << 24) | (3 << 30));

    GPIOA_PUPDR &= ~((3 << 20) | (3 << 22) | (3 << 24) | (3 << 30));
    GPIOA_PUPDR |=  ((2 << 20) | (2 << 22) | (2 << 24) | (2 << 30));

    return my_game;
}

void play_game(game* my_game){

    int play = 1;
    while(play == 1){
        move_ball(my_game);

        if(GPIOA_IDR & (1<<10)){
            move_paddle(my_game->p1_paddle,1);

        }else if(GPIOA_IDR & (1<<11)){
            move_paddle(my_game->p1_paddle,-1);

        }

        if(GPIOA_IDR & (1<<12)){
            move_paddle(my_game->p2_paddle,1);

        }else if(GPIOA_IDR & (1<<15)){
            move_paddle(my_game->p2_paddle,-1);

        }

        if(my_game->game_ball->bot_right_x >= max_rows){ // p1 wins
            play = 0;

        }else if(my_game->game_ball->top_left_x <= 0){ // p2 wins
            play = 0;
        }
    }

    fill_screen('b');
}
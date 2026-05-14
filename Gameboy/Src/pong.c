#include "pong.h"
#include "main.h"
#include "Delay.h"
#include "ILI9341_driver.h"
#include "ball.h"
#include "paddle.h"
#include <stdint.h>

#define RCC_Base 0x40023800
#define RCC_AHB1ENR *((volatile uint32_t*)(RCC_Base + 0x30))

#define GPIOB_base 0x40020400
#define GPIOB_MODER *((volatile uint32_t*)(GPIOB_base))
#define GPIOB_PUPDR *((volatile uint32_t*)(GPIOB_base + 0x0C))
#define GPIOB_IDR *((volatile uint32_t*)(GPIOB_base + 0x10))

#define paddle_speed 1

pong_game game_init(ball* game_ball, paddle* p1, paddle* p2){

    pong_game my_game = {game_ball, p1, p2};

    RCC_AHB1ENR |= 1<<1;

    // input mode
    GPIOB_MODER &= ~((3 << 8) | (3 << 10) | (3 << 12) | (3 << 14) | (3 << 16) | (3 << 18));

    // pull down
    GPIOB_PUPDR &= ~((3 << 8) | (3 << 10) | (3 << 12) | (3 << 14) | (3 << 16) | (3 << 18));
    GPIOB_PUPDR |=  (2 << 8) | (2 << 10) | (2 << 12) | (2 << 14) | (2 << 16) | (2 << 18);

    return my_game;
}

int is_paddle_in_ball(ball* game_ball, paddle* paddle){
    int paddle_top_y = paddle->y - paddle -> length;
    int paddle_bot_y = paddle->y + paddle -> length;

    if(paddle->x <= game_ball->bot_right_x && paddle->x >= game_ball->top_left_x){ // if x coords line up 
        if(paddle_top_y <= game_ball->top_left_y || paddle_top_y <= game_ball->bot_right_y){ // if ball is lower than top paddle
            if(paddle_bot_y >= game_ball->top_left_y || paddle_bot_y >= game_ball->bot_right_y){ // if ball is higher than bot paddle
                return 1;
            }
        } 
    }

    return 0;
}

void ball_bounce_paddle(pong_game* my_game){

    if(is_paddle_in_ball(my_game -> game_ball, my_game -> p1_paddle)){

        my_game->game_ball->velocity_x *= -1; // double speed oposite x
        my_game->game_ball->velocity_x += 1;
        //my_game->game_ball->velocity_y *= 2;

    }else if(is_paddle_in_ball(my_game -> game_ball, my_game -> p2_paddle)){

        my_game->game_ball->velocity_x *= -1; // double speed oposite x
        my_game->game_ball->velocity_x += -1;
        //my_game->game_ball->velocity_y *= 2;

    }
}

void play_game(pong_game* my_game){

    int play = 1;
    while(play == 1){
        move_ball(my_game->game_ball);
        ball_bounce_edge(my_game->game_ball);
        ball_bounce_paddle(my_game);


        if(GPIOB_IDR & (1<<6)){ // p1 up
            move_paddle(my_game->p1_paddle,-3);

        }else if(GPIOB_IDR & (1<<5)){ // p1 down
            move_paddle(my_game->p1_paddle,3);

        }else{
            print_paddle(my_game->p1_paddle, 'b');
        }

        if(GPIOB_IDR & (1<<8)){ // p2 up
            move_paddle(my_game->p2_paddle,-3);

        }else if(GPIOB_IDR & (1<<9)){ // p2 down
            move_paddle(my_game->p2_paddle,3);

        }else{
            print_paddle(my_game->p2_paddle, 'b');
        }

        if(my_game->game_ball->bot_right_x >= max_rows){ // p1 wins
            play = 0;

        }else if(my_game->game_ball->top_left_x <= 0){ // p2 wins
            play = 0;
        }
        delay_SysTick(20, system_frequency);
    }

    fill_screen('b');
}
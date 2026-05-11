#include "main.h"
#include "ILI9341_driver.h"
#include "pong.h"
#include "ball.h"
#include "Delay.h"

#include <stdint.h>

// trying to set to 20MHz
void clock_init(){

    // wait for HSI ready flag
    while(!(RCC_CR & (1<<1))){}

    // enable HSI
    RCC_CR |= (1<<0);

    /* working on PLL 
        F_pll = F_vco /pllp
        F_vco = vco_in * (plln)
        vco_in = F_in / pllm */

        // set HSI as vco source (16MHz)
        RCC_PLLCFGR &= ~(1<<22);

        // pllm, configure vco_in (ideally 2MHz)
        RCC_PLLCFGR &= ~(0x3F<<0); // 0b111111
        RCC_PLLCFGR |= (8<<0);

        // set plln (50<= plln <= 432) F_vco must be >100 and <432
        RCC_PLLCFGR &= ~(0x1FF<<6); // 0b111111111
        RCC_PLLCFGR |= (80<<6);

        // set pllp
        RCC_PLLCFGR &= ~(3<<16);
        RCC_PLLCFGR |= (3<<16); // 0b11
    
    // wait for PLL to be ready
    while(RCC_CR & (1<<25)){}

    // enable PLL
    RCC_CR |= (1<<24);

    // set PLL as system clock
    RCC_CFGR &= ~(3<<0);
    RCC_CFGR |= (2<<0);




}


int main(){
    ILI9341_Init();

    fill_screen('w');

    //draw_Square(0,100, 0, 200, 'b');

    ball my_ball = bouncing_ball_init(max_rows/2, max_cols/2, 5);

	while(1){
        move_ball(&my_ball);

        delay_SysTick(20, system_frequency);

    }

    return 0;
}

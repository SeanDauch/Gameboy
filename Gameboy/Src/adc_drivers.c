#include "adc_drivers.h"

#include <stdint.h>

#define RCC_Base 0x40023800
#define RCC_APB2ENR *((volatile uint32_t*)(RCC_Base + 0x44))

#define ADC1_Base 0x40012000
#define ADC_SR *((volatile uint32_t*)(ADC1_Base + 0x00))
#define ADC_CR1 *((volatile uint32_t*)(ADC1_Base + 0x04))
#define ADC_CR2 *((volatile uint32_t*)(ADC1_Base + 0x08))
#define ADC_SQR1 *((volatile uint32_t*)(ADC1_Base + 0x2c))
#define ADC_SQR2 *((volatile uint32_t*)(ADC1_Base + 0x30))
#define ADC_SQR3 *((volatile uint32_t*)(ADC1_Base + 0x34))
#define ADC_DR *((volatile uint32_t*)(ADC1_Base + 0x4c))

#define GPIOA_Base 0x40020000
#define GPIOA_MODER *((volatile uint32_t*)(GPIOA_Base + 0x00))

void adc_GPIOA_init(uint8_t pin_number){

    // set pin to analog mode
    GPIOA_MODER |= (3<<(2*pin_number));
}

// 0-18 ADC channels
void adc_init(uint8_t ADC_channel_go_first){

    // turn on ADC1 clock
    RCC_APB2ENR |= (1<<8);

    // turn ADC on
    ADC_CR2 |= (1<<0);

    // tells how many ADC channels need converting
    ADC_SQR1 &= ~(0xf<<20); // 0b0000 means 1 conversion

    // put the channel to go first
    ADC_SQR3 |= (ADC_channel_go_first<<0);

    // set resolution to 12 bits
    ADC_CR1 &= ~(3<<24);

    // make sure right alignment
    ADC_CR2 &= ~(1<<11);

}

uint16_t adc_regular_conversion(){

    // make sure there is no other conversion happening
    while(ADC_SR & (1<<4)){}

    // start conversion of regular channels
    ADC_CR2 |= (1<<30);

    // wait for end of conversion
    while(!(ADC_SR & (1<<1))){}

    // read data register
    uint16_t data = ADC_DR;

    //set regular channel start flag low
    ADC_SR &= ~(1<<4);

    return data;
}
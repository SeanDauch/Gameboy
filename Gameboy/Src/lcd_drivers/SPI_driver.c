#include "SPI_driver.h"
#include <stdint.h>


#define RCC_Base 0x40023800
#define RCC_APB2ENR *((volatile uint32_t*)(RCC_Base + 0x44))
#define RCC_AHB1ENR *((volatile uint32_t*)(RCC_Base + 0x30))

#define GPIOA_Base 0x40020000
#define GPIOA_MODER *((volatile uint32_t*)(GPIOA_Base + 0x00))
#define GPIOA_OSPEEDR *((volatile uint32_t*)(GPIOA_Base + 0x08))
#define GPIOA_ODR *((volatile uint32_t*)(GPIOA_Base + 0x14))
#define GPIOA_AFRL *((volatile uint32_t*)(GPIOA_Base + 0x20))

#define SPI1_Base 0x40013000
#define SPI_CR1 *((volatile uint32_t*)(SPI1_Base + 0x00))
#define SPI_SR *((volatile uint32_t*)(SPI1_Base + 0x08))
#define SPI_DR *((volatile uint32_t*)(SPI1_Base + 0x0C))



void spi1_gpioinit(){
    // enable clock for GPIO A
    RCC_AHB1ENR |= (1<<0);

    // enable PA7,6,5 in alt function
    GPIOA_MODER &= ~((3<<10)|(3<<12)|(3<<14));
    GPIOA_MODER |= (2<<10)|(2<<12)|(2<<14);

    // enable A0 as output for CS
    GPIOA_MODER &= ~(3<<0);
    GPIOA_MODER |= (1<<0);

    // set P7,6,5,0 to high speed
    GPIOA_OSPEEDR |= (3<<0)|(3<<10)|(3<<12)|(3<<14);

    // enable PA7,6,5 in SPI1(AF5 = 0b0101)
    GPIOA_AFRL &= ~((15<<20)|(15<<24)|(15<<28));
    GPIOA_AFRL |= (5<<20)|(5<<24)|(5<<28);
    GPIOA_AFRL &= ~((15<<20)|(15<<24)|(15<<28));
    GPIOA_AFRL |= (5<<20)|(5<<24)|(5<<28);
}

void spi1_config(){
    // enable clock for spi1
    RCC_APB2ENR |= (1<<12);

    // make sure DFF in in 8 bits
    SPI_CR1 &= ~(1<<11);

    // set MCU to be master
    SPI_CR1 |= (1<<2);

    // SSM/SSI: allows us to pull the CS pin oursleves
    SPI_CR1 |= (1<<9); 
    SPI_CR1 |= (1<<8);

    // set the baud rate scaler to 1/2
    SPI_CR1 &= ~(0b111<<3);

    //enable spi module
    SPI_CR1 |= (1<<6);
}

// array of 8-bit data with size data_size
void spi1_send(uint8_t *data, uint32_t data_size){
    uint8_t temp;

    for(int i = 0; i<data_size ; i++){
        
        // wait for send buffer to empty
        while(!(SPI_SR & (1<<1))){}

        // write data to data register
        SPI_DR = data[i];

        // wait for recieve buffer to be full
        while(!(SPI_SR & (1<<0))){} 

        // clear data register
        temp = SPI_DR;
        (void)temp;
    }

    // wait for BSY flag to reset
    while(SPI_SR & (1<<7)){}
}

// array of 8-bit data with size data_size
void spi1_receive(uint8_t *data, uint32_t data_size){
    for(int i = 0; i<data_size; i++){
        // set dummy data for clock pulses
        SPI_DR = 0;

        // wait for receive buffer to be full
        while (!(SPI_SR & (1<<0))){}

        data[i] = SPI_DR;
        
    }
}

void CS_enable(){
    GPIOA_ODR &= ~(1<<0);
}

void CS_disable(){
    GPIOA_ODR |= (1<<0);
}
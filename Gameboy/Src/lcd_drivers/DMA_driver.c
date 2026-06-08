#include <stdint.h>

// spi1_TX is in dma2 stream2 channel2
#define DMA2_base 0x40026400
#define DMA_LISR *((volatile uint32_t*)(DMA2_base + 0x00))
#define DMA_LIFCR *((volatile uint32_t*)(DMA2_base + 0x08))
#define DMA_S2CR *((volatile uint32_t*)(DMA2_base + 0x10 + (0x18 * 2))) // 0x10 + (0x18 * streamnumber)
#define DMA_S2NDTR *((volatile uint32_t*)(DMA2_base + 0x14 + (0x18 * 2))) // 0x14 + (0x18 * streamnumber)
#define DMA_S2PAR *((volatile uint32_t*)(DMA2_base + 0x18 + (0x18 * 2))) // 0x18 + (0x18 * streamnumber)
#define DMA_S2M0AR *((volatile uint32_t*)(DMA2_base + 0x1C + (0x18 * 2)))

#define SPI1_base 0x40013000
#define SPI_DR *((volatile uint32_t*)(SPI1_base + 0x0C))
#define SPI_CR2 *((volatile uint32_t*)(SPI1_base + 0x04))

#define RCC_base 0x40023800
#define RCC_AHB1RSTR *((volatile uint32_t*)(RCC_base + 0x10))
#define RCC_AHB1ENR *((volatile uint32_t*)(RCC_base + 0x30))

void DMA2_init(){

    RCC_AHB1RSTR |= (1<<22); // reset DMA2
    RCC_AHB1RSTR &= ~(1<<22);

    RCC_AHB1ENR |= (1<<22); // enable DMA2 clock

    SPI_CR2 |= (1<<1); // Tx buffer DMA enable
}

// 9.3.17 in refrence manual had config procedure
void DMA2_SPI1_config_s2c2(uint8_t data_start, uint16_t data_length){

    // 1. disable/reset stream
    DMA_S2CR &= ~(1<<0);
    while(DMA_S2CR & (1<<0)){} // wait for transfer to finish
    DMA_LIFCR = (1<<16) | (15<<18); // clear all interupt flags

    // 2. set the peripheral port register address to SPI1_DR
    DMA_S2PAR = 0;
    DMA_S2PAR = (uint32_t)&SPI_DR;

    // 3. set inital memory address
    DMA_S2M0AR = (uint32_t)&data_start;

    // 4. set length of transfer
    DMA_S2NDTR = data_length;

    // 5. set channel 2
    DMA_S2CR &= ~(7<<25);
    DMA_S2CR |= (2<<25);

    // 6. set DMA as flow controller
    DMA_S2CR &= ~(1<<5);

    // 7. set DMA priority level (doesnt matter rn)
    //DMA_S2CR = (3<<17);

    // 8. FIFO buffer

    // 9. activate the rest of the stuff
    DMA_S2CR &= ~(1<<10); // fixed memory address pointer
    DMA_S2CR |= (1<<6); // memory to peripheral
    //DMA_S2CR |= (1<<11); // set peripheral data size to 16 bits


    // 10. enable DMA 
    DMA_S2CR |= (1<<0);
}

uint8_t DMA_busy(){
    return DMA_S2CR & (1<<0);
}
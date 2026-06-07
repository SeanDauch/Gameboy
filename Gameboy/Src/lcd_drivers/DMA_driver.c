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

// 9.3.17 in refrence manual had config procedure
void DMA2_SPI1_config_s2c2(){

    // disable stream
    DMA_S2CR &= ~(1<<0);
    while(DMA_S2CR & (1<<0)){} // wait for transfer to finish

    // clear all interupt flags
    DMA_LIFCR &= ~((1<<16) | (15<<18));

    // set the peripheral port register address to SPI1_DR
    DMA_S2PAR = &SPI_DR;

    // !figure out MA0R
    DMA_S2M0AR = ;

    // 
}

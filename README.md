# LCD "Gameboy"
Uses STM32F411ceu6

### To Do:
1. ~~Make SPI driver - DONE~~
2. ~~Use spi to make lcd drivers - DONE~~
   - ~~Decide if we need DMA - Dont have time~~
3. ~~Make game - PONG~~
   - ~~make bouncing box - DONE~~
     - ~~make ball struct~~
       - ~~has a/y/dx/dy~~
     - ~~create fuction for drawing~~
     - ~~add if statement for boundries~~
   - ~~add user input to make pong - DONE~~
     - ~~make paddle struct~~
       - ~~has x/y~~
     - ~~create fuction for drawing~~
     - ~~add if statements for paddle colision~~
4. ~~Make a SWO driver to test ADC and printf~~ (Use debug menu instead, printf debugging stinks)
   - ~~create SWO_init using altfunction and ITM~~
   - ~~provide declaration for __io_putchar(*ptr++);~~
   - ~~test swo_drivers with openOCD~~
5. Use ADC to seed rand

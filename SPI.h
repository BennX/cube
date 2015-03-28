/*
* SPI.h
*
* Created: 16.12.2014 11:21:35
* Author: Benjamin
*/


#ifndef __SPI_H__
#define __SPI_H__

#include<avr/io.h>

//DDR = Data direction register
//PORT = use for output if configured as output
// PORT to enable all pullups if input
#define DDR_SPI DDRB
#define DD_MISO DDB6
#define DD_MOSI DDB5
#define DD_SCK DDB7
#define DD_SS DDB4
class SPI
{
public:
    static inline void init();
    static inline void transmit(const unsigned char &data);

private:
    SPI();
    ~SPI();
    SPI( const SPI &c );
    SPI &operator=( const SPI &c );
}; //SPI

inline void SPI::init()
{
    //set SS pin to output befor so it is handled as usual output
    DDRB |= (1 << DDB4);
    //make the pins a output mosi and sck
    DDR_SPI |= (1 << DD_MOSI) | (1 << DD_SCK);
    //1<<spe = enable spi, 1<<mstr = master, leave the SPR1 and SPR0 0 so the prescaler will be 2;
    SPCR |= (1 << SPE) | (1 << MSTR);
    //1<<SPI2X = Frequenz/2 speed
    //wenn SPI2X gesetzt ist verdoppelt sich die geschwindigkeit von SPCR
    // ist anderes register aös SPCR!
    SPSR  |= (1 << SPI2X);
}

inline void SPI::transmit(const unsigned char &data)
{
    SPDR = data; //data register
    while(!(SPSR & (1 << SPIF)))
        ; //wait till transmitted
    return;
}
#endif //__SPI_H__

/*
 * Temperatur.cpp
 *
 * Created: 12.04.2015 17:10:44
 *  Author: Benjamin
 */
#include "Temperatur.h"

void Temperatur::get(char *buffer)
{
    double d = get();
    dtostrf(d, 5, 3, buffer);
}

uint8_t Temperatur::reset()
{
    uint8_t i;

    //low for 480us
    DS18B20_PORT &= ~ (1 << DS18B20_DQ); //low
    DS18B20_DDR |= (1 << DS18B20_DQ); //output
    _delay_us(480);

    //release line and wait for 60uS
    DS18B20_DDR &= ~(1 << DS18B20_DQ); //input
    _delay_us(60);

    //get value and wait 420us
    i = (DS18B20_PIN & (1 << DS18B20_DQ));
    _delay_us(420);

    //return the read value, 0=ok, 1=error
    return i;
}

void Temperatur::write_bit(uint8_t bit)
{
    //low for 1uS
    DS18B20_PORT &= ~ (1 << DS18B20_DQ); //low
    DS18B20_DDR |= (1 << DS18B20_DQ); //output
    _delay_us(1);

    //if we want to write 1, release the line (if not will keep low)
    if(bit)
        DS18B20_DDR &= ~(1 << DS18B20_DQ); //input

    //wait 60uS and release the line
    _delay_us(60);
    DS18B20_DDR &= ~(1 << DS18B20_DQ); //input
}

void Temperatur::write_byte(uint8_t byte)
{
    uint8_t i = 8;
    while(i--)
    {
        write_bit(byte & 1);
        byte >>= 1;
    }
}

uint8_t Temperatur::read_bit()
{
    uint8_t bit = 0;

    //low for 1uS
    DS18B20_PORT &= ~ (1 << DS18B20_DQ); //low
    DS18B20_DDR |= (1 << DS18B20_DQ); //output
    _delay_us(1);

    //release line and wait for 14uS
    DS18B20_DDR &= ~(1 << DS18B20_DQ); //input
    _delay_us(14);

    //read the value
    if(DS18B20_PIN & (1 << DS18B20_DQ))
        bit = 1;

    //wait 45uS and return read value
    _delay_us(45);
    return bit;
}

uint8_t Temperatur::read_byte()
{
    uint8_t i = 8, n = 0;
    while(i--)
    {
        n >>= 1;
        n |= (read_bit() << 7);
    }
    return n;
}

double Temperatur::get()
{

    uint8_t temperature[2];
    int8_t digit;
    uint16_t decimal;
    double retd = 0;
    cli();
    reset(); //reset
    write_byte(DS18B20_CMD_SKIPROM); //skip ROM
    write_byte(DS18B20_CMD_CONVERTTEMP); //start temperature conversion

    while(!read_bit()); //wait until conversion is complete

    reset(); //reset
    write_byte(DS18B20_CMD_SKIPROM); //skip ROM
    write_byte(DS18B20_CMD_RSCRATCHPAD); //read scratchpad

    //read 2 byte from scratchpad
    temperature[0] = read_byte();
    temperature[1] = read_byte();

    reset(); //reset
    sei();
    //store temperature integer digits
    digit = temperature[0] >> 4;
    digit |= (temperature[1] & 0x7) << 4;

    //store temperature decimal digits
    decimal = temperature[0] & 0xf;
    decimal *= DS18B20_DECIMALSTEPS;

    //compose the double temperature value and return it
    retd = digit + decimal * 0.0001;

    return retd;
}
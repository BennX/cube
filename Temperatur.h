/*
 * Themperatur.h
 *
 * Created: 11.03.2015 16:30:05
 *  Author: Benjamin
 */
#ifndef __THEMPERATURE_H__
#define __THEMPERATURE_H__

#define F_CPU 22118400
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>

//setup connection
#define DS18B20_PORT PORTC
#define DS18B20_DDR DDRC
#define DS18B20_PIN PINC
#define DS18B20_DQ PINC0

#define THERM_DECIMAL_STEPS_12BIT 625 //0.0625
#define DS18B20_DECIMALSTEPS THERM_DECIMAL_STEPS_12BIT
//commands
#define DS18B20_CMD_CONVERTTEMP 0x44
#define DS18B20_CMD_RSCRATCHPAD 0xbe
#define DS18B20_CMD_WSCRATCHPAD 0x4e
#define DS18B20_CMD_CPYSCRATCHPAD 0x48
#define DS18B20_CMD_RECEEPROM 0xb8
#define DS18B20_CMD_RPWRSUPPLY 0xb4
#define DS18B20_CMD_SEARCHROM 0xf0
#define DS18B20_CMD_READROM 0x33
#define DS18B20_CMD_MATCHROM 0x55
#define DS18B20_CMD_SKIPROM 0xcc
#define DS18B20_CMD_ALARMSEARCH 0xec

class Temperatur
{
public:
    /**
     * Automatically convert into a string length of 5 with 3 digits after the dot
     */
    static inline void get(char *buffer);
    /**
     * Returns the temperature double.
     * Interupt safe access to the temperature sensor.
     * No interupts while getting and so on!
     * While converting interupts are fine
     */
    static inline double get();
private:
    static inline uint8_t reset();
    static inline void write_bit(uint8_t bit);
    static inline void write_byte(uint8_t bit);
    static inline uint8_t read_bit();
    static inline uint8_t read_byte();
};

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
#endif
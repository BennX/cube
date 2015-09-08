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
    static void get(char *buffer);
    /**
     * Returns the temperature double.
     * Interupt safe access to the temperature sensor.
     * No interupts while getting and so on!
     * While converting interupts are fine
     */
    static double get();
private:
    static inline uint8_t reset();
    static inline void write_bit(uint8_t bit);
    static inline void write_byte(uint8_t bit);
    static inline uint8_t read_bit();
    static inline uint8_t read_byte();

    static const volatile uint8_t m_port;
    static const volatile uint8_t m_ddr;
    static const volatile uint8_t m_pin;
    static const volatile uint8_t m_pin_no;
};
#endif
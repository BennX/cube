/*
* Display.h
*
* Created: 07.02.2015 14:51:30
* Author: Benjamin
*/


#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#define LCD_DDR DDRA
#define LCD_PORT	PORTA			//datapins are PB0 to PB4 (DB4 to DB7 on the DOG)
#define PIN_ENABLE 	PORTA4
#define PIN_RS 		PORTA6
#define PIN_RW      PORTA5
#define INPUT_PIN   PINA
#define BUSY_BIT    PORTA3

#define CHARACTER_BUFFER_BASE_ADDRESS		0b10000000
#define CHARACTERS_PER_ROW 							16

//instructions (see the ST7036 instruction set for further information)
#define INSTRUCTION_CLEAR_DISPLAY    		0b00000001
#define INSTRUCTION_FUNCTION_SET_INIT_0  	0b00110011
#define INSTRUCTION_FUNCTION_SET_INIT_1  	0b00110010
#define INSTRUCTION_FUNCTION_SET_INIT_2  	0b00101001
#define INSTRUCTION_INSTRUCTION_SET_0    	0b00101000
#define INSTRUCTION_INSTRUCTION_SET_1 		0b00101001
#define INSTRUCTION_BIAS_SET				0b00010101
#define INSTRUCTION_POWER_CONTROL 			0b01010011
#define INSTRUCTION_FOLLOWER_CONTROL		0b01101100
#define INSTRUCTION_CONTRAST_SET			0b01111111
#define INSTRUCTION_DISPLAY_ON				0b00001100
#define INSTRUCTION_DISPLAY_OFF				0b00001000
#define INSTRUCTION_ENTRY_MODE 				0b00000110

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#define F_CPU 22118400
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
/**
 * No interupt while write operation!
 */
class Display
{
public:
    ~Display();
    /**
     * Just need to be called once!
     */
    static void init();
    /**
    * Write a single Char
    */
    static void write_data(const unsigned char &data);
    static void set_cursor(const uint8_t &row, const uint8_t &column);
    /**
     * Used to write a char array to the current position.
     */
    static void write_string(const char *string);
    static void write_string_P(const char *string);
    /**
    * @param value 0...255 PWM Value
    */
    static void setDisplayLight(const uint8_t &value);
    static void clear();
    static void off();
    static void on();
    static bool isActive();
    static struct out
    {
        /**
         * Only use this for PSTR strings!!!!!
         */
        out &operator<<(const char *string)
        {
            Display::write_string(string);
            return *this;
        };

        out &operator<<(const int &i)
        {
            char buf[10];
            itoa(i, buf, 10);
            Display::write_string(buf);
            return *this;
        }

        out &operator<<(const float &f)
        {
            char buf[10];
            sprintf(buf, "%.2f", f);
            Display::write_string(buf);
            return *this;
        }

        out &operator <<(const bool &b)
        {
            if(b)
                Display::write_string_P(PSTR("true"));
            else
                Display::write_string_P(PSTR("false"));
            return *this;
        }

        out &operator<<(const char string)
        {
            Display::write_data(string);
            return *this;
        };

        out &operator ()(const uint8_t &row, const uint8_t &colum)
        {
            Display::set_cursor(row, colum);
        };

    } out;

    static struct out_p
    {
        /**
         * Override for pstr
         */
        out_p &operator<<(const char *string)
        {
            Display::write_string_P(string);
            return *this;
        };

        out_p &operator ()(const uint8_t &row, const uint8_t &colum)
        {
            Display::set_cursor(row, colum);
            return *this;
        };

        out_p &operator<<(const int &i)
        {
            char buf[10];
            itoa(i, buf, 10);
            Display::write_string(buf);
            return *this;
        }

        out_p &operator<<(const float &f)
        {
            char buf[10];
            sprintf(buf, "%.2f", f);
            Display::write_string(buf);
            return *this;
        }

        out_p &operator <<(const bool &b)
        {
            if(b)
                Display::write_string_P(PSTR("true"));
            else
                Display::write_string_P(PSTR("false"));
            return *this;
        }

        out_p &operator<<(const char string)
        {
            Display::write_data(string);
            return *this;
        };
    } out_p;

protected:
    static void write_instruction(const unsigned char &data);
    static inline void write(const unsigned char &data);
    static bool m_active;
private:
    Display() {};
    Display( const Display &c );
    Display &operator=( const Display &c );
}; //Display

#endif //__DISPLAY_H__
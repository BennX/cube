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
#define F_CPU 22118400
#include <util/delay.h>
#include <avr/interrupt.h>
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
protected:
    static void write_instruction(const unsigned char &data);
    static inline void write(const unsigned char &data);
private:
    Display() {};
    Display( const Display &c );
    Display &operator=( const Display &c );

}; //Display

#endif //__DISPLAY_H__
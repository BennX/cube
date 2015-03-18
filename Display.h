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
    /**
    * @param value 0...255 PWM Value
    */
    static inline void changeDisplayLight(const uint8_t &value);
    static void clear();
    static void off();
    static void on();
    static bool isActive();
protected:
    static void write_instruction(const unsigned char &data);
    static inline void write(const unsigned char &data);
private:
    static bool active;
    Display() {};
    Display( const Display &c );
    Display &operator=( const Display &c );

}; //Display
bool Display::active = false;


void Display::init()
{
    active = true;
    //display timer init
    //set OC0B as output
    DDRB |= (1 << DDB4);

    //COM0B0 toggle OC0B on compareMatch and phasecorect PWM
    TCCR0A = 0x00;
    //Clear OC0B on Compare Match when up-counting. Set OC0B on
    //Compare Match when down-counting.
    TCCR0A |= (1 << COM0B1) | (1 << WGM00);
    TCCR0B = 0x00;
    TCCR0B |= (1 << CS02); //prescaler of /256
    //doesnt matter if OCR0A or B just depend on clear flag
    OCR0B = 255; //compare register für B max helligkeit

//END DiSPLAY LIGHT

    LCD_DDR = 0x7F ;// 0b01111111; //set all 7 needed as output

    //initialize 4 bit mode
    write_instruction(INSTRUCTION_FUNCTION_SET_INIT_0);
    write_instruction(INSTRUCTION_FUNCTION_SET_INIT_1);
    write_instruction(INSTRUCTION_FUNCTION_SET_INIT_2);

    //initialize everything else
    //NOTE: In case you need an other initialization-routine (blinking cursor,
    //double line height etc.) choose the appropriate instructions from
    //the ST7036 datasheet and adjust the C-defines at the top of this file
    write_instruction(INSTRUCTION_BIAS_SET);
    write_instruction(INSTRUCTION_POWER_CONTROL);
    write_instruction(INSTRUCTION_FOLLOWER_CONTROL);
    write_instruction(INSTRUCTION_CONTRAST_SET);
    write_instruction(INSTRUCTION_INSTRUCTION_SET_0);
    write_instruction(INSTRUCTION_DISPLAY_ON);
    write_instruction(INSTRUCTION_CLEAR_DISPLAY);
    write_instruction(INSTRUCTION_ENTRY_MODE);
    //somehow needed to ensure
    _delay_ms(1);
}

void Display::changeDisplayLight(const uint8_t &value)
{
    if(value > 0)
        OCR0B = value;
}

void Display::clear()
{
    write_instruction(INSTRUCTION_CLEAR_DISPLAY);
}

void Display::off()
{
    write_instruction(INSTRUCTION_DISPLAY_OFF);
    active = false;
}

void Display::on()
{
    write_instruction(INSTRUCTION_DISPLAY_ON);
    active = true;
}

bool Display::isActive()
{
    return active;
}

void Display::write(const unsigned char &data)
{
    cli();
    char port_buffer = LCD_PORT;

    LCD_PORT |= (1 << PIN_RW);//pull high and readmode
    LCD_DDR &= ~(1 << BUSY_BIT);
    while(INPUT_PIN & (1 << BUSY_BIT));
    LCD_PORT &= ~(1 << PIN_RW); //pull low to write mode
    LCD_DDR |= (1 << BUSY_BIT); //to output mode again

    //write the high nibble first...
    char nibble = (data & 0xF0) >> 4;
    LCD_PORT |= nibble;
    LCD_PORT |= (1 << PIN_ENABLE);

    _delay_us(20);
    LCD_PORT = port_buffer; //set enable=0 and reset port to 0
    //_delay_us(200);

    LCD_PORT |= (1 << PIN_RW);//pull high and readmode
    LCD_DDR &= ~(1 << BUSY_BIT);
    while(INPUT_PIN & (1 << BUSY_BIT));
    LCD_PORT &= ~(1 << PIN_RW); //pull low to write mode
    LCD_DDR |= (1 << BUSY_BIT); //to output mode again

    //...then the low nibble
    nibble = data & 0x0F;
    LCD_PORT |= nibble;
    LCD_PORT |= (1 << PIN_ENABLE);
    _delay_us(20);

    LCD_PORT = port_buffer;//should pull the enable 0
    sei();
    return;
}

void Display::write_instruction(const unsigned char &instruction)
{
    //RS low = instruction
    LCD_PORT &= ~(1 << PIN_RS);
    write(instruction);
}

void Display::write_data(const unsigned char &data)
{
    //RS high = data
    LCD_PORT |= (1 << PIN_RS);
    write(data);
}


void Display::set_cursor(const uint8_t &row,
                         const uint8_t &column)
{
    write_instruction(CHARACTER_BUFFER_BASE_ADDRESS + row * CHARACTERS_PER_ROW +
                      column);
}

void Display::write_string(const char *string)
{
    LCD_PORT |= (1 << PIN_RS);
    while (*string)
    {
        write(*string);
        *string++;
    }
}

#endif //__DISPLAY_H__
/*
 * Display.cpp
 *
 * Created: 30.03.2015 19:02:18
 *  Author: Benjamin
 */
#include "Display.h"
#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//init static membervariables
bool Display::m_active = false;
Display::Out Display::out;
Display::Out_p Display::out_p;

void Display::init()
{
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
    m_active = true;
}

void Display::setDisplayLight(const uint8_t &value)
{
    if(value >= 0)
        OCR0B = value;
}

void Display::clear()
{
    //go to 0 and write 3*16 times " " to clean.
    //faster than calling the clean instruction!
    set_cursor(0, 0);
    for(uint8_t i = 0 ; i < 3; i++)
    {
        for(uint8_t j  = 0; j < 16; j++)
        {
            write_data(' ');
        }
    }
}

void Display::off()
{
    write_instruction(INSTRUCTION_DISPLAY_OFF);
    m_active = false;
}

void Display::on()
{
    write_instruction(INSTRUCTION_DISPLAY_ON);
    m_active = true;
}

bool Display::isActive()
{
    return m_active;
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

void Display::write_string_P(const char *string)
{
    LCD_PORT |= (1 << PIN_RS);

    while (1)
    {
        unsigned char c = pgm_read_byte (string);
        string++;
        if ('\0' == c)
            break;
        write(c);
    }
}

/**
 * Regular out
 */
Display::Out &Display::Out::operator<<(const char *string)
{
    Display::write_string(string);
    return *this;
}

Display::Out &Display::Out::operator<<(const int &i)
{
    char buf[10];
    itoa(i, buf, 10);
    Display::write_string(buf);
    return *this;
}

Display::Out &Display::Out::operator<<(const unsigned int &i)
{
    char buf[10];
    itoa(i, buf, 10);
    Display::write_string(buf);
    return *this;
}

Display::Out &Display::Out::operator<<(const double &d)
{
    char buf[10];
    sprintf(buf, "%.2f", d);
    Display::write_string(buf);
    return *this;
}

Display::Out &Display::Out::operator<<(const bool &b)
{
    if(b)
        Display::write_string_P(PSTR("true"));
    else
        Display::write_string_P(PSTR("false"));
    return *this;
}

Display::Out &Display::Out::operator<<(const char string)
{
    Display::write_data(string);
    return *this;
}

Display::Out &Display::Out::operator()(const uint8_t &row, const uint8_t &colum)
{
    Display::set_cursor(row, colum);
    return *this;
}

/**
 * PSTR
 */
Display::Out_p &Display::Out_p::operator<<(const char *string)
{
    Display::write_string_P(string);
    return *this;
}

Display::Out_p &Display::Out_p::operator<<(const int &i)
{
    char buf[10];
    itoa(i, buf, 10);
    Display::write_string(buf);
    return *this;
}

Display::Out_p &Display::Out_p::operator<<(const unsigned int &i)
{
    char buf[10];
    itoa(i, buf, 10);
    Display::write_string(buf);
    return *this;
}

Display::Out_p &Display::Out_p::operator<<(const double &d)
{
    char buf[10];
    sprintf(buf, "%.2f", d);
    Display::write_string(buf);
    return *this;
}

Display::Out_p &Display::Out_p::operator<<(const bool &b)
{
    if(b)
        Display::write_string_P(PSTR("true"));
    else
        Display::write_string_P(PSTR("false"));
    return *this;
}
Display::Out_p &Display::Out_p::operator<<(const char string)
{
    Display::write_data(string);
    return *this;
};

Display::Out_p &Display::Out_p::operator()(const uint8_t &row,
        const uint8_t &colum)
{
    Display::set_cursor(row, colum);
    return *this;
};

/*
* CPPFile1.cpp
*
* Created: 07.02.2015 15:00:36
*  Author: Benjamin
*/
#define F_CPU 22118400 //redefine! Defined in compiler too but always doublecheck

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include <avr/pgmspace.h>

//#include "Cube.h"
#include "Display.h"
#include "USART.h"
#include "Random.h" //progmem random generator
#include "Temperatur.h"
//Cube cube;

int main()
{
    USART::init();//setup the usart0
    //Test LED
    DDRB |= (1 << DDB3); //PB3

    char buff[20] = {0};
		
    Display::init();
    Display::set_cursor(0, 0);
    Display::write_string("Cube V2");
    Display::set_cursor(1, 0);
    Display::write_string("I AM HERE!");
    Display::set_cursor(2, 0);
    Display::write_string("Guess it's works");

    _delay_ms(5000);
    Display::clear();

    uint8_t i = 0;
    while(true)
    {
        Display::changeDisplayLight(i);
        i++;
        if(i == 255)
            i = 0;
        _delay_ms(20);
        if(rnd() < 30)
            USART::transmit_s("I am watching you!\n");
        else
            USART::transmit_s("Hello World!\n");

        //_delay_ms(500);
        PORTB ^= (1 << PB3); //toggle the testled
        if(i == 125)
        {
            Temperatur::get(buff);
            Display::set_cursor(0, 0);
            Display::write_string("Temperatur: ");
            Display::set_cursor(1, 0);
            Display::write_string(buff);
            Display::write_data('C');
        }
    }
}
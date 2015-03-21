/*
* CPPFile1.cpp
*
* Created: 07.02.2015 15:00:36
*  Author: Benjamin
*/
#define F_CPU 22118400  //redefine! Defined in compiler too but always doublecheck

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include <avr/pgmspace.h>
#include "SPI.h"
//#include "Cube.h"
#include "Display.h"
#include "USART.h"
#include "Random.h" //progmem random generator
#include "Temperatur.h"
#include "Input.h"

//global objects to access in interupts

//Cube cube();
Input input;

void initInterrupt();
void spitest();
void initCubeRoutine();
int main()
{
    Display::init();
    SPI::init();
    USART::init();//setup the usart0

    initInterrupt();
    initCubeRoutine();
    //Test LED
    DDRB |= (1 << DDB3); //PB3

    Display::set_cursor(0, 0);
    Display::write_string("Cube V2");
    Display::set_cursor(1, 0);
    Display::write_string("I AM HERE!");
    Display::set_cursor(2, 0);
    Display::write_string("Guess it's works");
    Display::setDisplayLight(20);
    _delay_ms(10);
    spitest();
    uint8_t i = 0;
    while(true)
    {
        //Display::write_string("Cube V2");
        PORTB ^= (1 << PB3); //toggle the testled
        _delay_ms(100);
    }
}
#define DDR_TO_STORAGE DDRC
#define TO_STORAGE_PORT PORTC
#define TO_STORAGE_PIN DDC6 //data direction C6

#define DDR_DISABLE_LINE DDRC
#define DISABLE_LINE_PORT PORTC
#define DISABLE_LINE_PIN DDC7 //data direction C7

void spitest()
{
    Display::set_cursor(0, 0);
    //enabel output on ss and latch pins
    DDR_TO_STORAGE |= (1 << TO_STORAGE_PIN);
    DDR_DISABLE_LINE |= (1 << DISABLE_LINE_PIN);
    //SPI::init();
    for(uint8_t i = 0; i < 10; i++)
    {
        SPI::transmit(0b11111111);
    }
    SPI::transmit(0b00000000); //enable last
    TO_STORAGE_PORT |= (1 << TO_STORAGE_PIN); //1 clock to storage
    TO_STORAGE_PORT &= ~(1 << TO_STORAGE_PIN); //1 clock to storage
    DISABLE_LINE_PORT &= ~(1 << DISABLE_LINE_PIN); //set low to enable the register
    return;
}

void initInterrupt()
{
    TCCR2A = 0x00;
    TCCR2A |= (1 << WGM21); //CTC mode
    TCCR2B = 0x00;
    TCCR2B |= (1 << CS22) | (1 << CS22); // 256 prescaler
    TIMSK2 |= (1 << OCIE2A); //enable compare interrupt
    //some compare counter ~ 1ms
    //OCR2A = (uint8_t)(F_CPU / 256.0 * 1e-3 - 0.5);
    OCR2A = 84; // 1ms
    sei();
}

void initCubeRoutine()
{
    //16 Bit timer!
    TCCR1A |= (1 << WGM12); // CTC on OCR1A
    TCCR1B |= (1 << CS10); //kein prescaler
    TIMSK1 |= (1 << OCIE1A); //compare interupt on A
    OCR1A = 0x0ACD;//2765  = 8khz
}

ISR(TIMER2_COMPA_vect)
{
    input.update();
}

ISR(TIMER1_COMPA_vect)
{
    //cube.render();
}
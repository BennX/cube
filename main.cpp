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
#include <avr/pgmspace.h>

#include "Cube.h"
#include "Display.h"
#include "USART.h"
#include "Temperatur.h"
#include "Input.h"
#include "Animation/Animator.h"
#include "Animation/FadeAnimation.h"
#include "Animation/RainAnimation.h"
#include "Animation/FontAnimation/FontAnimation.h"

#include "Animation/Ball.h"
#include "Util/cpp_util.h"
#include "Menu/Menu.h"

//global objects to access in interupts
Cube cube; //also calls SPI::init()!
Input input;

//declare some functions here
void initCubeRoutine();
void toggleInfoLED();
long long ms();

int main()
{
    Display::init();
    USART::init();//setup the usart0

    Animator animator;
    animator.addAnimation(new FadeAnimation(&cube));
    animator.addAnimation(new RainAnimation(&cube));
    animator.addAnimation(new Ball(&cube));
    animator.addAnimation(new FontAnimation(&cube));
    Menu menu(&input, &animator);
    //first test animation
    Animation *anim = new Ball(&cube);
    initCubeRoutine();
    sei();

    //Test LED
    DDRB |= (1 << DDB3); //PB3

    Display::set_cursor(0, 0);
    Display::write_string_P(PSTR("Cube V2"));
    Display::set_cursor(1, 0);
    Display::write_string_P(PSTR("I AM HERE!"));
    Display::set_cursor(2, 0);
    Display::write_string_P(PSTR("Guess it's works"));

    _delay_ms(1000);
    Display::clear();
    _delay_ms(1000);

    long long start = 1;
    uint16_t delta = 0;
    while(true)
    {
        start = ms();
        animator.update(delta);
        menu.update(delta);
        delta = ms() - start;
    }
}

/**
 * used to check if still alife
 */
void toggleInfoLED()
{
    PORTB ^= (1 << PB3); //toggle the testled
}


void initCubeRoutine()
{
    //16 Bit timer!
    TCCR1A = 0x00; // CTC on OCR1A
    TCCR1B |= (1 << CS00) | (1 << WGM12); //kein prescaler
    TIMSK1 |= (1 << OCIE1A); //compare interupt on A
    OCR1A = 0x0ACD;//2765  = 8khz
}

long long millis = 0;
long long ms()
{
    return millis;
}

uint8_t counter = 0;
ISR(TIMER1_COMPA_vect)
{
    cube.render();

    counter++;
    if(counter % 8 == 0) // & 8 geht nicht!
    {
        // 1khz routine here no need to clean counter
        millis++;
        input.update();
    }
}
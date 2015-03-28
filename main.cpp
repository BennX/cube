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

#include "Cube.h"
#include "Display.h"
#include "USART.h"
#include "Random.h" //progmem random generator
#include "Temperatur.h"
#include "Input.h"
#include "Animation/FadeAnimation.h"
#include "Animation/RainAnimation.h"
#include "cpp_util.h"

//global objects to access in interupts
Cube cube; //also calls SPI::init()!
Input input;

//declare some functions here
void initCubeRoutine();
void toggleInfoLED();
long long ms();

int main()
{
    //first test animation
    Animation *anim = new RainAnimation(&cube);

    Display::init();
    USART::init();//setup the usart0

    initCubeRoutine();
    sei();

    //Test LED
    DDRB |= (1 << DDB3); //PB3

    Display::set_cursor(0, 0);
    Display::write_string("Cube V2");
    Display::set_cursor(1, 0);
    Display::write_string("I AM HERE!");
    Display::set_cursor(2, 0);
    Display::write_string("Guess it's works");
    Display::setDisplayLight(20);
    _delay_ms(1000);
    Display::clear();

    char buff[20] = {0};
    short start = 0, delta = 0;
    int cur_free_ram = 0;
    bool toggle = true;
    uint8_t reset_timer = 0;
    while(true)
    {
        start = ms();
        anim->update(delta);
        reset_timer += delta;
        if(input.isPressed() & reset_timer > 200)
        {
            reset_timer = 0;
            Display::set_cursor(2, 0);
            Display::write_string("pres");
            if(toggle)
            {
                Animation *a = anim;
                anim = new FadeAnimation(&cube);
                delete a;
                toggle = false;
                cube.off();
            }
            else
            {
                Animation *b = anim;
                anim = new RainAnimation(&cube);
                delete b;
                toggle = true;
                cube.off();
            }
        }

        if(freeRam() != cur_free_ram)
        {
            Display::set_cursor(0, 0);
            Display::write_string("Free RAM");
            itoa(freeRam(), buff, 10);
            Display::set_cursor(1, 0);
            Display::write_string(buff);
            Display::write_string("MB");
        }
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
    counter++;
    if(counter & 0x04)
    {
        // 1khz routine here no need to clean counter
        millis++;
        input.update();
    }
    cube.render();
}
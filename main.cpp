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
#include "Input.h"

#include "Sensors/Temperatur.h"
#include "Sensors/Microphone.h"

#include "Util/GUID.h"
#include "Util/cpp_util.h"

#include "Animation/Animator.h"
#include "Animation/FadeAnimation.h"
#include "Animation/RainAnimation.h"
#include "Animation/FontAnimation/FontAnimation.h"
#include "Animation/SingleColor.h"
#include "Animation/Ball.h"
#include "Animation/AutoAnimation.h"
#include "Animation/Wall/Wall.h"
#include "Animation/colorFade/Twoballs.h"
#include "Animation/colorFade/RandomFade.h"

#include "Menu/Menu.h"

//load the static and const settings
#include "settings.h"

//sensors

//declare some functions here
void initCubeRoutine();
void toggleInfoLED();
long long ms();
void showCubeColors();

int main()
{
    cli();
    Display::init();
    USART::init();//setup the usart0
    Microphone::init();
    Display::out_p(0, 0) << PSTR("initialization");
//init the cube
    Cube& cube = Cube::getInstance();
    Input& input = Input::getInstance();

//init the effects
    Animator animator;
    RandomFade rFade(GUID::get());
    Wall wall(cube, GUID::get());
    FadeAnimation fade(cube, GUID::get());
    RainAnimation rain(cube, GUID::get());
    Ball ball(cube, GUID::get());
    //FontAnimation font(&cube, GUID::get());
    //SingleColor color(&cube, GUID::get());
    TwoBalls twoBalls(GUID::get());
    AutoAnimation autoAnimation(GUID::get(), &animator);

    animator.addAnimation(&rFade);
    animator.addAnimation(&wall);
    animator.addAnimation(&fade);
    animator.addAnimation(&rain);
    animator.addAnimation(&ball);
    //animator.addAnimation(&font);
    //animator.addAnimation(&color);
    animator.addAnimation(&twoBalls);
    animator.addAnimation(&autoAnimation);


    Display::out_p(1, 0) << PSTR("Animation done");
    //push the menu entrys
    Menu menu(input, animator);
    menu.addEntry(&rFade);
    menu.addEntry(&wall);
    menu.addEntry(&fade);
    menu.addEntry(&rain);
    menu.addEntry(&ball);
    //menu.addEntry(&font);
    //menu.addEntry(&color);
    menu.addEntry(&twoBalls);
    menu.addEntry(&autoAnimation);

    Display::out_p(2, 0) << PSTR("Menu done");

    initCubeRoutine();
    _delay_ms(1);
    sei();
    // so now everything is init
    //make some "nice color to show thats up!
    showCubeColors();

    //Test LED
    DDRB |= (1 << DDB3); //PB3
    _delay_ms(1000);
    Display::clear();

    long long start = 1; //long long since ms is a long long
    uint16_t delta = 0; // delta value always positiv
    uint16_t timer = 0;
    while(true) //loop start
    {
        start = ms();
        animator.update(delta);
        menu.update(delta);
        Display::update(delta);
        delta = ms() - start;
        timer += delta;
        /*
                if(timer > 100)
                {
                    Display::out_p(2, 10) << PSTR("      ");
                    int32_t median = abs(Microphone::sample() - 512);
                    for (uint8_t i = 0; i < 255; i++)
                    {
                        median += abs(Microphone::sample() - 512);
                    }
                    Display::out(2, 10) << (int)(median / 256);
                    timer = 0;
                }
        		*/
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
    //OCR1A = 0x0ACD;//2765  = 8khz
    //OCR1A = 2212; // 10khz
    OCR1A = 1843;// 12khz
    //OCR1A = 1580; // 14khz
    //OCR1A = 1382; // 16khz
}

long long millis = 0;
long long ms()
{
    return millis;
}

uint8_t counter = 0;
ISR(TIMER1_COMPA_vect)
{
    Cube::getInstance().render();

    counter++;
    if(counter % 12 == 0) //12khz
    {
        // 1khz routine here no need to clean counter
        millis++;
        Input::getInstance().update();
    }
}

void showCubeColors()
{
    Cube& cub = Cube::getInstance();
    for(uint8_t z = 0; z < 5; z++)
        for(uint8_t y = 0; y < 5; y++)
            for(uint8_t x = 0; x < 5; x++)
            {
                cub(x, y, z) = RGB(x / 4.0 * MAX_COLOR, y / 4.0 * MAX_COLOR, z / 4.0 * MAX_COLOR);
            }

    Display::clear();
    Display::out_p(0, 0) << PSTR("Show");
    Display::out_p(1, 0) << PSTR("Colors");
    Display::out_p(2, 0) << PSTR("Click 4 continue");
    while(!Input::getInstance().clicked())
        ;//nop for the first click ;)
}
/*
* Menu.cpp
*
* Created: 30.03.2015 18:28:35
* Author: Benjamin
*/


#include "Menu.h"
#include <math.h>
#include <stdio.h>
#define MIN( a, b ) (a < b) ? a : b
// default constructor
Menu::Menu(Input *i, Animator *a) : changed(true), cur_pos(0), input(i),
    animator(a), clicked(false), display_light_timer(0), displayIsOn(true),
    fading(false), fadeOn(true)
{
} //Menu

// default destructor
Menu::~Menu()
{
} //~Menu

void Menu::update(const short &delta)
{
    display_light_timer += delta;
    if(changed)
    {
        Display::clear();
        Display::set_cursor(cur_pos, 0);
        Display::write_string_P(PSTR(">"));
        Display::set_cursor(0, 1);
        Display::write_string_P(PSTR("Fade"));
        Display::set_cursor(1, 1);
        Display::write_string_P(PSTR("Rain"));
        Display::set_cursor(2, 1);
        Display::write_string_P(PSTR("Ball"));
        Display::on();
        changed = false;
        displayIsOn = true;
        if(!fading)
        {
            display_light_timer = 0;
            fading = true;
        }
    }
    //fade on
    if(DISPLAY_FADE_ON_TIME - display_light_timer > 0 && displayIsOn && fadeOn)
    {
        Display::setDisplayLight(255.0 / DISPLAY_FADE_ON_TIME * display_light_timer);
    }
    else if(displayIsOn && fadeOn)
    {
        Display::setDisplayLight(255);
        fadeOn = false;
        fading = false;
    }

    //fade off
    if((display_light_timer > DISPLAY_LIGHT_OF_TIMER) && displayIsOn)
    {
        if(255.0 / DISPLAY_FADE_OUT_TIME * (DISPLAY_FADE_OUT_TIME -
                                            (display_light_timer -
                                             DISPLAY_LIGHT_OF_TIMER))  < 1)
        {
            Display::setDisplayLight(0);
            Display::off();
            displayIsOn = false;
            fadeOn = true; // enable on fade
        }
        else
        {
            Display::setDisplayLight(255.0 / DISPLAY_FADE_OUT_TIME *
                                     (DISPLAY_FADE_OUT_TIME -
                                      (display_light_timer -
                                       DISPLAY_LIGHT_OF_TIMER)));
        }
    }

    //check if cursor move
    int8_t enc = input->getIncDelta();
    if (enc != 0)
    {
        cur_pos += enc;
        if(cur_pos <= 0)
            cur_pos = 0;
        else if (cur_pos >= 2)
            cur_pos = 2;
        //redraw next round

        changed = true;
    }

    if(clicked)
    {
        clicktimer += delta;
        if(clicktimer > CLICK_DELAY)
        {
            clicked = false;
            clicktimer = 0;
        }
    }
    //now check if click
    if(!clicked && input->isPressed())
    {
        animator->operator[](cur_pos);
    }
}
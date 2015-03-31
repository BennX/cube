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
Menu::Menu(Input *i) : changed(true), cur_pos(0), input(i)
{
} //Menu

// default destructor
Menu::~Menu()
{
} //~Menu

void Menu::update(const short &delta)
{
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
        changed = false;
    }
    //check if cursor move
    int8_t enc = input->getIncDelta();
    if (delta != 0)
    {
        cur_pos += enc;
        if(cur_pos < 0)
            cur_pos = 0;
        else if (cur_pos > 2)
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
        //tell the animator what todo
    }
}
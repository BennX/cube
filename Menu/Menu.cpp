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

void Menu::addEntry(PGM_P progmem_ptr)
{
    m_list.add(progmem_ptr);
}

void Menu::update(const short &delta)
{
    display_light_timer += delta;
    if(changed)
    {
        Display::clear();

        if(cur_pos <= 1)
        {
            //Draw if pos = 0
            for (uint8_t i = 0; i < 3 && i < m_list.size(); i++)
            {
                Display::set_cursor(i, 1);
                Display::write_string_P(m_list[i]);
            }
            Display::set_cursor(cur_pos, 0);
            Display::write_string_P(PSTR(">"));
        }
        else if(cur_pos == m_list.size())
        {
            //draw if last pos of list
            for (uint8_t i = 0; i < 3; i++)
            {
                Display::set_cursor(i, 1);
                Display::write_string_P(m_list[m_list.size() - (2 - i)]);
            }
            Display::set_cursor(2, 0);
            Display::write_string_P(PSTR(">"));
        }
        else
        {
            //else draw -1 0 +1 of pos
            for (uint8_t i = 0; i < 3; i++)
            {
                Display::set_cursor(i, 1);
                Display::write_string_P(m_list[(cur_pos - 1) + i]);
            }
            Display::set_cursor(1, 0);
            Display::write_string_P(PSTR(">"));
        }

        char buf[10];
        int ram = freeRam();
        itoa(ram, buf, 10);
        Display::out(0, 7) << buf;
        Display::write_string("b");

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
    if(displayIsOn && fadeOn && DISPLAY_FADE_ON_TIME - display_light_timer > 0)
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
    if(displayIsOn && (display_light_timer > DISPLAY_LIGHT_OF_TIMER))
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
        else if (cur_pos >= m_list.size())
            cur_pos = m_list.size();
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
    if(!clicked && input->isPressed() && cur_pos < m_list.size())
    {
        animator->operator[](cur_pos);
    }
}
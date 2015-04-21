/*
* Menu.cpp
*
* Created: 30.03.2015 18:28:35
* Author: Benjamin
*/


#include "Menu.h"
#include <math.h>
#include <stdio.h>
#include "../Util/PStrings.h"
#define MIN( a, b ) (a < b) ? a : b
// default constructor
Menu::Menu(Input *i, Animator *a) : changed(true), cur_pos(0),
    m_cur_selected(0), m_cur_submenu(false), input(i), animator(a), clicked(false),
    display_light_timer(0), displayIsOn(true), fading(false), fadeOn(true),
    m_current_animation(0)
{
} //Menu

// default destructor
Menu::~Menu()
{
} //~Menu

void Menu::addEntry(MenuEntry *e)
{
    m_list.add(e);
}

void Menu::update(const short &delta)
{
    if(!m_cur_submenu)
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
                    Display::out_p(i, 1) << m_list[i]->name();
                }

                Display::out_p(cur_pos, 0) << p_strings::right_arrow;
            }
            else if(cur_pos == m_list.size())
            {
                //draw if last pos of list
                for (uint8_t i = 0; i < 3; i++)
                {
                    Display::out_p(i, 1) << m_list[m_list.size() - (2 - i)]->name();
                }
                Display::out_p(2, 0) << p_strings::right_arrow;
            }
            else
            {
                //else draw -1 0 +1 of pos
                for (uint8_t i = 0; i < 3; i++)
                {
                    Display::out_p(i, 1) << m_list[(cur_pos - 1) + i]->name();
                }
                Display::out_p(1, 0) << p_strings::right_arrow;
            }
#ifdef DEBUG
            Display::out_p(0, 7) << PSTR("Free RAM");
            Display::out(1, 7) << freeRam();
            Display::out << "b";
            Display::out(2, 7) << delta;
#endif
            Display::out_p(0, 8) << PSTR("Momentan");
            if(m_current_animation != 0)
                Display::out_p(1, 8) << m_current_animation->name();
            Display::on();
            changed = false;
            displayIsOn = true;
            if(!fading)
            {
                display_light_timer = 0;
                fading = true;
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

        //if(clicked)
        //{
        //clicktimer += delta;
        //if(clicktimer > CLICK_DELAY)
        //{
        //clicked = false;
        //clicktimer = 0;
        //}
        //}

        //now check if click

        if(input->clicked() && cur_pos <= m_list.size())
        {
            if(!m_list[cur_pos]->subMenu())
            {
                animator->operator[](cur_pos);
                m_current_animation = m_list[cur_pos];
            }
            else
            {
                m_cur_selected = cur_pos;
                m_cur_submenu = true;
            }
            changed = true;
        }
    }
//last but not least draw the submenu if submenu
    else
    {
        m_list[m_cur_selected]->updateEntry(delta, *input, *this);
    }
}

void Menu::start(const uint8_t &animation)
{
    animator->operator[](animation);
    m_current_animation = m_list[animation];
    changed = true;
}

void Menu::leaveSubmenu()
{
    m_cur_submenu = false;
    changed = true;
}
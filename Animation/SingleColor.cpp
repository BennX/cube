/*
* SingleColor.cpp
*
* Created: 06.04.2015 13:13:57
* Author: Benjamin
*/


#include "SingleColor.h"
#include "../Util/PStrings.h"
// default constructor
SingleColor::SingleColor(Cube *c, const uint8_t &id): Animation(id), cube(c),
    m_changed(true), m_curMenuPos(0), m_selected(0), m_somethingSelected(false),
    m_menuChanged(true), m_clickdelay(0), m_clicked(true)
{
} //SingleColor

// default destructor
SingleColor::~SingleColor()
{
} //~SingleColor

void SingleColor::update(const uint16_t &delta)
{
    if(m_changed)
    {
        for(uint8_t x = 0; x < 5; x++)
        {
            for(uint8_t y = 0; y < 5; y++)
            {
                for(uint8_t z = 0; z < 5; z++)
                {
                    cube->setRGB(x, y, z, m_color);
                }
            }
        }
    }
}

void SingleColor::updateEntry(const uint16_t &delta, Input &i, Menu &m)
{
    if(m_clicked)
    {
        m_clickdelay += delta;
        if(m_clickdelay > CLICK_DELAY)
        {
            m_clicked = false;
            m_clickdelay = 0;
        }
    }

    if(m_menuChanged)
    {
        Display::clear();
        switch(m_curMenuPos)
        {
            case 0:
                Display::out_p(0, 0) << PSTR("Single Color");
                Display::out_p(1, 1) << p_strings::rot << m_color.r * 100.0 / (MAX_COLOR - 1) <<
                                     p_strings::procent;
                Display::out_p(2, 1) << p_strings::gruen << m_color.g * 100.0 /
                                     (MAX_COLOR - 1) <<
                                     p_strings::procent;
                Display::out_p(1, 0) << p_strings::right_arrow;
                break;
            case 1:
                Display::out_p(0, 1) << p_strings::rot << m_color.r * 100.0 / (MAX_COLOR - 1) <<
                                     p_strings::procent;
                Display::out_p(1, 1) << p_strings::gruen << m_color.g * 100.0 /
                                     (MAX_COLOR - 1) <<
                                     p_strings::procent;
                Display::out_p(2, 1) << p_strings::blau << m_color.b * 100.0 /
                                     (MAX_COLOR - 1) <<
                                     p_strings::procent;
                Display::out_p(1, 0) << p_strings::right_arrow;
                break;
            case 2:
                Display::out_p(0, 1) << p_strings::gruen << m_color.g * 100.0 /
                                     (MAX_COLOR - 1) <<
                                     p_strings::procent;
                Display::out_p(1, 1) << p_strings::blau << m_color.b * 100.0 /
                                     (MAX_COLOR - 1) <<
                                     p_strings::procent;
                Display::out_p(2, 1) << p_strings::start;
                Display::out_p(1, 0) << p_strings::right_arrow;
                break;
            case 3:
                Display::out_p(0, 1) << p_strings::gruen << m_color.g * 100.0 /
                                     (MAX_COLOR - 1) <<
                                     p_strings::procent;
                Display::out_p(1, 1) << p_strings::blau << m_color.b * 100.0 /
                                     (MAX_COLOR - 1) <<
                                     p_strings::procent;
                Display::out_p(2, 1) << p_strings::start;
                Display::out_p(2, 0) << p_strings::right_arrow;
                break;
        }
        m_menuChanged = false;
    }

    if(!m_clicked)
    {
        if(i.isPressed() && m_curMenuPos != 3)
        {
            m_somethingSelected = !m_somethingSelected;
            m_selected = m_curMenuPos;
            m_clicked = true;
        }
        else if (i.isPressed() && m_curMenuPos == 3)
        {
            m.start(m_ID);
            m.leaveSubmenu();
            m_menuChanged = true;
            m_clicked = true;
        }
    }

    int8_t enc = i.getIncDelta();
    if(enc != 0 && m_somethingSelected)
    {
        switch(m_selected)
        {
            case 0:
                if(m_color.r + enc < MAX_COLOR && m_color.r + enc >= 0)
                    m_color.r += enc;
                break;
            case 1:
                if(m_color.g + enc < MAX_COLOR && m_color.g + enc >= 0)
                    m_color.g += enc;
                break;
            case 2:
                if(m_color.b + enc < MAX_COLOR && m_color.b + enc >= 0)
                    m_color.b += enc;
                break;
        }
        m_changed = true;
        m_menuChanged = true;
    }
    else if(enc != 0)
    {
        uint8_t temp = m_curMenuPos;
        m_curMenuPos += enc;
        if(m_curMenuPos < 0)
        {
            m_curMenuPos = 0;
        }
        else if(m_curMenuPos > 3)
        {
            m_curMenuPos = 3;
        }
        if(temp != m_curMenuPos)
            m_menuChanged = true;
    }
}

bool SingleColor::subMenu()
{
    return true;
}
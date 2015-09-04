/*
* AutoAnimation.cpp
*
* Created: 08.04.2015 13:18:57
* Author: Benjamin
*/


#include "AutoAnimation.h"
#include "../Util/PStrings.h"
// default constructor
AutoAnimation::AutoAnimation(const uint8_t &id, Animator *anim): Animation(id), m_submenu(PSTR("Auto Anim."), id),
    m_animator(anim), m_timer(0), m_switchSpeed(DEFAULT_AUTO_SWITCH_SPEED)
{
    //add entry so there max time is 5minutes till it changes
    m_submenu.addEntry(p_strings::speed, &m_switchSpeed, 0, 65536, 250);
} //AutoAnimation

// default destructor
AutoAnimation::~AutoAnimation()
{
} //~AutoAnimation

void AutoAnimation::update(const uint16_t &delta)
{
    m_timer += delta;
    if(m_timer > m_switchSpeed)
    {
        m_timer = 0;
        //this starts the autoanimation
        m_animator->operator()(m_ID);
    }
}

void AutoAnimation::updateEntry(const uint16_t &delta, Input &i, Menu &m)
{
    m_submenu.update(delta, i, m);
}

bool AutoAnimation::subMenu()
{
    return true;
}

PGM_P AutoAnimation::name()
{
    return PSTR("Auto");
}
/*
* AutoAnimation.cpp
*
* Created: 08.04.2015 13:18:57
* Author: Benjamin
*/


#include "AutoAnimation.h"

// default constructor
AutoAnimation::AutoAnimation(const uint8_t &id, Animator *anim): Animation(id),
    m_animator(anim), m_timer(0), m_switchSpeed(DEFAULT_AUTO_SWITCH_SPEED)
{
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

}

bool AutoAnimation::subMenu()
{
    return false;
}

PGM_P AutoAnimation::name()
{
    return PSTR("Auto");
}
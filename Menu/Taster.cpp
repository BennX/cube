/*
* Taster.cpp
*
* Created: 20.04.2015 18:09:28
* Author: Benjamin
*/


#include "Taster.h"

// default constructor
Taster::Taster(Input &i): m_timer(0), m_input(i), m_clicked(true)
{
} //Taster

// default destructor
Taster::~Taster()
{
} //~Taster

void Taster::update(const uint16_t &delta)
{
    if(!m_clicked && m_input.isPressed())
        m_clicked = true;
    if(m_clicked)
    {
        m_timer += delta;
    }
}

bool Taster::clicked()
{
    if(m_timer > CLICK_DELAY_TASTER)
    {
        m_clicked = false;
        return true;
    }
    else
    {
        return false;
    }
}
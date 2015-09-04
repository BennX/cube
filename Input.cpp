/*
* Input.cpp
*
* Created: 15.03.2015 19:18:34
* Author: Benjamin
*/


#include "Input.h"
#include <avr/interrupt.h>
Input Input::m_instance;
// default constructor
Input::Input() : m_enc_delta(0), m_last(0), m_inc_last(false),
    m_inc_clicked(false), m_inc_click_timer(0)
{
    // Button input
    *BUTTON_DDR &= ~((1 << BUTTON0) | (1 << BUTTON1) | (1 << BUTTON2) |
                     (1 << BUTTON3));
    //enable pullup
    *BUTTON_PORT |= ((1 << BUTTON0) | (1 << BUTTON1) | (1 << BUTTON2) |
                     (1 << BUTTON3));

    //make the INC as inputs
    *INC_DDR &= ~((1 << INC_PHASE1_PIN) | (1 << INC_PHASE2_PIN) |
                  (1 << INC_TASER_PIN));

    //enable pullups
    *INC_PORT |= ((1 << INC_PHASE1_PIN) | (1 << INC_PHASE2_PIN) |
                  (1 << INC_TASER_PIN));
    //first init
    int8_t newv;

    newv = 0;
    if( !(*INC_PIN & (1 << INC_PHASE2_PIN)) )
        newv = 3;
    if( !(*INC_PIN & (1 << INC_PHASE1_PIN)) )
        newv ^= 1;                   // convert gray to binary
    m_last = newv;                   // power on state
} //Input

// default destructor
Input::~Input()
{
} //~Input

void Input::update()
{
    int8_t newv, diff;
    newv = 0;
    if( !(*INC_PIN & (1 << INC_PHASE2_PIN)) )
        newv = 3;
    if( !(*INC_PIN & (1 << INC_PHASE1_PIN)) )
        newv ^= 1;                   // convert gray to binary

    diff = m_last - newv;                // difference last - new
    if( diff & 1 )                // bit 0 = value (1)
    {
        this->m_last = newv;                 // store new as next last
        this->m_enc_delta += (diff & 2) - 1;        // bit 1 = direction (+/-)
    }

    //check if "clicked
    m_inc_click_timer += 1; //since we call this method every ms
    if(!m_inc_clicked && m_inc_click_timer > INC_CLICK_DELAY)
    {
        if(!m_inc_last && isPressed())
            m_inc_last = true;
        if(m_inc_last && !isPressed())
        {
            m_inc_last = false;
            m_inc_clicked = true;
        }
    }
}

bool Input::clicked()
{
    if(m_inc_clicked)
    {
        m_inc_click_timer = 0; //start the "delay" timer
        m_inc_clicked = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool Input::isPressed()
{
    return !(*INC_PIN & (1 << INC_TASER_PIN)) ? true : false;
}

bool Input::isPressed(const uint8_t &i)
{
    switch(i)
    {
    case 0:
        if(!(*BUTTON_PIN & 1 << BUTTON0))
            return true;
        break;
    case 1:
        if(!(*BUTTON_PIN & 1 << BUTTON1))
            return true;
        break;
    case 2:
        if(!(*BUTTON_PIN & 1 << BUTTON2))
            return true;
        break;
    case 3:
        if(!(*BUTTON_PIN & 1 << BUTTON3))
            return true;
        break;
    }
    return false;
}

int8_t Input::getIncDelta()
{
    //reading doublestep encoder
    int8_t val;
    cli();
    val = m_enc_delta;
    m_enc_delta = val & 1;
    sei();
    return val >> 1;
}
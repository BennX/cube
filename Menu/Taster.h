/*
* Taster.h
*
* Created: 20.04.2015 18:09:28
* Author: Benjamin
*/


#ifndef __TASTER_H__
#define __TASTER_H__

#include "../Input.h"
#include <avr/io.h>
/**
 * Taster which has a delay.
 * If clicked it stays clicked till clicked() is called.
 * Clicked returns true if it was clicked else false
 */
class Taster
{
//variables
public:
protected:
private:
    static const uint16_t CLICK_DELAY_TASTER;

    uint16_t m_timer;
    Input &m_input;
    bool m_clicked;

//functions
public:
    Taster(Input &i);
    ~Taster();
    void update(const uint16_t &delta);
    bool clicked();
protected:
private:
    Taster( const Taster &c );
    Taster &operator=( const Taster &c );

}; //Taster

#endif //__TASTER_H__

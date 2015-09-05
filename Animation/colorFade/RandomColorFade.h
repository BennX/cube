/*
* RandomColorFade.h
*
* Created: 05.09.2015 13:07:26
* Author: Benjamin
*/


#ifndef __RANDOMCOLORFADE_H__
#define __RANDOMCOLORFADE_H__
#include "../../Menu/Submenu.h"
#include "../../Menu/MenuEntry.h"
#include "../../RGB.h"
struct Point
{
    float x,y,z;
};
class RandomColorFade: public Submenu, public Animation
{
public:
    RandomColorFade(const uint8_t &id);
    ~RandomColorFade();

    void update(const uint16_t &delta);

    //override
    PGM_P name() override
    {
        return PSTR("R Fade");
    };

private:
    RandomColorFade( const RandomColorFade &c );
    RandomColorFade& operator=( const RandomColorFade &c );
    RGB m_color0;
	RGB m_color0Target;
    RGB m_color1;
	RGB m_color1Target;
	
	uint16_t m_timer;
	int m_changeSpeed;
	
	uint16_t m_timerCol0;
	uint16_t m_timerCol1;
	int m_stayTime;
	
    Point m_p0;
    Point m_p1;

    bool m_done;
	
	void updateColor(RGB &r, const RGB &target);
}; //RandomColorFade

#endif //__RANDOMCOLORFADE_H__

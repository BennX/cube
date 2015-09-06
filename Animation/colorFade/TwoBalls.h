/*
* RandomColorFade.h
* A animation which has 2 points which move around. The size and speed of
* the points can be changed. Also the color change of the dots while moving can
* be speed up or slowed down.
*
* Created: 05.09.2015 13:07:26
* Author: Benjamin
*/


#ifndef __RANDOMCOLORFADE_H__
#define __RANDOMCOLORFADE_H__
#include "../../Menu/Submenu.h"
#include "../../Menu/MenuEntry.h"
#include "../../RGB.h"
#include "../../graphic/Vector.h"

class TwoBalls: public Submenu, public Animation
{
public:
    TwoBalls(const uint8_t& id);
    ~TwoBalls();

    void update(const uint16_t& delta);

    //override
    PGM_P name() override
    {
        return PSTR("2 Balls");
    };

private:
    TwoBalls(const TwoBalls& c);
    TwoBalls& operator=(const TwoBalls& c);
    RGB m_color0;
    RGB m_color0Target;
    RGB m_color1;
    RGB m_color1Target;

    uint16_t m_timer;
    int m_changeSpeed;

    uint16_t m_timerCol0;
    uint16_t m_timerCol1;
    int m_stayTime;

    float m_range;
    float m_moveSpeed;

    Vector m_p0;
    Vector m_p1;

    Vector m_direction0;
    Vector m_direction1;

    bool m_done;

    void updateColor(RGB& r, const RGB& target);

    //checks for collision and changes the dir vector if collision
    void checkCollision(const Vector& v, Vector& direction);

    void print(const Vector& v, const uint8_t& col);
}; //RandomColorFade

#endif //__RANDOMCOLORFADE_H__

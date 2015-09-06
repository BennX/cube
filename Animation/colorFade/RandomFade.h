/*
* RandomFade.h
* A fade animation which uses two points and interpolate the colors of
* ALL dots which can be colorized depending on the distance to the two points.
* While this it slightly changes the color to the next one.
* The speed of the color change can be increased or slowed down.
*
* Created: 06.09.2015 13:00:52
* Author: Benjamin
*/


#ifndef __RANDOMFADE_H__
#define __RANDOMFADE_H__

#include "../../Menu/Submenu.h"
#include "../../Menu/MenuEntry.h"
#include "../../RGB.h"
#include "../../graphic/Vector.h"
class RandomFade: public Submenu, public Animation
{
public:
    RandomFade(const uint8_t& id);
    ~RandomFade();

    void update(const uint16_t& delta);

    //override
    PGM_P name() override
    {
        return PSTR("R Fade");
    };

private:
    RandomFade(const RandomFade& c);
    RandomFade& operator=(const RandomFade& c);
    RGB m_color0;
    RGB m_color0Target;
    RGB m_color1;
    RGB m_color1Target;

    uint16_t m_timer;
    int m_changeSpeed;

    uint16_t m_timerCol0;
    uint16_t m_timerCol1;
    //time a reached the color stays till it fades to the next
    int m_stayTime;

    float m_moveSpeed;

    Vector m_p0;
    Vector m_p1;
    Vector m_direction0;
    Vector m_direction1;

    bool m_done;

    void updateColor(RGB& r, const RGB& target);

    //if collision it changes the direction of the update vector
    void checkCollision(const Vector& v, Vector& direction);
}; //RandomColorFade

#endif //__RANDOMFADE_H__

/*
* Ball.h
*
* Created: 30.03.2015 19:34:25
* Author: Benjamin
*/


#ifndef __BALL_H__
#define __BALL_H__

#include "Animation.h"
#include "../Menu/MenuEntry.h"
#include "../Cube.h"

#define CLICK_DELAY_BALL 1000
class Ball : public Animation, public MenuEntry
{
public:
    Ball(Cube *c, const uint8_t &id);
    ~Ball();
    void update(const uint16_t &delta);

    //menu stuff
    void updateEntry(const uint16_t &delta, Input &i, Menu &m);
    PGM_P name()
    {
        return PSTR("Ball");
    };
    bool subMenu();
private:
//config stuff defined in settings
    static const float START_UPDATE_TIME;
    static const float MAX_SIZE;
    static const float MIN_UPDATE_TIME;
    static const float UPDATE_TIME_CHANGE;

    Cube *cube;
    RGB color;

    uint8_t pos_x, pos_y, pos_z;
    bool toggle;
    float extend;
    float update_time;
    uint16_t passed_time;

//menu stuff;
    bool m_changed, m_speedSelected, m_clicked;
    int8_t m_curMenuPos;
    uint16_t m_clickdelay;

    void mov();
    Ball( const Ball &c );
    Ball &operator=( const Ball &c );
}; //Ball

#endif //__BALL_H__

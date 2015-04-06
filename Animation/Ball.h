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
#define BALL_UPDATE_TIME 2000.0f
#define BALL_SIZE 4.5f
#define BALL_MIN_UPDATE_TIME 200.0f
#define BALL_SPEED_CHANGE_SPEED 25.0f
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
protected:
private:
    Cube *cube;
    RGB color;

    uint8_t pos_x, pos_y, pos_z;
    bool toggle;
    float extend;
    float update_time;
    uint16_t passed_time;

//menu stuff;
    bool m_changed, m_speedSelected, m_clicked;
    uint8_t m_curMenuPos;
    uint16_t m_clickdelay;

    void mov();
    Ball( const Ball &c );
    Ball &operator=( const Ball &c );


}; //Ball

#endif //__BALL_H__

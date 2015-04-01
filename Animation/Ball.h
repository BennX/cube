/*
* Ball.h
*
* Created: 30.03.2015 19:34:25
* Author: Benjamin
*/


#ifndef __BALL_H__
#define __BALL_H__

#include "Animation.h"
#include "../Cube.h"
#define BALL_UPDATE_TIME 4000.0f
#define BALL_SIZE 4.0f
class Ball : public Animation
{
public:
    Ball(Cube *c);
    ~Ball();
    void update(const uint16_t &delta);
protected:
private:
    Cube *cube;
    RGB color;

    uint8_t pos_x, pos_y, pos_z;
    bool toggle;
    float extend;
    float update_time;
    uint16_t passed_time;

    void mov();
    Ball( const Ball &c );
    Ball &operator=( const Ball &c );


}; //Ball

#endif //__BALL_H__

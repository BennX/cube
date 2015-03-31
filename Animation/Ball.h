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
#include "../Input.h"
#define BALL_UPDATE_TIME 500.0f
#define BALL_SIZE 6.0f
class Ball : public Animation
{
public:
    Ball(Cube *c, Input *i);
    ~Ball();
    void update(const short &delta);
protected:
private:
    Cube *cube;
    Input *input;

    RGB color;

    uint8_t pos_x, pos_y, pos_z;
    bool toggle;
    float extend;
    float update_time;

    void mov();
    Ball( const Ball &c );
    Ball &operator=( const Ball &c );


}; //Ball

#endif //__BALL_H__

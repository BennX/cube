/*
* Ball.cpp
*
* Created: 30.03.2015 19:34:25
* Author: Benjamin
*/


#include "Ball.h"
#include "../Util/Random.h"
#include <math.h>
// default constructor
Ball::Ball(Cube *c, Input *i): cube(c), pos_x(1), pos_y(1), pos_z(1), extend(0),
    toggle(true), input(i), update_time(UPDATE_TIME)
{
    color.r = rnd(MAX_COLOR);
    color.g = rnd(MAX_COLOR);
    color.b = rnd(MAX_COLOR);
} //Ball

// default destructor
Ball::~Ball()
{
} //~Ball

void Ball::update(const short &delta)
{
    int8_t u = input->getIncDelta();
    if(update_time + u * 25.0 > UPDATE_TIME)
        update_time += u * 25.0;

    if(toggle)
    {
        extend += delta / update_time;
    }
    else
    {
        extend -= delta / update_time;
    }
    for (uint8_t x = 0; x < 5; x++)
    {
        for (uint8_t y = 0; y < 5; y++)
        {
            for (uint8_t z = 0; z < 5; z++)
            {
                if(sqrt(pow(sqrt(pow(pos_x - x, 2) + pow(pos_y - y,
                                 2) + pow(pos_z - z, 2)) - extend, 2)) < 0.5f)
                {
                    cube->setRGB(x, y, z, color);
                }
                else
                {
                    cube->setRGB(x, y, z, 0, 0, 0);
                }
            }
        }
    }
    if(extend > BALL_SIZE || extend < 0)
    {
        if(toggle)
        {
            toggle = false;
        }
        else
        {
            toggle = true;
            mov();
        }

        color.r = rnd(MAX_COLOR);
        color.g = rnd(MAX_COLOR);
        color.b = rnd(MAX_COLOR);
    }
}
void Ball::mov()
{
    switch(rnd(6))
    {
        case 0:
            if(pos_x - 1 >= 0)
                pos_x--;
            else
                mov();
            break;
        case 1:
            if(pos_x + 1 < 5)
                pos_x++;
            else
                mov();
            break;
        case 2:
            if(pos_y - 1 >= 0)
                pos_y--;
            else
                mov();
            break;
        case 3:
            if(pos_y + 1 < 5)
                pos_y++;
            else
                mov();
            break;
        case 4:
            if(pos_z - 1 >= 0)
                pos_z--;
            else
                mov();
            break;
        case 5:
            if(pos_z + 1 < 5)
                pos_z++;
            else
                mov();
            break;
    }
}
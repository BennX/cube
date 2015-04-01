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
Ball::Ball(Cube *c): cube(c), pos_x(1), pos_y(1), pos_z(1), extend(0.0f),
    toggle(true), update_time(BALL_UPDATE_TIME), passed_time(0)
{
    color.r = rnd(MAX_COLOR);
    color.g = rnd(MAX_COLOR);
    color.b = rnd(MAX_COLOR);
} //Ball

// default destructor
Ball::~Ball()
{
} //~Ball

void Ball::update(const uint16_t &delta)
{
    passed_time += delta;

    extend = BALL_SIZE * (-pow(passed_time / update_time - 1, 2) + 1);

    if(extend <= 0)
    {
        passed_time = 0;
        mov();
        color.r = rnd(MAX_COLOR);
        color.g = rnd(MAX_COLOR);
        color.b = rnd(MAX_COLOR);
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
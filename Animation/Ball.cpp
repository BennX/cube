/*
* Ball.cpp
*
* Created: 30.03.2015 19:34:25
* Author: Benjamin
*/


#include "Ball.h"
#include "../Util/Random.h"
#include "../Util/PStrings.h"
#include <math.h>


// default constructor
Ball::Ball(Cube &c, const uint8_t &id): Animation(id), cube(c), pos_x(1),
    pos_y(1), pos_z(1), extend(0.0f), update_time(START_UPDATE_TIME),
    passed_time(0), m_max_size(MAX_SIZE),m_max_size_rnd(0.0f),m_max_size_rnd_max(1.0f), m_submenu(PSTR("Ball Animation"), id)
{
    color.r = rnd(MAX_COLOR);
    color.g = rnd(MAX_COLOR);
    color.b = rnd(MAX_COLOR);

    //add the manipulators to the submenu
    m_submenu.addEntry(p_strings::speed, &update_time, MIN_UPDATE_TIME, 5000.0f,
                       UPDATE_TIME_CHANGE);
    m_submenu.addEntry(p_strings::size, &m_max_size, 0, MAX_SIZE, 0.1f);
	m_submenu.addEntry(p_strings::rnd, &m_max_size_rnd_max, 0, MAX_SIZE_RND, 0.1f);
} //Ball

// default destructor
Ball::~Ball()
{
} //~Ball

void Ball::update(const uint16_t &delta)
{
    passed_time += delta;

    extend = (m_max_size + m_max_size_rnd) *(-pow(passed_time / update_time - 1, 2) + 1);

    if(extend <= 0)
    {
        m_max_size_rnd = m_max_size_rnd_max*rnd()/255.0;
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
                    cube.setRGB(x, y, z, color);
                }
                else
                {
                    cube.setRGB(x, y, z, 0, 0, 0);
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

void Ball::updateEntry(const uint16_t &delta, Input &i, Menu &m)
{
    m_submenu.update(delta, i, m);
}

bool Ball::subMenu()
{
    return true;
}
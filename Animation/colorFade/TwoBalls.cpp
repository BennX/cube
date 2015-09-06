/*
* RandomColorFade.cpp
*
* Created: 05.09.2015 13:07:26
* Author: Benjamin
*/


#include "TwoBalls.h"
#include "../../Cube.h"
#include "../../Util/PStrings.h"
#include "../../Display.h"
#include <math.h>

//const uint16_t RandomColorFade::m_changeSpeed = 100;
//const uint16_t RandomColorFade::m_stayTime = 5000;
// default constructor
TwoBalls::TwoBalls(const uint8_t& id): Submenu(PSTR("Two Balls"), id), Animation(id), m_done(false),
    m_changeSpeed(100), m_stayTime(5000), m_range(2.0f), m_moveSpeed(250.0f)
{
    m_color0.random();
    m_color1.random();
    m_color0Target.random();
    m_color1Target.random();

    //set them fixed at first
    m_p0.rnd() *= 4.0f; //to make it max 5 vectors
    m_p1.rnd() *= 4.0f;
    m_direction0.rnd();
    m_direction1.rnd();

    Submenu::addEntry(p_strings::speed, &m_changeSpeed, 0, 500, 10);
    Submenu::addEntry(PSTR("Stay: "), &m_stayTime, 0, 50000, 25);
    Submenu::addEntry(p_strings::speed, &m_moveSpeed, 25, 2500, 25);
    Submenu::addEntry(PSTR("Size: "), &m_range, 0, 4.0f, 0.1f);
} //RandomColorFade

// default destructor
TwoBalls::~TwoBalls()
{
} //~RandomColorFade

void TwoBalls::update(const uint16_t& delta)
{
    //retarget
    if(m_color0 == m_color0Target)
    {
        m_timerCol0 += delta;
        if(m_timerCol0 > m_stayTime)
        {
            m_timerCol0 = 0;
            m_color0Target.random();
        }
    }
    if(m_color1 == m_color1Target)
    {
        m_timerCol1 += delta;
        if(m_timerCol1 > m_stayTime)
        {
            m_timerCol1 = 0;
            m_color1Target.random();
        }
    }

    m_p0 += (m_direction0 * ((float)delta / m_moveSpeed));
    m_p1 += (m_direction1 * ((float)delta / m_moveSpeed));
    checkCollision(m_p0, m_direction0);
    checkCollision(m_p1, m_direction1);

    m_timer += delta;
    if(m_timer >= m_changeSpeed)
    {
        m_timer = 0;
        //change the color
        updateColor(m_color0, m_color0Target);
        updateColor(m_color1, m_color1Target);

        for(int8_t x = 0; x < 5; x++)
        {
            for(int8_t y = 0; y < 5; y++)
            {
                for(int8_t z = 0; z < 5; z++)
                {
                    float distanceToP0 = sqrt(pow((float)x - m_p0.x, 2) + pow((float)y - m_p0.y, 2) + pow((float)z - m_p0.z, 2));
                    float distanceToP1 = sqrt(pow((float)x - m_p1.x, 2) + pow((float)y - m_p1.y, 2) + pow((float)z - m_p1.z, 2));

                    if(distanceToP0 < m_range && distanceToP1 > m_range)
                    {
                        RGB dotCol = m_color0 * (1.0f - (distanceToP0 / m_range));
                        Cube::getInstance().setRGB(x, y, z, dotCol);
                    }
                    else if(distanceToP0 > m_range && distanceToP1 < m_range)
                    {
                        RGB dotCol = m_color1 * (1.0f - (distanceToP1 / m_range));
                        Cube::getInstance().setRGB(x, y, z, dotCol);
                    }
                    else if(distanceToP0 < m_range && distanceToP1 < m_range)
                    {
                        //in range of both so add up
                        RGB dotCol = m_color0 * (1.0f - (distanceToP0 / m_range)) * 0.5f + m_color1 * (1.0f - (distanceToP1 / m_range)) * 0.5f;
                        Cube::getInstance().setRGB(x, y, z, dotCol);
                    }
                    else
                    {
                        //nothing in range so make it off
                        Cube::getInstance().setRGB(x, y, z, RGB());
                    }
                }
            }
        }
    }
}

void TwoBalls::updateColor(RGB& r, const RGB& target)
{
    if(r.r < target.r)
        r.r++;
    if(r.r > target.r)
        r.r--;
    if(r.g < target.g)
        r.g++;
    if(r.g > target.g)
        r.g--;
    if(r.b < target.b)
        r.b++;
    if(r.b > target.b)
        r.b--;
}

void TwoBalls::checkCollision(const Vector& v, Vector& direction)
{
    //only can collide once!
    //first check
    if(v.x <= 0.0) //if smaller 0 change into +
    {
        if(direction.x < 0)
            direction.x *= -1;
        return;
    }
    if(v.x >= 4.0)
    {
        if(direction.x > 0.0)
            direction.x *= -1;
        return;
    }

    if(v.y <= 0.0) //if smaller 0 change into +
    {
        if(direction.y < 0)
            direction.y *= -1;
        return;
    }
    if(v.y >= 4.0)
    {
        if(direction.y > 0.0)
            direction.y *= -1;
        return;
    }

    if(v.z <= 0.0) //if smaller 0 change into +
    {
        if(direction.z < 0)
            direction.z *= -1;
        return;
    }
    if(v.z >= 4.0)
    {
        if(direction.z > 0.0)
            direction.z *= -1;
        return;
    }
}

void TwoBalls::print(const Vector& v, const uint8_t& col)
{
    Display::out(0, col) << v.x;
    Display::out(1, col) << v.y;
    Display::out(2, col) << v.z;
}
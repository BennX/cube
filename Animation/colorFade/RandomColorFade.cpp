/*
* RandomColorFade.cpp
*
* Created: 05.09.2015 13:07:26
* Author: Benjamin
*/


#include "RandomColorFade.h"
#include "../../Cube.h"
#include "../../Util/PStrings.h"
#include <math.h>

//const uint16_t RandomColorFade::m_changeSpeed = 100;
//const uint16_t RandomColorFade::m_stayTime = 5000;
// default constructor
RandomColorFade::RandomColorFade(const uint8_t &id): Submenu(PSTR("Random Fade"),id), Animation(id), m_done(false),m_changeSpeed(100), m_stayTime(5000)
{
    m_color0.random();
    m_color1.random();
    //set them fixed at first
    m_p0.x = 0;
    m_p0.y = 0;
    m_p0.z = 0;
    m_p1.x = 4;
    m_p1.y = 4;
    m_p1.z = 4;
    Submenu::addEntry(p_strings::speed, &m_changeSpeed,0,500,10);
	Submenu::addEntry(PSTR("Stay: "), &m_stayTime,0,50000,25);
} //RandomColorFade

// default destructor
RandomColorFade::~RandomColorFade()
{
} //~RandomColorFade

void RandomColorFade::update(const uint16_t &delta)
{
    //retarget
    if(m_color0 == m_color0Target)
    {
        m_timerCol0+=delta;
        if(m_timerCol0>m_stayTime)
        {
            m_timerCol0=0;
            m_color0Target.random();
        }
    }
    if(m_color1 == m_color1Target)
    {
        m_timerCol1+=delta;
        if(m_timerCol1>m_stayTime)
        {
            m_timerCol1=0;
            m_color1Target.random();
        }
    }

    m_timer+=delta;
    if(m_timer >=m_changeSpeed)
    {
        m_timer = 0;
        //change the color
        updateColor(m_color0,m_color0Target);
        updateColor(m_color1,m_color1Target);

        for (int8_t x = 0; x<5; x++)
        {
            for (int8_t y = 0; y<5; y++)
            {
                for (int8_t z = 0; z<5; z++)
                {
                    float distanceToP0 = sqrt(pow((float)x-m_p0.x,2)+pow((float)y-m_p0.y,2)+pow((float)z-m_p0.z,2));
                    float distanceToP1 = sqrt(pow((float)x-m_p1.x,2)+pow((float)y-m_p1.y,2)+pow((float)z-m_p1.z,2));
                    //float relative =sqrt(pow((float)m_p1.x-m_p0.x,2)+pow((float)m_p1.y-m_p0.y,2)+pow((float)m_p1.z-m_p0.z,2));
                    float relative = distanceToP0+distanceToP1;
                    RGB dotCol = m_color0*(distanceToP0/relative)+m_color1*(distanceToP1/relative);
                    Cube::getInstance().setRGB(x,y,z,dotCol);
                }
            }
        }
    }
}

void RandomColorFade::updateColor(RGB &r, const RGB &target)
{
    if(r.r < target.r)
        r.r++;
    if(r.r>target.r)
        r.r--;
    if(r.g<target.g)
        r.g++;
    if(r.g>target.g)
        r.g--;
    if(r.b<target.b)
        r.b++;
    if(r.b>target.b)
        r.b--;
}
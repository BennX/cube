#include "RandomFade.h"
#include "../../Cube.h"
#include "../../Util/PStrings.h"
#include <math.h>

//const uint16_t RandomColorFade::m_changeSpeed = 100;
//const uint16_t RandomColorFade::m_stayTime = 5000;
// default constructor
RandomFade::RandomFade(const uint8_t& id): Submenu(PSTR("Random Fade"), id), Animation(id), m_done(false),
    m_changeSpeed(10), m_stayTime(5), m_moveSpeed(1000.0f)
{
    Submenu::addEntry(p_strings::speed, &m_changeSpeed, 0, 500, 10);
    Submenu::addEntry(PSTR("Stay: "), &m_stayTime, 0, 60, 1);
    Submenu::addEntry(p_strings::speed, &m_moveSpeed, 50.0f, 4000.0f, 25.0f);
} //RandomColorFade

// default destructor
RandomFade::~RandomFade()
{
} //~RandomColorFade

void RandomFade::update(const uint16_t& delta)
{
    if(!m_done)
    {
        //init on runtime to always have a different effect
        m_color0.random();
        m_color1.random();
        m_color0Target.random();
        m_color1Target.random();

        //random start position
        m_p0.rnd(4.0f);
        m_p1.rnd(4.0f);

        //call random till they have minimum of 0.5 as speed
        //so nothing moves "TOO slow"
        while(m_direction0.rnd().norm() < 0.5f)
            ;
        while(m_direction1.rnd().norm() < 0.5f)
            ;
        m_done = true;
    }

    //retarget
    if(m_color0 == m_color0Target)
    {
        m_timerCol0 += delta;
        if(m_timerCol0 > m_stayTime * 1000)
        {
            m_timerCol0 = 0;
            m_color0Target.random();
        }
    }
    if(m_color1 == m_color1Target)
    {
        m_timerCol1 += delta;
        if(m_timerCol1 > m_stayTime * 1000)
        {
            m_timerCol1 = 0;
            m_color1Target.random();
        }
    }

    //
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
                    //check if this point is behind the other seen from p0 oder p1
                    // and colorize it just by that color
                    // if its between these 2 points
                    //colorize it depending on the distance

                    Vector curPos(x, y, z);

                    //calculate the vectors between the points
                    Vector linep0p1(m_p1 - m_p0);

                    //calc plannorms since they are the same just invert one.
                    Vector planeNormp1p0(linep0p1);
                    planeNormp1p0.nor();
                    Vector planeNormp0p1(planeNormp1p0);
                    planeNormp0p1 *= -1;

                    //calc the vector to the point we check
                    Vector vectorToPos0(curPos - m_p0);
                    Vector vectorToPos1(curPos - m_p1);

                    //dot it with the normals of the "planes"
                    float dotPos0Planp0p1 = vectorToPos0.dot(planeNormp0p1);
                    float dotPos1Planp1p0 = vectorToPos1.dot(planeNormp1p0);

                    if(dotPos0Planp0p1 < 0 && dotPos1Planp1p0 > 0)
                    {
                        //behind p1 seen from p0!
                        Cube::getInstance().setRGB(curPos, m_color1);
                    }
                    else if(dotPos1Planp1p0 < 0 && dotPos0Planp0p1 > 0)
                    {
                        //behind p0 seen from p1
                        Cube::getInstance().setRGB(curPos, m_color0);
                    }
                    else
                    {
                        //between
                        float distanceToP0 = curPos.dist(m_p0);
                        float distanceToP1 = curPos.dist(m_p1);
                        float relative = distanceToP0 + distanceToP1;
                        RGB dotCol = m_color0 * (1.0f - (distanceToP0 / relative)) + m_color1 * (1.0f - (distanceToP1 / relative));
                        Cube::getInstance().setRGB(curPos, dotCol);
                    }
                }
            }
        }
    }
}

void RandomFade::updateColor(RGB& r, const RGB& target)
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
void RandomFade::checkCollision(const Vector& v, Vector& direction)
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


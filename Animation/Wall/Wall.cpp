/*
* Wall.cpp
*
* Created: 26.04.2015 18:16:37
* Author: Benjamin
*/


#include "Wall.h"
#include "../../Util/Random.h"
#include "../../Util/PStrings.h"
// default constructor
Wall::Wall(Cube& c, const uint8_t& id) : Animation(id), m_cube(c),
    m_submenu(PSTR("Rain Animation"), id), m_direction(0), m_position(0),
    m_timer(0), m_updatetime(START_UPDATE_TIME), m_probability(START_PROBABILITY),
    m_doneCounter(0), m_directionToggle(true)
{
    m_submenu.addEntry(p_strings::rate, &m_probability, 0, 100, 1);
    m_submenu.addEntry(p_strings::speed, &m_updatetime, 0, 25000, 1);
    setDotsToDirection();
} //Wall

// default destructor
Wall::~Wall()
{
} //~Wall

void Wall::update(const uint16_t& delta)
{
    m_timer += delta;
    if(m_timer > m_updatetime)
    {
        m_timer = 0;
        for (uint8_t i = 0; i < 25; i++)
        {
            switch(m_direction)
            {
                case 0:
                {
                    if(m_dots[i].m_z == 4)
                    {
                        if(rnd(100) < m_probability)
                        {
                            //clear old dot
                            m_cube(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z) = RGB(0, 0, 0);
                            m_dots[i].m_z--;
                            setColor(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z, 4 / 5.0 );
                        }
                        break;
                    }
                    else if(m_dots[i].m_z == 0)
                    {
                        m_doneCounter++;
                        if(m_doneCounter == 25)
                        {
                            if(!m_directionToggle)
                            {
                                m_cube.off();
                                m_direction = rnd(6);
                                m_directionToggle = true;
                            }
                            else
                            {
                                m_direction = 1;
                                m_directionToggle = false;
                            }
                            setDotsToDirection();
                            m_doneCounter = 0;
                        }
                        break;
                    }

                    //not finished and not start of dot i
                    m_cube(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z) = RGB(0, 0, 0);
                    m_dots[i].m_z--;
                    setColor(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z, m_dots[i].m_z / 5.0 );
                }
                break;

                case 1:
                {
                    if(m_dots[i].m_z == 0)
                    {
                        if(rnd(100) < m_probability)
                        {
                            //clear old dot
                            m_cube(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z) = RGB(0, 0, 0);
                            m_dots[i].m_z++;
                            setColor(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z, 4 / 5.0 );
                        }
                        break;
                    }
                    else if(m_dots[i].m_z == 4)
                    {
                        m_doneCounter++;
                        if(m_doneCounter == 25)
                        {
                            if(!m_directionToggle)
                            {
                                m_cube.off();
                                m_direction = rnd(6);
                                m_directionToggle = true;
                            }
                            else
                            {
                                m_direction = 0;
                                m_directionToggle = false;
                            }
                            setDotsToDirection();
                            m_doneCounter = 0;
                        }
                        break;
                    }

                    //not finished and not start of dot i
                    m_cube(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z) = RGB(0, 0, 0);
                    m_dots[i].m_z++;
                    setColor(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z,
                             (5 - m_dots[i].m_z) / 5.0 );
                }
                break;

                case 2:
                {
                    if(m_dots[i].m_x == 4)
                    {
                        if(rnd(100) < m_probability)
                        {
                            //clear old dot
                            m_cube(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z) = RGB(0, 0, 0);
                            m_dots[i].m_x--;
                            setColor(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z, 4 / 5.0 );
                        }
                        break;
                    }
                    else if(m_dots[i].m_x == 0)
                    {
                        m_doneCounter++;
                        if(m_doneCounter == 25)
                        {
                            if(!m_directionToggle)
                            {
                                m_cube.off();
                                m_direction = rnd(6);
                                m_directionToggle = true;
                            }
                            else
                            {
                                m_direction = 3;
                                m_directionToggle = false;
                            }
                            setDotsToDirection();
                            m_doneCounter = 0;
                        }
                        break;
                    }

                    //not finished and not start of dot i
                    m_cube(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z) = RGB(0, 0, 0);
                    m_dots[i].m_x--;
                    setColor(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z, m_dots[i].m_x / 5.0 );
                }
                break;
                case 3:
                {
                    if(m_dots[i].m_x == 0)
                    {
                        if(rnd(100) < m_probability)
                        {
                            //clear old dot
                            m_cube(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z) = RGB(0, 0, 0);
                            m_dots[i].m_x++;
                            setColor(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z, 4 / 5.0 );
                        }
                        break;
                    }
                    else if(m_dots[i].m_x == 4)
                    {
                        m_doneCounter++;
                        if(m_doneCounter == 25)
                        {
                            if(!m_directionToggle)
                            {
                                m_cube.off();
                                m_direction = rnd(6);
                                m_directionToggle = true;
                            }
                            else
                            {
                                m_direction = 2;
                                m_directionToggle = false;
                            }
                            setDotsToDirection();
                            m_doneCounter = 0;
                        }
                        break;
                    }

                    //not finished and not start of dot i
                    m_cube(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z) = RGB(0, 0, 0);
                    m_dots[i].m_x++;
                    setColor(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z,
                             (5 - m_dots[i].m_x) / 5.0 );
                }
                break;

                case 4:
                {
                    if(m_dots[i].m_y == 4)
                    {
                        if(rnd(100) < m_probability)
                        {
                            //clear old dot
                            m_cube(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z) = RGB(0, 0, 0);
                            m_dots[i].m_y--;
                            setColor(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z, 4 / 5.0 );
                        }
                        break;
                    }
                    else if(m_dots[i].m_y == 0)
                    {
                        m_doneCounter++;
                        if(m_doneCounter == 25)
                        {
                            if(!m_directionToggle)
                            {
                                m_cube.off();
                                m_direction = rnd(6);
                                m_directionToggle = true;
                            }
                            else
                            {
                                m_direction = 5;
                                m_directionToggle = false;
                            }
                            setDotsToDirection();
                            m_doneCounter = 0;
                        }
                        break;
                    }

                    //not finished and not start of dot i
                    m_cube(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z) = RGB(0, 0, 0);
                    m_dots[i].m_y--;
                    setColor(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z, m_dots[i].m_y / 5.0 );
                }
                break;

                case 5:
                {
                    if(m_dots[i].m_y == 0)
                    {
                        if(rnd(100) < m_probability)
                        {
                            //clear old dot
                            m_cube(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z) = RGB(0, 0, 0);
                            m_dots[i].m_y++;
                            setColor(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z, 4 / 5.0 );
                        }
                        break;
                    }
                    else if(m_dots[i].m_y == 4)
                    {
                        m_doneCounter++;
                        if(m_doneCounter == 25)
                        {
                            if(!m_directionToggle)
                            {
                                m_cube.off();
                                m_direction = rnd(6);
                                m_directionToggle = true;
                            }
                            else
                            {
                                m_direction = 4;
                                m_directionToggle = false;
                            }
                            setDotsToDirection();
                            m_doneCounter = 0;
                        }
                        break;
                    }

                    //not finished and not start of dot i
                    m_cube(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z) = RGB(0, 0, 0);
                    m_dots[i].m_y++;
                    setColor(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z,
                             (5 - m_dots[i].m_y) / 5.0 );
                }
                break;
            }
        }
        m_doneCounter = 0;
    }
}

void Wall::updateEntry(const uint16_t& delta, Input& i, Menu& m)
{
    m_submenu.update(delta, i, m);
}

bool Wall::subMenu()
{
    return true;
}

void Wall::setColor(const uint8_t& x, const uint8_t& y, const uint8_t& z,
                    const float& v)
{
    m_cube(x, y, z) = m_color * v + m_targetColor * (1 - v);
}

void Wall::setDotsToDirection()
{
    switch (m_direction)
    {
        case 0:
            //top
            for (uint8_t i = 0; i < 5; i++)
            {
                for (uint8_t j = 0; j < 5; j++)
                {
                    m_dots[(i * 5) + j].m_x = i;
                    m_dots[(i * 5) + j].m_y = j;
                    m_dots[(i * 5) + j].m_z = 4;
                }
            }
            break;
        case 1:
            //down
            for (uint8_t i = 0; i < 5; i++)
            {
                for (uint8_t j = 0; j < 5; j++)
                {
                    m_dots[(i * 5) + j].m_x = i;
                    m_dots[(i * 5) + j].m_y = j;
                    m_dots[(i * 5) + j].m_z = 0;
                }
            }
            break;
        case 2:
            //left
            for (uint8_t i = 0; i < 5; i++)
            {
                for (uint8_t j = 0; j < 5; j++)
                {
                    m_dots[(i * 5) + j].m_x = 4;
                    m_dots[(i * 5) + j].m_y = i;
                    m_dots[(i * 5) + j].m_z = j;
                }
            }
            break;
        case 3:
            //right
            for (uint8_t i = 0; i < 5; i++)
            {
                for (uint8_t j = 0; j < 5; j++)
                {
                    m_dots[(i * 5) + j].m_x = 0;
                    m_dots[(i * 5) + j].m_y = i;
                    m_dots[(i * 5) + j].m_z = j;
                }
            }


            break;
        case 4:
            //back
            for (uint8_t i = 0; i < 5; i++)
            {
                for (uint8_t j = 0; j < 5; j++)
                {
                    m_dots[(i * 5) + j].m_x = i;
                    m_dots[(i * 5) + j].m_y = 4;
                    m_dots[(i * 5) + j].m_z = j;
                }
            }
            break;
        case 5:
            //front
            for (uint8_t i = 0; i < 5; i++)
            {
                for (uint8_t j = 0; j < 5; j++)
                {
                    m_dots[(i * 5) + j].m_x = i;
                    m_dots[(i * 5) + j].m_y = 0;
                    m_dots[(i * 5) + j].m_z = j;
                }
            }
            break;
    }

    m_color = m_targetColor;

    m_targetColor.random();
    for(uint8_t i = 0; i < 25; i++)
    {
        m_cube(m_dots[i].m_x, m_dots[i].m_y, m_dots[i].m_z) =  m_color;
    }
    return;
}

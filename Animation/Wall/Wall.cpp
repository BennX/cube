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
Wall::Wall(Cube &c, const uint8_t &id) : Animation(id), m_cube(c),
    m_submenu(PSTR("Rain Animation"), id), m_direction(0), m_position(0),
    m_timer(0), m_updatetime(START_UPDATE_TIME)
{
    m_color.r = rnd(MAX_COLOR);
    m_color.g = rnd(MAX_COLOR);
    m_color.b = rnd(MAX_COLOR);

    m_targetColor.r = rnd(MAX_COLOR);
    m_targetColor.g = rnd(MAX_COLOR);
    m_targetColor.b = rnd(MAX_COLOR);
} //Wall

// default destructor
Wall::~Wall()
{
} //~Wall

void Wall::update(const uint16_t &delta)
{
    m_timer += delta;
    if(m_timer > m_updatetime)
    {

    }
}

void Wall::updateEntry(const uint16_t &delta, Input &i, Menu &m)
{
    m_submenu.update(delta, i, m);
}

bool Wall::subMenu()
{
    return true;
}
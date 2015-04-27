/*
* Wall.h
*
* Created: 26.04.2015 18:16:37
* Author: Benjamin
*/


#ifndef __WALL_H__
#define __WALL_H__
#include "../../Cube.h"
#include "../Animation.h"
#include "../../Menu/MenuEntry.h"
#include "../../Menu/Submenu.h"


class Wall: public Animation, public MenuEntry
{
//functions
public:
    Wall(Cube &c, const uint8_t &id);
    ~Wall();

    void update(const uint16_t &delta);
    //menu stuff
    void updateEntry(const uint16_t &delta, Input &i, Menu &m);
    PGM_P name()
    {
        return PSTR("Wall");
    };
    bool subMenu();

private:
    struct Dot
    {
        uint8_t m_x, m_y, m_z;
    };

    //variables
    Cube &m_cube;
    Submenu m_submenu;

    //the direction of the wall movement
    // there are 6 directions!
    uint8_t m_direction;
    //current distance from the start
    uint8_t m_position;
    //the regular update timer
    uint16_t m_timer;
    //the value with the update time since it can be changed by the menu
    int16_t m_updatetime;
    //current probability to start moving
    int8_t m_probability;
    uint8_t m_doneCounter;

    bool m_directionToggle;

    RGB m_color; //current color
    RGB m_targetColor; // color when arived at target

    Dot m_dots[25];

    //static settings
    static const uint16_t START_UPDATE_TIME;
    static const uint8_t START_PROBABILITY;

    Wall( const Wall &c );
    Wall &operator=( const Wall &c );

    void setDotsToDirection();
    void setColor(const uint8_t &x, const uint8_t &y, const uint8_t &z,
                  const float &v);
}; //Wall

#endif //__WALL_H__

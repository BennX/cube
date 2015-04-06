/*
* SingleColor.h
*
* Created: 06.04.2015 13:13:57
* Author: Benjamin
*/


#ifndef __SINGLECOLOR_H__
#define __SINGLECOLOR_H__
#include "Animation.h"
#include "../Menu/MenuEntry.h"
#include "../Cube.h"
class SingleColor: public Animation, public MenuEntry
{
//functions
public:
    SingleColor(Cube *c, const uint8_t &id);
    ~SingleColor();
    void update(const uint16_t &delta);

    void updateEntry(const uint16_t &delta, Input &i, Menu &m);
    PGM_P name()
    {
        return PSTR("Single");
    }
    bool subMenu();

private:
    SingleColor( const SingleColor &c );
    SingleColor &operator=( const SingleColor &c );
    Cube *cube;
    bool m_changed;
	bool m_menuChanged;
    RGB m_color;

    int8_t m_curMenuPos;
	uint8_t m_selected;
	bool m_somethingSelected;
	bool m_clicked;
	uint16_t m_clickdelay;

}; //SingleColor

#endif //__SINGLECOLOR_H__

/*
* FontAnimation.cpp
*
* Created: 03.04.2015 16:33:30
* Author: Benjamin
*/


#include "FontAnimation.h"
#include "../../Util/Random.h"
#include "../../Display.h"
#include <string.h>
// default constructor
FontAnimation::FontAnimation(Cube *c, const uint8_t &id): Animation(id), cube(c),
    cur_letter(TO_SHOW_STRING)
{
    color.r = rnd(MAX_COLOR);
    color.g = rnd(MAX_COLOR);
    color.b = rnd(MAX_COLOR);
} //FontAnimation

// default destructor
FontAnimation::~FontAnimation()
{
} //~FontAnimation

void FontAnimation::update(const uint16_t &delta)
{
    counter += delta;
    if(counter > LETTER_UPDATE_TIME)
    {
        counter = 0;
        Letter l = font.get(*cur_letter);
        uint8_t count = l.count;

        for (uint8_t x = 0; x < 5; x++)
        {
            for (uint8_t y = 0; y < 5; y++)
            {
                cube->setRGB(x, y, 0, 0, 0, 0);
            }
        }

        for(uint8_t i = 0; i < count; i++)
        {
            cube->setRGB(l.pixel[i].x, l.pixel[i].y, 0, color);
        }

        if(*cur_letter++ == '\n')
            cur_letter -= strlen(TO_SHOW_STRING);

        color.r = rnd(MAX_COLOR);
        color.g = rnd(MAX_COLOR);
        color.b = rnd(MAX_COLOR);
    }
}

void FontAnimation::updateEntry(const uint16_t &delta, Input &i,
                                Menu &m)
{
}
bool FontAnimation::subMenu()
{
    return false;
}
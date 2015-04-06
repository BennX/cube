/*
* FontAnimation.h
*
* Created: 03.04.2015 16:33:31
* Author: Benjamin
*/


#ifndef __FONTANIMATION_H__
#define __FONTANIMATION_H__
#include <avr/io.h>
#include "../Animation.h"
#include "../../Menu/MenuEntry.h"

#include "Font.h"
#include "../../Cube.h"

#define TO_SHOW_STRING  "KRISTINA\n"
#define LETTER_UPDATE_TIME 750
class FontAnimation : public Animation, public MenuEntry
{
public:
    FontAnimation(Cube *c, const uint8_t &id);
    ~FontAnimation();
    void update(const uint16_t &delta);
    //menu stuff
    void updateEntry(const uint16_t &delta, Input &i, Menu &m);
    PGM_P name()
    {
        return PSTR("Font");
    };
    bool subMenu();
private:
    Font font;
    Cube *cube;
    RGB color;
    FontAnimation( const FontAnimation &c );
    FontAnimation &operator=( const FontAnimation &c );
    char *cur_letter;
    uint16_t counter;
}; //FontAnimation

#endif //__FONTANIMATION_H__

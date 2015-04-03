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
#include "Font.h"
#include "../../Cube.h"

#define TO_SHOW_STRING  "KRISTINA\n"
#define LETTER_UPDATE_TIME 750
class FontAnimation : public Animation
{
public:
    FontAnimation(Cube *c);
    ~FontAnimation();
    void update(const uint16_t &delta);
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

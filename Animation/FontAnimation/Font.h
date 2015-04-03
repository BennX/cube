/*
* Font.h
*
* Created: 03.04.2015 16:18:12
* Author: Benjamin
*/


#ifndef __FONT_H__
#define __FONT_H__
#include <avr/io.h>
struct Pixel
{
    uint8_t x, y;
};

struct Voxel
{
    uint8_t x, y, z;
};

struct Letter
{
    uint8_t count;
    Pixel pixel[20];
};

class Font
{
//functions
public:
    Font();
    ~Font();
    Letter get(const unsigned char &a);
private:
    Font( const Font &c );
    Font &operator=( const Font &c );
    Letter letters[26];
}; //Font

#endif //__FONT_H__

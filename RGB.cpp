/*
* RGB.cpp
*
* Created: 27.04.2015 15:16:57
* Author: Benjamin
*/


#include "RGB.h"
#include "Util/Random.h"
RGB::RGB() : r(0), g(0), b(0)
{
}
// default constructor
RGB::RGB(uint8_t r, uint8_t g, uint8_t b)
{
    this->r = r % MAX_COLOR_RGB;
    this->g = g % MAX_COLOR_RGB;
    this->b = b % MAX_COLOR_RGB;
} //RGB

RGB::RGB(const uint32_t& hex)
{

    this->b = (hex & 0xFF);
    b %= MAX_COLOR_RGB;
    this->g = ((hex >> 8) & 0xFF);
    g %= MAX_COLOR_RGB;
    this->r = ((hex >> 8) & 0xFF);
    r %= MAX_COLOR_RGB;
} //RGB

bool RGB::operator == (const RGB& other) const
{
    return (r == other.r && g == other.g && b == other.b);
}

RGB RGB::operator+ (const RGB& other) const
{
    return RGB(*this) += other;   //return new
}

RGB& RGB::operator+= (const RGB& other)
{
    r = (r + other.r) % MAX_COLOR_RGB;
    g = (g + other.g) % MAX_COLOR_RGB;
    b = (b + other.b) % MAX_COLOR_RGB;
    return *this;
}

RGB RGB::operator- (const RGB& other) const
{
    return RGB(*this) -= other;   //new
}

RGB& RGB::operator-= (const RGB& other)
{
    r = (r - other.r) % MAX_COLOR_RGB;
    g = (g - other.g) % MAX_COLOR_RGB;
    b = (b - other.b) % MAX_COLOR_RGB;
    return *this;
}

RGB RGB::operator* (const RGB& other) const
{
    return RGB(*this) *= other;   //new
}

RGB& RGB::operator*= (const RGB& other)
{
    r = (r * other.r) % MAX_COLOR_RGB;
    g = (g * other.g) % MAX_COLOR_RGB;
    b = (b * other.b) % MAX_COLOR_RGB;
    //per convention return "yourself"
    return *this;
}

RGB RGB::operator/ (const RGB& other) const
{
    return RGB(*this) /= other;
}

RGB& RGB::operator/= (const RGB& other)
{
    r = (r / other.r) % MAX_COLOR_RGB;
    g = (g / other.g) % MAX_COLOR_RGB;
    b = (b / other.b) % MAX_COLOR_RGB;
    //per convention return "yourself"
    return *this;
}


RGB RGB::operator+ (uint8_t i) const
{
    return 	RGB(*this) += i;   //ret new
}

RGB& RGB::operator+= (uint8_t i)
{
    r = (r + i) % MAX_COLOR_RGB;
    g = (g + i) % MAX_COLOR_RGB;
    b = (b + i) % MAX_COLOR_RGB;
    //per convention return "yourself"
    return *this;
}
RGB RGB::operator- (uint8_t i) const
{
    return RGB(*this) -= i;
}

RGB& RGB::operator-= (uint8_t i)
{
    if(r >= i)
        r = (r - i) % MAX_COLOR_RGB;
    else
        r = 0;

    if(g >= i)
        g = (g - i) % MAX_COLOR_RGB;
    else
        g = 0;

    if( b >= i)
        b = (b - i) % MAX_COLOR_RGB;
    else
        b = 0;
    //per convention return "yourself"
    return *this;
}


RGB RGB::operator* (uint8_t i) const
{
    return RGB(*this) *= i;   //new
}

RGB& RGB::operator*= (uint8_t i)
{
    r = (r * i) % MAX_COLOR_RGB;
    g = (g * i) % MAX_COLOR_RGB;
    b = (b * i) % MAX_COLOR_RGB;
    //per convention return "yourself"
    return *this;
}

RGB& RGB::operator*= (const float& f)
{
    r *= f;
    r %= MAX_COLOR_RGB;
    g *= f;
    g %= MAX_COLOR_RGB;
    b *= f;
    b %= MAX_COLOR_RGB;
    return *this;
}

RGB RGB::operator* (const float& f) const
{
    return RGB(*this) *= f;   //return a new one
}

RGB RGB::operator/ (uint8_t i) const
{
    //per convention return "yourself"
    return RGB(*this) /= i;
}

RGB& RGB::operator/= (uint8_t i)
{
    r /= i;
    r %= MAX_COLOR_RGB;
    g /= i;
    g %= MAX_COLOR_RGB;
    b /= i;
    b %= MAX_COLOR_RGB;
    //per convention return "yourself"
    return *this;
}

RGB RGB::operator/ (const float& f) const
{
    return RGB(*this) /= f;
}

RGB& RGB::operator/= (const float& f)
{
    r /= f;
    r %= MAX_COLOR_RGB;
    g /= f;
    g %= MAX_COLOR_RGB;
    b /= f;
    b %= MAX_COLOR_RGB;
    //per convention return "yourself"
    return *this;
}

void RGB::random()
{
    r = rnd(MAX_COLOR_RGB);
    g = rnd(MAX_COLOR_RGB);
    b = rnd(MAX_COLOR_RGB);
}
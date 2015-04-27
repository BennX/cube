/*
* RGB.h
*
* Created: 27.04.2015 15:16:57
* Author: Benjamin
*/


#ifndef __RGB_H__
#define __RGB_H__
#include <avr/io.h>

class RGB
{
//variables
public:
// the values
    uint8_t r, g, b;

//functions
public:
    RGB();
    RGB(const uint8_t &r, const uint8_t &g, const uint8_t &b);
    //constructor for hex values like
    // 0x000000
    // first 8 bit = r secon 8bit = g last 8bit = b
    explicit RGB(const uint32_t &hex);
    //copy constructor
    RGB( const RGB &c );
    //assignment
    RGB &operator=( const RGB &other );

    RGB &operator+(const RGB &other);
    RGB &operator-(const RGB &other);
    RGB &operator*(const RGB &other);
    RGB &operator/(const RGB &other);

    /**
     * Adds the value to all!
     */
    RGB &operator+(const uint8_t &i);
    /**
    * subs the value to all!
    */
    RGB &operator-(const uint8_t &i);
    /**
    * mult the value to all!
    */
    RGB &operator* (const uint8_t &i);
    RGB &operator* (const float &f);

    /**
    * div the value to all!
    */
    RGB &operator/(const uint8_t &i);
    RGB &operator/(const float &f);

    void random();

    ~RGB();

    friend RGB operator*(const float &, const RGB &);
    friend RGB operator/(const float &, const RGB &);
private:
    static const uint8_t MAX_COLOR_RGB;
}; //RGB

/**
 * right hand operators
 * here they are implemented with the left hand
 * but take care this can cause some issues with negatives!
 * so no negatives with this operators!
 */
RGB operator*(const float &, const RGB &);

#endif //__RGB_H__

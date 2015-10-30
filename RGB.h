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
    RGB(uint8_t r, uint8_t g, uint8_t b);
    //constructor for hex values like
    // 0x000000
    // first 8 bit = r secon 8bit = g last 8bit = b
    explicit RGB(const uint32_t &hex);

    //compare
    bool operator== (const RGB &other) const;


    RGB operator+ (const RGB &other) const;
    RGB &operator+= (const RGB &other);

    RGB operator- (const RGB &other) const;
    RGB &operator-= (const RGB &other);

    RGB operator* (const RGB &other) const;
    RGB &operator*= (const RGB &other);

    RGB operator/ (const RGB &other) const;
    RGB &operator/= (const RGB &other);


    /**
     * Adds the value to all!
     */
    RGB operator+ (uint8_t i) const;
    RGB &operator+= (uint8_t i);
    /**
    * subs the value to all!
    */
    RGB operator- (uint8_t i) const;
    RGB &operator-= (uint8_t i);

    /**
    * mult the value to all!
    */
    RGB operator* (const float &f) const;
    RGB &operator*= (const float &f);

    RGB operator* (uint8_t i) const;
    RGB &operator*= (uint8_t i);


    /**
    * div the value to all!
    */
    RGB operator/ (uint8_t i) const;
    RGB &operator/= (uint8_t i);

    RGB operator/ (const float &f) const;
    RGB &operator/= (const float &f);

    void random();

private:
    static const uint8_t MAX_COLOR_RGB;
}; //RGB


#endif //__RGB_H__

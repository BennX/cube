// Animation.h
#pragma once
#include <avr/io.h>
class Animation
{
public:
    /** update with millis instead of float */
    virtual void update(const uint16_t &delta) = 0;
};
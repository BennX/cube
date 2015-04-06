// Animation.h
#pragma once
#include <avr/io.h>
class Animation
{
protected:
    const uint8_t m_ID;
public:
    Animation(const uint8_t &id): m_ID(id) {};
    /** update with millis instead of float */
    virtual void update(const uint16_t &delta) = 0;
};
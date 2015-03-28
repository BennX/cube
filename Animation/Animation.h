// Animation.h
#pragma once
class Animation
{
public:
    /** update with millis instead of float */
    virtual void update(const short &delta) = 0;
};
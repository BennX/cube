/*
* Animator.cpp
*
* Created: 01.04.2015 10:49:37
* Author: Benjamin
*/


#include "Animator.h"
// default constructor
Animator::Animator(): cur_animation(0)
{
} //Animator

// default destructor
Animator::~Animator()
{
} //~Animator

void Animator::update(const short &delta)
{
    cur_animation->update(delta);
}

void Animator::addAnimation(Animation *a)
{
    if(animations.size() == -1)
        cur_animation = a;
    animations.add(a);
}

bool Animator::operator[](const uint8_t &i)
{
    if(i <= animations.size() && cur_animation_number != i)
    {
        cur_animation_number = i;
        cur_animation = animations[cur_animation_number];
        return true;
    }
    else
    {
        return false;
    }
}

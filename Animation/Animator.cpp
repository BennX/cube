/*
* Animator.cpp
*
* Created: 01.04.2015 10:49:37
* Author: Benjamin
*/


#include "Animator.h"
#include "../Util/Random.h"
// default constructor
Animator::Animator(): cur_animation_number(0), cur_animation(0), m_to_update(0),
    m_autoAnimation(false)
{
} //Animator

// default destructor
Animator::~Animator()
{
} //~Animator

void Animator::update(const short &delta)
{
    //if autoanimation also update this one
    if(m_autoAnimation)
        m_to_update->update(delta);
    //regular update
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
        m_autoAnimation = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool Animator::operator()(const uint8_t &toupdate)
{
    m_to_update = animations[toupdate];//safe the old
    //start a random new one
    while((operator[](rnd(animations.size()))))
    {
    }
    m_autoAnimation = true;
    return m_autoAnimation;
}

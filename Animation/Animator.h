/*
* Animator.h
*
* Created: 01.04.2015 10:49:37
* Author: Benjamin
*/


#ifndef __ANIMATOR_H__
#define __ANIMATOR_H__
#include <avr/io.h>
#include "../Util/cpp_util.h"
#include "../Util/LinkedList.h"
#include "Animation.h"
class Animator
{
public:
    Animator();
    ~Animator();
    void update(const short &delta);
    void addAnimation(Animation *a);
    /**
     * Start the animation with the number
     */
    bool operator[] (const uint8_t &i);
    /**
     * method to start a random animation but still update the old
     */
    bool operator ()(const uint8_t &toupdate);
private:
    uint8_t cur_animation_number;
    Animation *cur_animation;
    Animation *m_to_update;
    bool m_autoAnimation;
    Animator( const Animator &c );
    Animator &operator=( const Animator &c );

    LinkedList<Animation *> animations;

}; //Animator

#endif //__ANIMATOR_H__

/*
* AutoAnimation.h
*
* Created: 08.04.2015 13:18:57
* Author: Benjamin
*/


#ifndef __AUTOANIMATION_H__
#define __AUTOANIMATION_H__
#include "Animation.h"
#include "Animator.h"
#include "../Menu/MenuEntry.h"
#define DEFAULT_AUTO_SWITCH_SPEED 5000
class AutoAnimation : public Animation, public MenuEntry
{
//functions
public:
    AutoAnimation(const uint8_t &id, Animator *anim);
    ~AutoAnimation();

    void update(const uint16_t &delta);
    void updateEntry(const uint16_t &delta, Input &i, Menu &m);
    bool subMenu();
    PGM_P name();
private:
    AutoAnimation( const AutoAnimation &c );
    AutoAnimation &operator=( const AutoAnimation &c );
	
    Animator *m_animator;
    uint16_t m_timer;
    uint16_t m_switchSpeed;

}; //AutoAnimation

#endif //__AUTOANIMATION_H__

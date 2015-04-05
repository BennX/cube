/*
 * MenuEntry.h
 *
 * Created: 05.04.2015 17:27:56
 *  Author: Benjamin
 */

#pragma once
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "../Input.h"
#include "Menu.h"
class Menu;
class MenuEntry
{
public:
    /**
     * get the name of the Menu entry
     */
    virtual PGM_P name() = 0;
    /**
     * Used to draw and update the entry if selected
     */
    virtual void updateEntry(const uint16_t &delta, Input &i,
                             Menu &m) = 0;
    virtual bool subMenu() = 0;
};
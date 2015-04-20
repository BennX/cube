/*
* Submenu.cpp
*
* Created: 20.04.2015 17:31:25
* Author: Benjamin
*/

#include "Submenu.h"
#include "../Display.h"

// default constructor
Submenu::Submenu(PGM_P name) : m_submenu_name(name)
{
} //Submenu

// default destructor
Submenu::~Submenu()
{
} //~Submenu

void Submenu::addEntry(PGM_P name, float *value, const float &min,
                       const float &max)
{
    m_attribut_list.add(new SubmenuEntry(name, value, min, max));
}

void Submenu::update(const uint16_t &delta)
{
    m_incremental_taster.update(delta); //update the taster
}
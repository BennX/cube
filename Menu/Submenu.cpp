/*
* Submenu.cpp
*
* Created: 20.04.2015 17:31:25
* Author: Benjamin
*/

#include "Submenu.h"
#include "../Display.h"
#include "../Util/PStrings.h"
// default constructor
Submenu::Submenu(PGM_P name) : m_submenu_name(name), m_cur_pos(0),
    m_menu_changed(false)
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

void Submenu::update(const uint16_t &delta, Input &i)
{
    if(m_menu_changed)
    {
        Display::clear();

        if(m_attribut_list.size() < 0)
        {
            return; //list is empty
        }
        else if(m_attribut_list.size() < 1)
        {
            //1 attribut inside
            Display::out_p(0, 0) << m_submenu_name;
            SubmenuEntry *entry = m_attribut_list[0];
            Display::out_p(1, 1) << entry->m_name << entry-> m_value;
            Display::out_p(2, 1) << p_strings::start;
            Display::out_p(m_cur_pos + 1, 0) << p_strings::right_arrow;//draw arrow
        }
        else
        {
            // 2 or more items
            //just 1 or 2 elements inside
            if(m_cur_pos < 1)
            {
                //at the start
                Display::out_p(0, 0) << m_submenu_name; //draw title
                //draw elements
                Display::out_p(1, 1) << m_attribut_list[m_attribut_list.size() - 1] <<
                                     m_attribut_list[m_attribut_list.size() - 1]->m_value;
                Display::out_p(2, 1) << m_attribut_list[m_attribut_list.size()] <<
                                     m_attribut_list[m_attribut_list.size()]->m_value;
                Display::out_p(1, 0) << p_strings::right_arrow;
            }
            else  if(m_cur_pos == m_attribut_list.size() + 1)
            {
                //last pos so draw the last 2 elements +start
                Display::out_p(0, 1) << m_attribut_list[m_attribut_list.size() - 1] <<
                                     m_attribut_list[m_attribut_list.size() - 1]->m_value;
                Display::out_p(1, 1) << m_attribut_list[m_attribut_list.size()] <<
                                     m_attribut_list[m_attribut_list.size()]->m_value;
                Display::out_p(2, 1) << p_strings::start;
                //since curpos = last => we are at start
                Display::out_p(2, 0) << p_strings::right_arrow;
            }
            else
            {
                //in the middle of the list
                Display::out_p(0, 1) << m_attribut_list[m_cur_pos - 1] <<
                                     m_attribut_list[m_cur_pos - 1]->m_value;
                Display::out_p(1, 1) << m_attribut_list[m_cur_pos] <<
                                     m_attribut_list[m_cur_pos]->m_value;
                Display::out_p(2, 1) << m_attribut_list[m_cur_pos + 1] <<
                                     m_attribut_list[m_cur_pos + 1]->m_value;
            }
        }
    }
    //now update the position:
    int8_t enc = i.getIncDelta();
    if (enc != 0)
    {
        m_cur_pos += enc;
        if(m_cur_pos <= 0)
            m_cur_pos = 0;
        else if (m_cur_pos > m_attribut_list.size())
            m_cur_pos = (m_attribut_list.size() + 1);
        //redraw next round
        m_menu_changed = true;
    }
}
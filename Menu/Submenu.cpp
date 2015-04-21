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
Submenu::Submenu(PGM_P name, const uint8_t &id) : m_ID(id),
    m_submenu_name(name), m_cur_pos(0), m_menu_changed(true)
{
} //Submenu

// default destructor
Submenu::~Submenu()
{
} //~Submenu

void Submenu::addEntry(PGM_P name, float *value, const float &min,
                       const float &max, const float &update_value)
{
    m_attribut_list.add(new SubmenuEntry(name, value, min, max, update_value));
}

void Submenu::addEntry(PGM_P name, int *value, const float &min,
                       const float &max, const float &update_value)
{
    m_attribut_list.add(new SubmenuEntry(name, value, min, max, update_value));
}

void Submenu::addEntry(PGM_P name, int8_t *value, const float &min,
                       const float &max, const float &update_value)
{
    m_attribut_list.add(new SubmenuEntry(name, value, min, max, update_value));
}


void Submenu::update(const uint16_t &delta, Input &i, Menu &m)
{
    if(m_menu_changed)
    {
        m_menu_changed = false;
        Display::clear();

        if(m_attribut_list.size() < 0)
        {
            return; //list is empty
        }
        else if(m_attribut_list.size() < 1)
        {
            //1 attribut inside
            Display::out_p(0, 0) << m_submenu_name;

            drawEntry(1, 1, m_attribut_list[0]);
            Display::out_p(2, 1) << p_strings::start;
            Display::out_p(m_cur_pos + 1, 0) << p_strings::right_arrow;//draw arrow
        }
        else
        {
            // 2 or more items
            //just 1 or 2 elements inside
            if(m_cur_pos < 1)
            {
                //first entry
                Display::out_p(0, 0) << m_submenu_name; //draw title
                drawEntry(1, 1, m_attribut_list[0]);
                drawEntry(2, 1, m_attribut_list[1]);
                Display::out_p(1, 0) << p_strings::right_arrow;
            }
            else  if(m_cur_pos == m_attribut_list.size() + 1)
            {
                //last pos so draw the last 2 elements +start and position is start
                drawEntry(0, 1, m_attribut_list[m_attribut_list.size() - 1]);
                drawEntry(1, 1, m_attribut_list[m_attribut_list.size()]);
                Display::out_p(2, 1) << p_strings::start;
                //since curpos = last => we are at start
                Display::out_p(2, 0) << p_strings::right_arrow;
            }
            else if(m_cur_pos == m_attribut_list.size())
            {
                //last pos so draw the last 2 elements +start position is middle
                drawEntry(0, 1, m_attribut_list[m_attribut_list.size() - 1]);
                drawEntry(1, 1, m_attribut_list[m_attribut_list.size()]);
                Display::out_p(2, 1) << p_strings::start;
                //since curpos = last => we are at start
                Display::out_p(1, 0) << p_strings::right_arrow;
            }
            else
            {
                //in the middle of the list
                drawEntry(0, 1, m_attribut_list[m_cur_pos - 1]);
                drawEntry(1, 1, m_attribut_list[m_cur_pos]);
                drawEntry(2, 1, m_attribut_list[m_cur_pos + 1]);
                Display::out_p(1, 0) << p_strings::right_arrow;
            }
        }
    }

    //now check manipulation
    if(i.clicked())
    {
        if(m_cur_pos == (m_attribut_list.size() + 1))
        {
            // clicked start
            m.start(m_ID);
            m.leaveSubmenu();
            m_menu_changed = true;
        }
        else
        {
            //not start selected
            m_seleced_entry = !m_seleced_entry;
            m_selected_entry_no = m_cur_pos;
        }
    }

    //now update the position or the entry
    int8_t enc = i.getIncDelta();
    if (enc != 0 && !m_seleced_entry)
    {
        m_cur_pos += enc;
        if(m_cur_pos <= 0)
            m_cur_pos = 0;
        else if (m_cur_pos > m_attribut_list.size())
            m_cur_pos = (m_attribut_list.size() + 1);
        //redraw next round
        m_menu_changed = true;
    }
    else if(enc != 0)
    {
        //something selected manipulate this
        SubmenuEntry *entry = m_attribut_list[m_selected_entry_no];
        switch(entry->m_value.type)
        {
            case INT:
                if(*entry->m_value.data.i + (enc * entry->m_update_value) <= entry->m_max
                        && *entry->m_value.data.i + (enc * entry->m_update_value ) >= entry->m_min)
                {
                    *entry->m_value.data.i += (enc * entry->m_update_value);
                }
                break;
            case FLOAT:
                if(*entry->m_value.data.f + (enc * entry->m_update_value) <= entry->m_max
                        && *entry->m_value.data.f + (enc * entry->m_update_value ) >= entry->m_min)
                {
                    *entry->m_value.data.f += (enc * entry->m_update_value);
                }
                break;
            case INT8:
                if(*entry->m_value.data.i8 + (enc * entry->m_update_value) <= entry->m_max
                        && *entry->m_value.data.i8 + (enc * entry->m_update_value ) >= entry->m_min)
                {
                    *entry->m_value.data.i8 += (enc * entry->m_update_value);
                }
                break;
        }
        m_menu_changed = true;
    }
}

void Submenu::drawEntry(const uint8_t &x, const uint8_t &y, SubmenuEntry *e)
{

    switch(e->m_value.type)
    {
        case INT:
            Display::out_p(x, y) << e->m_name << *e->m_value.data.i;
            break;
        case FLOAT:
            Display::out_p(x, y) << e->m_name << *e->m_value.data.f;
            break;
        case INT8:
            Display::out_p(x, y) << e->m_name << *e->m_value.data.i8;
            break;
    }
}
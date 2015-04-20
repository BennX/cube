/*
* Submenu.h
*
* Created: 20.04.2015 17:31:25
* Author: Benjamin
*/


#ifndef __SUBMENU_H__
#define __SUBMENU_H__
#include <avr/pgmspace.h>
#include "../Util/LinkedList.h"
#include "Taster.h"
class Submenu
{
//variables
private:
    struct SubmenuEntry;
    LinkedList<SubmenuEntry *> m_attribut_list;
    PGM_P m_submenu_name;
    Taster m_incremental_taster;
//functions
public:
    Submenu(PGM_P name);
    ~Submenu();
    /**
     * Add one more entry
     */
    void addEntry(PGM_P name, float *value, const float &min, const float &max);
    /**
     * Update and draw stuff
     */
    void update(const uint16_t &delta);
private:
    Submenu( const Submenu &c );
    Submenu &operator=( const Submenu &c );

    struct SubmenuEntry
    {
        PGM_P m_name;
        float *m_value;
        float m_min;
        float m_max;
        SubmenuEntry(PGM_P name, float *value, const float &min,
                     const float &max): m_name(name),
            m_value(value), m_min(min), m_max(max) {}
    };
}; //Submenu

#endif //__SUBMENU_H__

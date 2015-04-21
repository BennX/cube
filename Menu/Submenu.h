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
#include "../Input.h"
#include "Menu.h"
class Submenu
{
//variables
private:
    struct SubmenuEntry;
    LinkedList<SubmenuEntry *> m_attribut_list;
    uint8_t m_ID;
    PGM_P m_submenu_name;

    //navigation stuff
    int8_t m_cur_pos;
    bool m_menu_changed;

    int8_t m_selected_entry_no;
    bool m_seleced_entry;

//functions
public:
    Submenu(PGM_P name, const uint8_t &id);
    ~Submenu();
    /**
     * Add one more entry
     */
    void addEntry(PGM_P name, float *value, const float &min, const float &max,
                  const float &update_value);
    void addEntry(PGM_P name, int *value, const float &min, const float &max,
                  const float &update_value);
    void addEntry(PGM_P name, int8_t *value, const float &min, const float &max,
                  const float &update_value);

    void drawEntry(const uint8_t &x, const uint8_t &y, SubmenuEntry *e);
    /**
     * Update and draw stuff
     */
    void update(const uint16_t &delta, Input &i, Menu &m);
private:
    Submenu( const Submenu &c );
    Submenu &operator=( const Submenu &c );

    enum Type
    {
        FLOAT,
        INT,
        INT8,
    };
    union Data
    {
        float *f;
        int *i;
        int8_t *i8;
        int16_t *i16;
    };
    struct SubmenuEntry
    {
        struct WeakType
        {
            Type type;
            Data data;

            WeakType(int *i): type(INT)
            {
                data.i = i;
            }

            WeakType(int8_t *i): type(INT8)
            {
                data.i8 = i;
            }

            WeakType(float *f): type(FLOAT)
            {
                data.f = f;
            }
        };

        PGM_P m_name;
        WeakType m_value;
        float m_min;
        float m_max;
        float m_update_value;
        SubmenuEntry(PGM_P name, float *value, const float &min,
                     const float &max, const float &update_value): m_name(name), m_value(value),
            m_min(min), m_max(max), m_update_value(update_value)
        {
        }

        SubmenuEntry(PGM_P name, int *value, const float &min,
                     const float &max, const float &update_value): m_name(name), m_value(value),
            m_min(min), m_max(max), m_update_value(update_value)
        {
        }

        SubmenuEntry(PGM_P name, int8_t *value, const float &min,
                     const float &max, const float &update_value): m_name(name), m_value(value),
            m_min(min), m_max(max), m_update_value(update_value)
        {
        }
    };
};
#endif //__SUBMENU_H__

/*
* GUID.cpp
*
* Created: 08.04.2015 13:43:47
* Author: Benjamin
*/


#include "GUID.h"
namespace GUID
{
    uint8_t current_id = 0;

    uint8_t get()
    {
        return current_id++;
    }
}
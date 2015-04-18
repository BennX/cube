/*
* GUID.cpp
*
* Created: 08.04.2015 13:43:47
* Author: Benjamin
*/


#include "GUID.h"

uint8_t GUID::get()
{
    return current_id++;
}

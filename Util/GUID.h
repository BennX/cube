/*
* GUID.h
*
* Created: 08.04.2015 13:43:47
* Author: Benjamin
*/


#ifndef __GUID_H__
#define __GUID_H__
#include <avr/io.h>
namespace GUID
{
    extern uint8_t current_id;
    extern uint8_t get();
}
#endif //__GUID_H__

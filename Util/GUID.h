/*
* GUID.h
*
* Created: 08.04.2015 13:43:47
* Author: Benjamin
*/


#ifndef __GUID_H__
#define __GUID_H__
#include <avr/io.h>
class GUID
{
public:
    static uint8_t get();
private:
    static uint8_t current_id;
};
#endif //__GUID_H__

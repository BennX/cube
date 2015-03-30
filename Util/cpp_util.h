/*
 * cpp_util.h
 * Including new and deelte operators
 * and also include guards for templates and so on
 * @see http://www.avrfreaks.net/forum/avr-c-micro-how?name=PNphpBB2&file=viewtopic&t=59453
 * Created: 28.03.2015 14:03:05
 *  Author: Benjamin
 */
#ifndef __CPP_UTIL_H__
#define __CPP_UTIL_H__
#include <stdlib.h>

void *operator new(size_t size);
void operator delete(void *ptr);

//returns free ram if not O3!
int freeRam();

#endif
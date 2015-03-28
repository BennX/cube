/*
 * cpp_util.h
 * Including new and deelte operators
 * and also include guards for templates and so on
 * @see http://www.avrfreaks.net/forum/avr-c-micro-how?name=PNphpBB2&file=viewtopic&t=59453
 * Created: 28.03.2015 14:03:05
 *  Author: Benjamin
 */


void *operator new(size_t size);
void operator delete(void *ptr);

void *operator new(size_t size)
{
    return malloc(size);
}

void operator delete(void *ptr)
{
    free(ptr);
}

/**
 * That's almost all. Almost because if you are using gcc
 * 4.x and newer (I didn't check it with older versions) and
 * you want to use templates, virtual inheritance and so on you
 * must define some additional functions, which is not used now
 * by compiler, but must be present to satisfy linker:
 */
__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);

/**
 * Please be sure to define these functions exactly as I showed,
 * I other case gcc could crash during compilation (segmentation fault!),
 * and for sure your program WILL BE NOT working.
 * Implementation is as follow (very important too):
 */
int __cxa_guard_acquire(__guard *g)
{
    return !*(char *)(g);
};
void __cxa_guard_release (__guard *g)
{
    *(char *)g = 1;
};
void __cxa_guard_abort (__guard *) {};

/**
 * And last thing, if you use pure virtual functions you must define another function:
 */
extern "C" void __cxa_pure_virtual(void);
void __cxa_pure_virtual(void) {};

//returns free ram if not O3!
int freeRam ()
{
    extern int __heap_start, *__brkval;
    int v;
    return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

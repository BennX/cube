/*
* CubeProxy.h
*
* Created: 30.10.2015 09:28:42
* Author: Benjamin
*/


#ifndef __CUBEPROXY_H__
#define __CUBEPROXY_H__
#include "RGB.h"
namespace cube
{
//Proxy Object to set values of the cube and
//to optain a value
    class CubeProxy
    {
    public:
        //create a new proxy obj
        CubeProxy& set(uint8_t x, uint8_t y, uint8_t z);
        //set the new color and returns the old
        RGB operator=(const RGB& rgb);

        //get the currenct color
        RGB operator()();
    private:
        uint8_t m_x, m_y, m_z;
    }; //CubeProxy
}
#endif //__CUBEPROXY_H__

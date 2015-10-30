/*
* CubeProxy.cpp
*
* Created: 30.10.2015 09:28:42
* Author: Benjamin
*/


#include "CubeProxy.h"
#include "Cube.h"
namespace cube
{
    CubeProxy& CubeProxy::set(uint8_t x, uint8_t y, uint8_t z)
    {
        m_x = x,
        m_y = y;
        m_z = z;
        return *this;
    }

    RGB CubeProxy::operator =(const RGB& rgb)
    {
        return Cube::getInstance().setRGB(m_x, m_y, m_z, rgb);
    }

    RGB CubeProxy::operator ()()
    {
        return Cube::getInstance().getRGB(m_x, m_y, m_z);
    }
}
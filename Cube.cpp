/*
* Cube.cpp
*
* Created: 16.12.2014 11:44:05
* Author: Benjamin
*/

#include "Cube.h"
// default constructor
Cube::Cube(): level(0), cur_color_counter(0)
{
    SPI::init();//init the spi
    for(uint8_t i = 0; i < MAX_COLOR; i++)
    {
        //maxbe reverse
        colors[0][i][0] = 0x04;//
        colors[1][i][0] = 0x03;//
        colors[2][i][0] = 0x02;//
        colors[3][i][0] = 0x01;//
        colors[4][i][0] = 0x00;//
    }
    //set all 0 with a string function
    //memset(cur_colors, 0, 5*5*5*sizeof(RGB));

    //enabel output on ss and latch pins
    *m_to_storage_ddr |= (1 << m_to_storage_pin_no);
    *m_disable_ddr |= (1 << m_disable_pin_no);
} //Cube

// default destructor
Cube::~Cube()
{
} //~Cube

void Cube::off()
{
    for(uint8_t x = 0; x < 5; x++)
    {
        for(uint8_t y = 0; y < 5; y++)
        {
            for(uint8_t z = 0; z < 5; z++)
            {
                setRGB(x, y, z, 0, 0, 0);
            }
        }
    }
}

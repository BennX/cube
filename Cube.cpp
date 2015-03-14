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
        //set the default register for the level
        colors[0][i][0] = (1 << 7);
        colors[1][i][0] = (1 << 6);
        colors[2][i][0] = (1 << 5);
        colors[3][i][0] = (1 << 4);
        colors[4][i][0] = (1 << 3);
    }
    //set all 0 with a string function
    //memset(cur_colors, 0, 5*5*5*sizeof(RGB));

    //enabel output on ss and latch pins
    DDR_TO_STORAGE |= (1 << TO_STORAGE_PIN);
    DDR_DISABLE_LINE |= (1 << DISABLE_LINE_PIN);
} //Cube

// default destructor
Cube::~Cube()
{
} //~Cube

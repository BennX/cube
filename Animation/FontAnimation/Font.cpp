/*
* Font.cpp
*
* Created: 03.04.2015 16:18:11
* Author: Benjamin
*/


#include "Font.h"

// default constructor
Font::Font()
{
    letters[0] =
    {
        16,
        Pixel{1, 4}, Pixel{2, 4}, Pixel{3, 4},
        Pixel{0, 3}, Pixel{1, 3}, Pixel{3, 3}, Pixel{4, 3},
        Pixel{0, 2}, Pixel{4, 2},
        Pixel{0, 1}, Pixel{1, 1}, Pixel{2, 1}, Pixel{3, 1}, Pixel{4, 1},
        Pixel{0, 0}, Pixel{4, 0}
    };// A

    letters[1] =
    {
        20,
        Pixel{0, 4}, Pixel{1, 4}, Pixel{2, 4}, Pixel{3, 4}, Pixel{4, 4},
        Pixel{0, 3}, Pixel{4, 3},
        Pixel{0, 2}, Pixel{1, 2}, Pixel{2, 2}, Pixel{3, 2},
        Pixel{0, 1}, Pixel{4, 1},
        Pixel{0, 0}, Pixel{1, 0}, Pixel{2, 0}, Pixel{3, 0}, Pixel{4, 0}
    };// B

    letters[2] =
    {
        13,
        Pixel{0, 4}, Pixel{1, 4}, Pixel{2, 4}, Pixel{3, 4}, Pixel{4, 4},
        Pixel{0, 3},
        Pixel{0, 2},
        Pixel{0, 1},
        Pixel{0, 0}, Pixel{1, 0}, Pixel{2, 0}, Pixel{3, 0}, Pixel{4, 0}
    };// C

    letters[3] =
    {
        16,
        Pixel{0, 4}, Pixel{1, 4}, Pixel{2, 4}, Pixel{3, 4},
        Pixel{0, 3}, Pixel{4, 3},
        Pixel{0, 2}, Pixel{4, 2},
        Pixel{0, 1}, Pixel{4, 1},
        Pixel{0, 0}, Pixel{1, 0}, Pixel{2, 0}, Pixel{3, 0},
    };// D

    letters[4] =
    {
        16,
        Pixel{0, 4}, Pixel{1, 4}, Pixel{2, 4}, Pixel{3, 4}, Pixel{4, 4},
        Pixel{0, 3},
        Pixel{0, 2}, Pixel{1, 2}, Pixel{2, 2}, Pixel{3, 2},
        Pixel{0, 1},
        Pixel{0, 0}, Pixel{1, 0}, Pixel{2, 0}, Pixel{3, 0}, Pixel{4, 0}
    };// E

    letters[5] =
    {
        12,
        Pixel{0, 4}, Pixel{1, 4}, Pixel{2, 4}, Pixel{3, 4}, Pixel{4, 4},
        Pixel{0, 3},
        Pixel{0, 2}, Pixel{1, 2}, Pixel{2, 2}, Pixel{3, 2},
        Pixel{0, 1},
        Pixel{0, 0},
    };// F

    letters[6] =
    {
        16,
        Pixel{0, 4}, Pixel{1, 4}, Pixel{2, 4}, Pixel{3, 4}, Pixel{4, 4},
        Pixel{0, 3},
        Pixel{0, 2}, Pixel{3, 2}, Pixel{4, 2},
        Pixel{0, 1}, Pixel{4, 1},
        Pixel{0, 0}, Pixel{1, 0}, Pixel{2, 0}, Pixel{3, 0}, Pixel{4, 0},
    };// G

    letters[7] =
    {
        13,
        Pixel{0, 4}, Pixel{4, 4},
        Pixel{0, 3}, Pixel{4, 3},
        Pixel{0, 2}, Pixel{1, 2}, Pixel{2, 2}, Pixel{3, 2}, Pixel{4, 2},
        Pixel{0, 1}, Pixel{4, 1},
        Pixel{0, 0}, Pixel{4, 0},
    };// H

    letters[8] =
    {
        13,
        Pixel{0, 4}, Pixel{1, 4}, Pixel{2, 4}, Pixel{3, 4}, Pixel{4, 4},
        Pixel{2, 3},
        Pixel{2, 2},
        Pixel{2, 1},
        Pixel{0, 0}, Pixel{1, 0}, Pixel{2, 0}, Pixel{3, 0}, Pixel{4, 0},
    };// I

    letters[9] =
    {
        11,
        Pixel{3, 4}, Pixel{4, 4},
        Pixel{4, 3},
        Pixel{4, 2},
        Pixel{0, 1}, Pixel{4, 1},
        Pixel{0, 0}, Pixel{1, 0}, Pixel{2, 0}, Pixel{3, 0}, Pixel{4, 0},
    };// J

    letters[10] =
    {
        11,
        Pixel{0, 4}, Pixel{4, 4},
        Pixel{0, 3}, Pixel{3, 3},
        Pixel{0, 2}, Pixel{1, 2}, Pixel{2, 2},
        Pixel{0, 1}, Pixel{3, 1},
        Pixel{0, 0}, Pixel{4, 0},
    };// K

    letters[11] =
    {
        9,
        Pixel{0, 4},
        Pixel{0, 3},
        Pixel{0, 2},
        Pixel{0, 1},
        Pixel{0, 0}, Pixel{1, 0}, Pixel{2, 0}, Pixel{3, 0}, Pixel{4, 0},
    };// L

    letters[12] =
    {
        13,
        Pixel{0, 4}, Pixel{4, 4},
        Pixel{0, 3}, Pixel{1, 3}, Pixel{3, 3}, Pixel{4, 3},
        Pixel{0, 2}, Pixel{2, 2}, Pixel{4, 2},
        Pixel{0, 1}, Pixel{4, 1},
        Pixel{0, 0}, Pixel{4, 0},
    };// M

    letters[13] =
    {
        13,
        Pixel{0, 4}, Pixel{4, 4},
        Pixel{0, 3}, Pixel{1, 3}, Pixel{4, 3},
        Pixel{0, 2}, Pixel{2, 2}, Pixel{4, 2},
        Pixel{0, 1}, Pixel{3, 1}, Pixel{4, 1},
        Pixel{0, 0}, Pixel{4, 0},
    };// N

    letters[14] =
    {
        16,
        Pixel{0, 4}, Pixel{1, 4}, Pixel{2, 4}, Pixel{3, 4}, Pixel{4, 4},
        Pixel{0, 3}, Pixel{4, 3},
        Pixel{0, 2}, Pixel{4, 2},
        Pixel{0, 1}, Pixel{4, 1},
        Pixel{0, 0}, Pixel{1, 0}, Pixel{2, 0}, Pixel{3, 0}, Pixel{4, 0},
    };// o

    letters[15] =
    {
        14,
        Pixel{0, 4}, Pixel{1, 4}, Pixel{2, 4}, Pixel{3, 4},
        Pixel{0, 3}, Pixel{4, 3},
        Pixel{0, 2}, Pixel{1, 2}, Pixel{2, 2}, Pixel{3, 2},
        Pixel{0, 1},
        Pixel{0, 0},
    };// P

    letters[16] =
    {
        15,
        Pixel{0, 4}, Pixel{1, 4}, Pixel{2, 4}, Pixel{3, 4}, Pixel{4, 4},
        Pixel{0, 3}, Pixel{4, 3},
        Pixel{0, 2}, Pixel{4, 2},
        Pixel{0, 1}, Pixel{1, 1}, Pixel{2, 1}, Pixel{3, 1}, Pixel{4, 1},
        Pixel{2, 0},
    };// Q

    letters[17] =
    {
        16,
        Pixel{0, 4}, Pixel{1, 4}, Pixel{2, 4}, Pixel{3, 4},
        Pixel{0, 3}, Pixel{4, 3},
        Pixel{0, 2}, Pixel{1, 2}, Pixel{2, 2}, Pixel{3, 2},
        Pixel{0, 1}, Pixel{4, 1},
        Pixel{0, 0}, Pixel{4, 0},
    };// R

    letters[18] =
    {
        17,
        Pixel{0, 4}, Pixel{1, 4}, Pixel{2, 4}, Pixel{3, 4}, Pixel{4, 4},
        Pixel{0, 3},
        Pixel{0, 2}, Pixel{1, 2}, Pixel{2, 2}, Pixel{3, 2}, Pixel{4, 2},
        Pixel{4, 1},
        Pixel{0, 0}, Pixel{1, 0}, Pixel{2, 0}, Pixel{3, 0}, Pixel{4, 0},
    };// S

    letters[19] =
    {
        9,
        Pixel{0, 4}, Pixel{1, 4}, Pixel{2, 4}, Pixel{3, 4}, Pixel{4, 4},
        Pixel{2, 3},
        Pixel{2, 2},
        Pixel{2, 1},
        Pixel{2, 0},
    };// T

    letters[20] =
    {
        13,
        Pixel{0, 4}, Pixel{4, 4},
        Pixel{0, 3}, Pixel{4, 3},
        Pixel{0, 2}, Pixel{4, 2},
        Pixel{0, 1}, Pixel{4, 1},
        Pixel{0, 0}, Pixel{1, 0}, Pixel{2, 0}, Pixel{3, 0}, Pixel{4, 0},
    };// U

    letters[21] =
    {
        9,
        Pixel{0, 4}, Pixel{4, 4},
        Pixel{0, 3}, Pixel{4, 3},
        Pixel{1, 2}, Pixel{3, 2},
        Pixel{1, 1}, Pixel{3, 1},
        Pixel{2, 0},
    };// V

    letters[22] =
    {
        12,
        Pixel{0, 4}, Pixel{4, 4},
        Pixel{0, 3}, Pixel{4, 3},
        Pixel{0, 2}, Pixel{2, 2}, Pixel{4, 2},
        Pixel{0, 1}, Pixel{2, 1}, Pixel{4, 1},
        Pixel{1, 0}, Pixel{3, 0}
    };// W

    letters[23] =
    {
        9,
        Pixel{0, 4}, Pixel{4, 4},
        Pixel{1, 3}, Pixel{3, 3},
        Pixel{2, 2},
        Pixel{1, 1}, Pixel{3, 1},
        Pixel{0, 0}, Pixel{4, 0}
    };// X

    letters[24] =
    {
        8,
        Pixel{0, 4}, Pixel{4, 4},
        Pixel{0, 3}, Pixel{4, 3},
        Pixel{1, 2}, Pixel{3, 2},
        Pixel{2, 1},
        Pixel{2, 0},
    };// Y

    letters[25] =
    {
        13,
        Pixel{0, 4}, Pixel{1, 4}, Pixel{2, 4}, Pixel{3, 4}, Pixel{4, 4},
        Pixel{3, 3},
        Pixel{2, 2},
        Pixel{1, 1},
        Pixel{0, 0}, Pixel{1, 0}, Pixel{2, 0}, Pixel{3, 0}, Pixel{4, 0},
    };// Z
}

// default destructor
Font::~Font()
{
} //~Font

Letter Font::get(const unsigned char &a)
{
    return letters[a - 'A'];
}
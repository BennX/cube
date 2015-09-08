/*
* Vector.cpp
*
* Created: 06.09.2015 11:05:40
* Author: Benjamin
*/


#include "Vector.h"
// default constructor
Vector::Vector(): x(0), y(0), z(0)
{
} //Vector

Vector::Vector(const float& x, const float& y, const float& z): x(x), y(y), z(z)
{
} //Vector

Vector::Vector(const Vector& other): x(other.x), y(other.y), z(other.z)
{
}
// default destructor
Vector::~Vector()
{
} //~Vector
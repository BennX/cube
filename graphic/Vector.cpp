/*
* Vector.cpp
*
* Created: 06.09.2015 11:05:40
* Author: Benjamin
*/


#include "Vector.h"
#include <math.h>
#include "../Util/Random.h"
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

Vector& Vector::operator=(const Vector& other)
{
    if(this != &other)
    {
        x = other.x;
        y = other.y;
        z = other.x;
    }
    return *this;
}

// default destructor
Vector::~Vector()
{
} //~Vector

Vector& Vector::nor()
{
    float length = sqrt(x * x + y * y + z * z);
    x = 1.0f / length * x;
    y = 1.0f / length * y;
    z = 1.0f / length * z;
    return *this;
}

Vector Vector::cross(const Vector& other) const
{
    return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

float Vector::dot(const Vector& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector& Vector::rnd()
{
    x = rndF();
    y = rndF();
    z = rndF();
    return *this;
}

Vector& Vector::operator +=(const Vector& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector Vector::operator +(const Vector& other) const
{
    return Vector(*this) += other;
}

Vector& Vector::operator -=(const Vector& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector Vector::operator -(const Vector& other) const
{
    return Vector(*this) -= other;
}


Vector& Vector::operator *=(const float& f)
{
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

Vector Vector::operator *(const float& f) const
{
    return Vector(*this) *= f;
}

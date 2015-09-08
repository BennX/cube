
/*
 * Vector.hpp
 *
 * Created: 08.09.2015 10:59:06
 *  Author: Benjamin
 */

#include <math.h>
#include "../Util/Random.h"

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

float Vector::norm() const
{
    return sqrt(x * x + y * y + z * z);
}

float Vector::dist(const Vector& other) const
{
    return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2) + pow(z - other.z, 2));
}

Vector& Vector::rnd()
{
    x = rndF();
    y = rndF();
    z = rndF();
    return *this;
}
Vector& Vector::rnd(const float& f)
{
    x = rndF() * f;
    y = rndF() * f;
    z = rndF() * f;
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

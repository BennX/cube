/*
* Vector.h
*
* Created: 06.09.2015 11:05:41
* Author: Benjamin
*/


#ifndef __VECTOR_H__
#define __VECTOR_H__
class Vector
{
public:
    float x, y, z;

    Vector();
    Vector(const Vector& c);   //copy ctor
    Vector& operator=(const Vector& c);
    Vector(const float& x, const float& y, const float& z);

    ~Vector();

    Vector& nor();
    Vector cross(const Vector& other) const;
    float dot(const Vector& other) const;

    Vector& rnd();

    Vector& operator+=(const Vector& other);
    Vector operator+(const Vector& other) const;

    Vector& operator-=(const Vector& other);
    Vector operator-(const Vector& other) const;

    Vector& operator*=(const float& f);
    Vector operator*(const float& other) const;
}; //Vector

#endif //__VECTOR_H__

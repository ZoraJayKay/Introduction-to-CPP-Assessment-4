#pragma once
#include <cmath>

class MyVector3 
{
public:
	float x, y, z;

	MyVector3(float x, float y, float z);
	~MyVector3();

	// TRANSFORM: VECTOR ADDITION
	MyVector3 operator + (MyVector3&);

	// TRANSFORM: VECTOR SUBTRACTION
	MyVector3 operator - (MyVector3&);

	// TRANSFORM: VECTOR SCALE (Float - multiply)    overloaded operator (accept one Vector3 and multiply it by a float)
	MyVector3 operator * (float rhs);

	// DOT PRODUCT
	float Dot(MyVector3&);

	// CROSS PRODUCT
	MyVector3* Cross(MyVector3&);
};
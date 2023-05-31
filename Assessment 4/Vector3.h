#pragma once
#include <cmath>

// This is called MyVector3 to distinguish it from the RayLib vector3, just in case there are distinct differences between the two that I cannot detect / understand / anticipate
class MyVector3 
{
public:
	float x, y, z;
	MyVector3();
	MyVector3(float x, float y, float z);

	// *** ---	GAME OBJECT MOVEMENT RELEVANT FUNCTIONS  --- ***
		// TRANSFORM: VECTOR ADDITION
		MyVector3 operator + (MyVector3& rhs);

		// TRANSFORM: VECTOR SUBTRACTION
		MyVector3 operator - (MyVector3&);

		// TRANSFORM: VECTOR SCALE (Float - multiply)    overloaded operator (accept one Vector3 and multiply it by a float)
		MyVector3 operator * (float rhs);

		// EQUALITY 
		MyVector3 operator = (MyVector3& rhs);
		
		// DOT PRODUCT
		float Dot(MyVector3&);

		// CROSS PRODUCT
		MyVector3 Cross(MyVector3&);


	// *** ---	COLLISION DETECTION RELEVANT FUNCTIONS  --- ***
		// Minimum Vector3
		// A function to create the smallest vector possible from the combination of two other vectors
		static MyVector3 Min(MyVector3& v1, MyVector3& v2);

		// Maximum Vector3
		// A function to create the largest vector possible from the combination of two other vectors
		static MyVector3 Max(MyVector3& v1, MyVector3& v2);

		// Clamp vector3
		// A function to create a vector3 that is always the largest 3 given vector3's
		MyVector3 Clamp(MyVector3& t, MyVector3& vMinimum, MyVector3& vMaximum);

		// Extents
		MyVector3 Extents();
};
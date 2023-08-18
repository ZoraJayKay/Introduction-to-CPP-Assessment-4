#include "Vector3.h"
#include <algorithm>

// Default constructor (should not be in use)
MyVector3::MyVector3() {};

// Overloaded constructor (should always be used)
MyVector3::MyVector3(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
};

// *** ---	GAME OBJECT MOVEMENT RELEVANT FUNCTIONS  --- ***
	// TRANSFORM: VECTOR ADDITION
	MyVector3 MyVector3::operator +(MyVector3& rhs) {
		return MyVector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
	};

	// TRANSFORM: VECTOR SCALE (Float - multiply)    overloaded operator (accept one Vector3 and multiply it by a float)
	MyVector3 MyVector3::operator *(float rhs)
	{
		return MyVector3(this->x * rhs, this->y * rhs, this->z * rhs);
	}


	MyVector3 MyVector3::operator =(MyVector3& rhs)
	{
		return MyVector3(
			this->x = rhs.x, 
			this->y = rhs.y, 
			this->z = rhs.z);
	}


	// DOT PRODUCT
	// Function set up to accept one Vector3, presumption is that function is called from a Vector3 itself (so only needs to pass in one)
	// dot product returns a scalar value which is the length of the two vectors multiplied by the cosine of the angle between them
	float MyVector3::Dot(MyVector3& V1) {
		float dotProduct = 
			(V1.x * this->x) + 
			(V1.y * this->y) + 
			(V1.z * this->z);
		return dotProduct;
	};

	// CROSS PRODUCT
	// Function set up to accept one Vector3, presumption is that function is called from a Vector3 itself (so only needs to pass in one)
	// cross product returns a vector perpendicular to the input vector and itself
	MyVector3 MyVector3::Cross(MyVector3& V1) {
		return MyVector3(
			this->y * V1.z - this->z * V1.y,
			this->z * V1.x - this->x * V1.z,
			this->x * V1.y - this->y * V1.x);
	};


// *** ---	COLLISION DETECTION RELEVANT FUNCTIONS  --- ***
	// Minimum Vector3
	// A function to create the smallest vector possible from the combination of two other vectors
	MyVector3 MyVector3::Min(MyVector3& v1, MyVector3& v2) {
		return MyVector3(
			std::min(v1.x, v2.x),
			std::min(v1.y, v2.y),
			std::min(v1.z, v2.z));
	};

	// Maximum Vector3
	// A function to create the largest vector possible from the combination of two other vectors
	MyVector3 MyVector3::Max(MyVector3& v1, MyVector3& v2) {
		return MyVector3(
			std::max(v1.x, v2.x),
			std::max(v1.y, v2.y),
			std::max(v1.z, v2.z));
	};

	// Clamp vector3
	// A function that clamps a specified value t within a range specified by minimum and maximum values.
	// If t is smaller than the other two vectors, 
	MyVector3 MyVector3::Clamp(MyVector3& t, MyVector3& vMinimum, MyVector3& vMaximum) {
		// Return the smaller of t or the maximum allowed vector.
		// This returns t if it is an allowable size, or else it returns the max 'clamp', the largest maximum vector.
		MyVector3 minVector3 = Min(vMaximum, t);

		// Create a pointer to the smaller of t or the maximum allowed vector.
		MyVector3* minVector3Ptr = &minVector3;

		// Return the clamped vector that lies imbetween the min and max, aka return the larger of: 
		// a) the smallest permissible vector;
		// b) the smaller of t and the maximum permissible vector.
		MyVector3 vector3Clamp = Max(vMinimum, *minVector3Ptr);

		// Destroy the pointer to the minimum of the 2nd and t vectors
		delete minVector3Ptr;
		minVector3Ptr = nullptr;

		// Return the clamp vector3 that is the largest of all 3 vectors
		return vector3Clamp;
	};
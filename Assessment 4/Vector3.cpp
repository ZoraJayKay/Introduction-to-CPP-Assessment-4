#include "Vector3.h"

MyVector3::MyVector3(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
};

// TRANSFORM: VECTOR SCALE (Float - multiply)    overloaded operator (accept one Vector3 and multiply it by a float)
MyVector3 MyVector3::operator *(float rhs)
{
	return MyVector3(this->x * rhs, this->y * rhs, this->z * rhs);
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
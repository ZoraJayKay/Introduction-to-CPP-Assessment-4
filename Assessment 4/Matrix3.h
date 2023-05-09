#pragma once
#include <cmath>

// a class for calculating 2D movements using matrices
class Matrix3
{
public:
	// variables
	float m00, m01, m02;	// row 1 (Ax, Bx, Cx)
	float m10, m11, m12;	// row 2 (Ay, By, Cy)
	float m20, m21, m22;	// row 3 (Az, Bz, Cz)

	// default constructor
	Matrix3();

	// default destructor
	~Matrix3();

	// constructor to set an identity matrix
	Matrix3(float identity);
	// implementation in source file

	// Overloaded constructor for all 9 variables
	// COLUMN MAJOR ORDER
	Matrix3(float _m00, float _m10, float _m20, float _m01, float _m11, float _m21, float _m02, float _m12, float _m22);
	// implementation in source file

	// MATRIX MULTIPLICATION
	Matrix3 operator * (Matrix3 M2);
	// implementation in source file
	// there is only one parameter needed because the member calling this function is IMPLICITLY the first parameter.

	// MATRIX SETTING
	Matrix3 Set(Matrix3);
	// implementation in source file

	//	MATRIX ROTATION
	// Set rotation to specific point
	void SetRotateX(float rotationInRadians);
	void SetRotateY(float rotationInRadians);
	void SetRotateZ(float rotationInRadians);
											
	// Rotate incrementally					
	Matrix3 RotateX(float rotationinRadians);
	Matrix3 RotateY(float rotationinRadians);
	Matrix3 RotateZ(float rotationinRadians);


	// TRANSLATION
	// Set translation to specific point


	// Translate incrementally
};

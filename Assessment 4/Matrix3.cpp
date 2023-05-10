#include "Matrix3.h"


// default constructor (just to avoid null errors)
Matrix3::Matrix3() {}

// default destructor
Matrix3::~Matrix3() {}


// constructor to set an identity matrix
Matrix3::Matrix3(float identity)
{
    //Column 1
    m00 = identity; // (Vector A x-axis value)
    m10 = 0;        // (Vector A y-axis value)
    m20 = 0;        // (Vector A z-axis value)

    // Column 2
    m01 = 0;        // (Vector B x-axis value)
    m11 = identity; // (Vector B y-axis value)
    m21 = 0;        // (Vector B z-axis value)

    // Column 3
    m02 = 0;        // (Vector C x-axis value)
    m12 = 0;        // (Vector C y-axis value)
    m22 = identity; // (Vector C z-axis value)
}

// overloaded constructor COLUMN MAJOR ORDER
Matrix3::Matrix3(float _m00, float _m10, float _m20, float _m01, float _m11, float _m21, float _m02, float _m12, float _m22)
{
    //Column 1
    m00 = _m00; // (Vector A x-axis value)
    m10 = _m10; // (Vector A y-axis value)
    m20 = _m20; // (Vector A z-axis value)

    // Column 2
    m01 = _m01; // (Vector B x-axis value)
    m11 = _m11; // (Vector B y-axis value)
    m21 = _m21; // (Vector B z-axis value)

    // Column 3
    m02 = _m02; // (Vector C x-axis value)
    m12 = _m12; // (Vector C y-axis value)
    m22 = _m22; // (Vector C z-axis value)
}

// MATRIX MULTIPLICATION OPERATOR OVERLOAD
// Multiply a matrix by a matrix (3x3 matrix * 3x3 matrix = 3x3 matrix)
// My comments assume a 1st matrix3 of 3 columns ABC, and a 2nd matrix of 3 columns DEF
// This operator overload function has been written so as to be inherently place the matrix that calls it as the first matrix in the multiplication

Matrix3 Matrix3::operator * (Matrix3& M2)
// the scope operator comes AFTER the type
// there is only one parameter needed because the member calling this function is IMPLICITLY the first parameter.
{
    return Matrix3(
        // COLUMN MAJOR
        // ABCxyz * Dxyz
        (this->m00 * M2.m00 + this->m01 * M2.m10 + this->m02 * M2.m20),  // Ax * Dx + Bx * Dy + Cx * Dz
        (this->m10 * M2.m00 + this->m11 * M2.m10 + this->m12 * M2.m20),  // Ay * Dx + By * Dy + Cy * Dz
        (this->m20 * M2.m00 + this->m21 * M2.m10 + this->m22 * M2.m20),  // Az * Dx + Bz * Dy + Cz * Dz

        // ABCxyz * Exyz
        (this->m00 * M2.m01 + this->m01 * M2.m11 + this->m02 * M2.m21),  // Ax * Ex + Bx * Ey + Cx * Ez
        (this->m10 * M2.m01 + this->m11 * M2.m11 + this->m12 * M2.m21),  // Ay * Ex + By * Ey + Cy * Ez
        (this->m20 * M2.m01 + this->m21 * M2.m11 + this->m22 * M2.m21),  // Az * Ex + Bz * Ey + Cz * Ez

        // ABCxyz * Fxyz
        (this->m00 * M2.m02 + this->m01 * M2.m12 + this->m02 * M2.m22),  // Ax * Fx + Bx * Fy + Cx * Fz
        (this->m10 * M2.m02 + this->m11 * M2.m12 + this->m12 * M2.m22),  // Ay * Fx + By * Fy + Cy * Fz
        (this->m20 * M2.m02 + this->m21 * M2.m12 + this->m22 * M2.m22)); // Az * Fx + Bz * Fy + Cz * Fz
}




// set the matrix that calls this function equal to the matrix it passes in
Matrix3 Matrix3::Set(Matrix3 m)
{
    return Matrix3
    (
        this->m00 = m.m00,
        this->m10 = m.m10,
        this->m20 = m.m20,
        this->m01 = m.m01,
        this->m11 = m.m11,
        this->m21 = m.m21,
        this->m02 = m.m02,
        this->m12 = m.m12,
        this->m22 = m.m22
    );    
}

//	MATRIX ROTATION
// Set rotation to specific point
void Matrix3::SetRotateX(float rotationInRadians) 
{
    float c = (float)cos(rotationInRadians);
    float s = (float)sin(rotationInRadians);

    // COLUMN MAJOR ORDER
    this->m00 = 1; this->m01 = 0; this->m02 = 0;
    this->m10 = 0; this->m11 = c; this->m12 = -s;
    this->m20 = 0; this->m21 = s; this->m22 = c;
};

void Matrix3::SetRotateY(float rotationInRadians)
{
    float c = (float)cos(rotationInRadians);
    float s = (float)sin(rotationInRadians);

    // COLUMN MAJOR ORDER
    this->m00 = c;  this->m01 = 0;  this->m02 = -s;
    this->m10 = 0;  this->m11 = 1;  this->m12 = 0;
    this->m20 = s;  this->m21 = 0;  this->m22 = c;
};

void Matrix3::SetRotateZ(float rotationInRadians)
{
    float c = (float)cos(rotationInRadians);
    float s = (float)sin(rotationInRadians);

    // COLUMN MAJOR ORDER
    this->m00 = c;  this->m01 = -s; this->m02 = 0;
    this->m10 = s;  this->m11 = c;  this->m12 = 0;
    this->m20 = 0;  this->m21 = 0;  this->m22 = 1;
};

// Rotate incrementally					 
Matrix3 Matrix3::RotateX(float rotationinRadians)
{
    Matrix3* m = new Matrix3(1);        // create an identity matrix
    m->SetRotateX(rotationinRadians);   // set up the identity matrix as a rotation matrix
    return *this * *m;
};

Matrix3 Matrix3::RotateY(float rotationinRadians)
{
    Matrix3* m = new Matrix3(1);        // create an identity matrix
    m->SetRotateY(rotationinRadians);   // set up the identity matrix as a rotation matrix
    return *this * *m;
};

Matrix3 Matrix3::RotateZ(float rotationinRadians)
{
    Matrix3* m = new Matrix3(1);        // create an identity matrix
    m->SetRotateZ(rotationinRadians);   // set up the identity matrix as a rotation matrix
    return *this * *m;
};


// *** NOTE TO SELF: THERE IS A DISTINCTION BETWEEN SETTRANSLATE AND TRANSLATE ***
// ** SETTRANSLATE AKA MOVING TO ABSOLUTE DESTINATION; TELEPORTING**
// * TRANSLATE AKA MOVING RELATIVE POSITION; WALKING*

// Absolute translation; teleportation
void Matrix3::SetTranslation(float x, float y)
{
    // COLUMN MAJOR ORDER
    this->m02 = x; this->m12 = y;
}

// Incremental translation; movement
void Matrix3::Translate(float x, float y)
{
    // COLUMN MAJOR ORDER
    this->m02 += x; this->m12 += y;
}
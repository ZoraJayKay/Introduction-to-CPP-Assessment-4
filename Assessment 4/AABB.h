#pragma once
#include "Vector3.h"

class AABB
{
public:
	// Default constructor (should not be in use)
	AABB();
	// Overloaded constructor (should be in use 100% of the time)
	AABB(MyVector3& min, MyVector3& max);

	// Destructor
	~AABB();

	// *** BOUNDING BOX VARIABLES ***
	float positive = 1;
	float negative = -1;

	float AABBtextureWidth;
	float AABBtextureHeight;

	// *** BOUNDING BOX ***
	// Axis-Aligned Bounding Box minimum vector3
	MyVector3* minVector3AABB = new MyVector3(negative, negative, negative);
	// Axis-Aligned Bounding Box maximum vector3
	MyVector3* maxVector3AABB = new MyVector3(positive, positive, positive);

	// *** BOUNDING BOX FUNCTIONS ***
	// Return the centre of the collision hitbox
	MyVector3 ReturnCenter();
	void UpdateBoxBoundries(MyVector3& min, MyVector3& max);

	// Extents
	MyVector3 Extents();

	// Return the corners of the AABB, using min and max. In 2D we would return 4 corners, and in 3D we would return 8 corners.
	MyVector3* Corners();

	// Calculate the bounding box for this sprite object
	void Fit(MyVector3* points[4]);

	/* Test if a point is contained within an AABB by checking if the point is within the range of the min and max corners. */
	bool Overlaps(MyVector3& point);

	bool Overlaps(AABB& otherObject);

	void debugBox2D(Color c);
};


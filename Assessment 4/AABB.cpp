#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "AABB.h"
#include "GameObject.h"

// Default constructor (should not be in use)
AABB::AABB() {};

// Overloaded constructor (should be in use 100% of the time)
AABB::AABB(MyVector3& min, MyVector3& max) {
	*minVector3AABB = min;
	*maxVector3AABB = max;
};

// Destructor
AABB::~AABB() {
	delete minVector3AABB;
	minVector3AABB = nullptr;	

	delete maxVector3AABB;
	maxVector3AABB = nullptr;
};


// *** BOUNDING BOX FUNCTIONS ***
	// Return the centre of the collision hitbox (the point halfway between the miximum and maximum)
MyVector3 AABB::ReturnCenter() {
	return (*this->minVector3AABB + *this->maxVector3AABB) * 0.5f;
};

// Set the AABB min and max equal to inputs
void AABB::UpdateBoxBoundries(MyVector3& min, MyVector3& max) {
	*this->minVector3AABB = min;
	*this->maxVector3AABB = max;
};

// Extents
// Calculate the half-extents for each vector component by subtracting the min point from the max point and then halving the absolute value 
MyVector3 AABB::Extents() {
	return MyVector3(
		abs(this->maxVector3AABB->x - this->minVector3AABB->x) * 0.5f,
		abs(this->maxVector3AABB->y - this->minVector3AABB->y) * 0.5f,
		abs(this->maxVector3AABB->z - this->minVector3AABB->z) * 0.5f);
};

// Return the corners of the AABB as an array of vectors, using min and max. In 2D we would return 4 corners, and in 3D we would return 8 corners. This is taking the XYZ of the min (bottom left) and the XYZ of the max (top right) and inferring the other 2 corners.
MyVector3* AABB::Corners() {
	MyVector3* cornerPtr_01 = new MyVector3(this->minVector3AABB->x, this->maxVector3AABB->y, this->minVector3AABB->z);
	MyVector3* cornerPtr_03 = new MyVector3(this->maxVector3AABB->x, this->minVector3AABB->y, this->minVector3AABB->z);

	MyVector3 corners[4];
	corners[0] = *this->minVector3AABB;
	//corners[1] = MyVector3(this->minVector3AABB->x, this->maxVector3AABB->y, this->minVector3AABB->z);
	corners[1] = *cornerPtr_01;
	corners[2] = *this->maxVector3AABB;
	//corners[3] = MyVector3(this->maxVector3AABB->x, this->minVector3AABB->y, this->minVector3AABB->z);
	corners[3] = *cornerPtr_03;

	delete cornerPtr_01;
	cornerPtr_01 = nullptr;

	delete cornerPtr_03;
	cornerPtr_03 = nullptr;

	// return the address of the array which contains the vectors. Because an array is contiguous, we only need the address of the start of the array.
	return corners;
};

// This function will calculate a bounding region that would encapsulate a set of points (corners) and fit an AABB around the points. In 2D this creates a rectangle of space. To do this we need to find the minimum and maximum components from all the points of the rectangle (the outline of the corners).
void AABB::Fit(MyVector3* points[4]) {
	// First, invalidate our current AABB min and max by setting min to the largest value possible, and by setting max to the smallest value possible.
	//minVector3AABB = new MyVector3(positive, positive, positive);
	minVector3AABB->x = { positive };
	minVector3AABB->y = { positive };
	minVector3AABB->z = { positive };

	//maxVector3AABB = new MyVector3(negative, negative, negative);
	maxVector3AABB->x = { negative };
	maxVector3AABB->y = { negative };
	maxVector3AABB->z = { negative };

	// Second, find the min and max of the passed-in points. I already know that any AABB this program uses will have a 4-element point array (it's a rectangle)
	// Create a size_t type because it's a safe way to iterate through the array of points, which is a collection of pointers, being memory addresses
	size_t numberOfPoints = sizeof(points) / sizeof(points[0]);

	// For each vector pointer (memory address) in the array called points (the rectangular set of points passed-in for the bounding box), find the min and max.
	// This will find the bounding box for this one sprite.
	for (size_t point = 0; point < numberOfPoints; point++) {
		MyVector3 min = min.Min(*this->minVector3AABB, *points[point]);
		MyVector3 max = max.Max(*this->maxVector3AABB, *points[point]);

		*this->minVector3AABB = min;
		*this->maxVector3AABB = max;
	};
};


/* We can test if a point is contained within an AABB by checking if the point is within the range of the min and max corners. If any component of the point is outside of these ranges then there is no overlap and we can return straight away, rather than checking any further component ranges */
bool AABB::Overlaps(MyVector3& point) {
	// Test for NOT being overlapped (faster)
	return !(
		point.x < this->minVector3AABB->x ||	// Is the point to the left of this sprite?
		point.y < this->minVector3AABB->y ||	// Is the point below the bottom of this sprite?
		point.x > this->maxVector3AABB->x ||	// Is the point to the right of this sprite?
		point.y > this->maxVector3AABB->y);		// Is the point above the top of this sprite?
};

bool AABB::Overlaps(AABB& otherObject) {
	// Test for NOT being overlapped (faster)
	return !(
		this->maxVector3AABB->x < otherObject.minVector3AABB->x ||	// Is my right side NOT touching their left side?
		this->maxVector3AABB->y < otherObject.minVector3AABB->y ||	// Is my top side NOT touching their bottom?
		this->minVector3AABB->x > otherObject.maxVector3AABB->x ||	// Is my left side NOT touching their right?
		this->minVector3AABB->y > otherObject.maxVector3AABB->y);	// Is my bottom side NOT touching their top?
};

bool AABB::Overlaps(GameObject& otherObject) {
	// Test for NOT being overlapped (faster)
	return !(
		this->maxVector3AABB->x < otherObject.colliderPtr->minVector3AABB->x ||	// Is my right side NOT touching their left side?
		this->maxVector3AABB->y < otherObject.colliderPtr->minVector3AABB->y ||	// Is my top side NOT touching their bottom?
		this->minVector3AABB->x > otherObject.colliderPtr->maxVector3AABB->x ||	// Is my left side NOT touching their right?
		this->minVector3AABB->y > otherObject.colliderPtr->maxVector3AABB->y);	// Is my bottom side NOT touching their top?
};


void AABB::debugBox2D(Color c) { // draw debug box
	DrawRectangle(
		minVector3AABB->x, 						// x
		minVector3AABB->y, 						// y
		maxVector3AABB->x - minVector3AABB->x,	// width
		maxVector3AABB->y - minVector3AABB->y,	// height
		c);										// colour
}
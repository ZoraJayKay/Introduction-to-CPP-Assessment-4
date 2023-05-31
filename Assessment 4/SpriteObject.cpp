#pragma once

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "SpriteObject.h"
#include <iostream>
#include <math.h>

//	*** CONSTRUCTOR AND DESTRUCTOR
// default constructor function
SpriteObject::SpriteObject() {
	std::cout << "---SpriteObject constructor---" << endl;

	// Set the type of game object as being a weapon
	objType = Sprite_Type;
};

// default destructor function
SpriteObject::~SpriteObject() {
	delete minVector3AABB;
	minVector3AABB = nullptr;

	delete maxVector3AABB;
	maxVector3AABB = nullptr;
};


//	*** FUNCTIONS	***
// return the width of the texture
float SpriteObject::Width() {
	return texture.width;
}

// return the height of the texture
float SpriteObject::Height() {
	return texture.height;
}

// load the image and turn it into a texture 
void SpriteObject::Load(const char* fileName)
{
	image = LoadImage(fileName);
	texture = LoadTextureFromImage(image);

	// TEMPORARY DEBUG
	cout << Height() << endl;
	cout << Width() << endl;
}

//void SpriteObject::OnUpdate(float deltaTime, Controller& ctrlr) {
//	if (GetParent().objType == Player_Type) {
//		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
//			// Rotate right a little
//			if (parent->moveSpeed > 0) {
//				this->Rotate(-deltaTime);
//			}
//		}
//		
//		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
//			if (parent->moveSpeed < 0) {
//				this->Rotate(deltaTime);
//			}
//		}
//
//			SetRotate((float)(PI / 180.0f));
//	}	
//};

 //a virtual override method for implementing specific derived drawing behaviours
void SpriteObject::OnDraw()
{
	// perform any rotation needed
	// local x-axis y and x get passed into Atan2
	float rotation = (float)atan2(globalTransform->m10, globalTransform->m00);

	Vector2 v = {globalTransform->m02, globalTransform->m12};

	// Draw the texture
	DrawTextureEx(texture, v, rotation * (float)(180 / PI), 1, WHITE);
}

// *** BOUNDING BOX FUNCTIONS ***
	// Return the centre of the collision hitbox (the point halfway between the miximum and maximum)
	MyVector3 SpriteObject::ReturnCenter() {
		return (*this->minVector3AABB + *this->maxVector3AABB) * 0.5f;
	};

	// Set the AABB min and max equal to inputs
	void SpriteObject::SetAABB(MyVector3& min, MyVector3& max) {
		*this->minVector3AABB = min;
		*this->maxVector3AABB = max;
	};

	// Extents
	// Calculate the half-extents for each vector component by subtracting the min point from the max point and then halving the absolute value 
	MyVector3 SpriteObject::Extents() {
		return MyVector3(
			abs(this->maxVector3AABB->x - this->minVector3AABB->x) * 0.5f,
			abs(this->maxVector3AABB->y - this->minVector3AABB->y) * 0.5f,
			abs(this->maxVector3AABB->z - this->minVector3AABB->z) * 0.5f);
	};

	// Return the corners of the AABB as an array of vectors, using min and max. In 2D we would return 4 corners, and in 3D we would return 8 corners. This is taking the XYZ of the min (bottom left) and the XYZ of the max (top right) and inferring the other 2 corners.
	MyVector3* SpriteObject::Corners() {
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
	void SpriteObject::Fit(MyVector3* points[4]) {
		// First, invalidate our current AABB min and max by setting min to the largest value possible, and by setting max to the smallest value possible.
		minVector3AABB = new MyVector3(positive, positive, positive);
		maxVector3AABB = new MyVector3(negative, negative, negative);

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
	bool SpriteObject::Overlaps(MyVector3& point) {
		// Test for NOT being overlapped (faster)
		return !(
			point.x < this->minVector3AABB->x ||	// Is the point to the left of this sprite?
			point.y < this->minVector3AABB->y ||	// Is the point below the bottom of this sprite?
			point.x > this->maxVector3AABB->x ||	// Is the point to the right of this sprite?
			point.y > this->maxVector3AABB->y);		// Is the point above the top of this sprite?
	};

	bool SpriteObject::Overlaps(SpriteObject& otherSprite) {
		// Test for NOT being overlapped (faster)
		return !(
			this->maxVector3AABB->x < otherSprite.minVector3AABB->x ||	// Is my right side NOT touching their left side?
			this->maxVector3AABB->y < otherSprite.minVector3AABB->y ||	// Is my top side NOT touching their bottom?
			this->minVector3AABB->x > otherSprite.maxVector3AABB->x ||	// Is my left side NOT touching their right?
			this->minVector3AABB->y > otherSprite.maxVector3AABB->y);	// Is my bottom side NOT touching their top?
	};
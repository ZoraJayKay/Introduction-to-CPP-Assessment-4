#pragma once

#include "GameObject.h"

class SpriteObject : public GameObject
{
public:
	// *** BOUNDING BOX VARIABLES ***
	float positive = 1;
	float negative = -1;

	//	*** CONSTRUCTOR & DESTRUCTOR
		// default constructor function
		SpriteObject();
		// default destructor function
		~SpriteObject();

	// ***	CLASS PARAMETERS	***
		// *** IMAGERY ***
		// a new image for converting to a texture
		Image image = Image();
		// a new texture for the sprite to use on top of the object
		Texture2D texture = Texture2D();

		// *** BOUNDING BOX ***
		// Axis-Aligned Bounding Box minimum vector3
		MyVector3* minVector3AABB; /*= new MyVector3(negative, negative, negative);*/
		// Axis-Aligned Bounding Box maximum vector3
		MyVector3* maxVector3AABB; /*= new MyVector3(positive, positive, positive);*/


	//	*** FUNCTIONS	***
	// load the image and turn it into a texture  (behaviour in source file)
	void Load(const char* fileName);
	
	// return the width of the texture
	float Width();

	// return the height of the texture
	float Height();

	//void OnUpdate(float deltaTime, Controller& ctrlr) override;


	//	*** DRAWING FUNCTIONS	***
	// definition to override the OnDraw from parent GameObject so that the sprite source file can use OnDraw with sprite texture
	void OnDraw() override;

	// *** BOUNDING BOX FUNCTIONS ***
	// Return the centre of the collision hitbox
	MyVector3 ReturnCenter();
	void SetAABB(MyVector3& min, MyVector3& max);

	// Extents
	MyVector3 Extents();

	// Return the corners of the AABB, using min and max. In 2D we would return 4 corners, and in 3D we would return 8 corners.
	MyVector3* Corners();

	// Calculate the bounding box for this sprite object
	void Fit(MyVector3* points[4]);

	/* Test if a point is contained within an AABB by checking if the point is within the range of the min and max corners. */
	bool Overlaps(MyVector3& point);

	bool Overlaps(SpriteObject& otherSprite);

	//bool Overlaps(GameObject& otherSprite);
};


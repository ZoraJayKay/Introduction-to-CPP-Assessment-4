#pragma once

#include "GameObject.h"

class SpriteObject : public GameObject
{
public:
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
		MyVector3* minVector3AABB = new MyVector3(negative, negative, negative);
		MyVector3* maxVector3AABB = new MyVector3(positive, positive, positive);


	//	*** FUNCTIONS	***
	// load the image and turn it into a texture  (behaviour in source file)
	void Load(const char* fileName);
	
	// return the width of the texture
	float Width();

	// return the height of the texture
	float Height();


	//	*** DRAWING FUNCTIONS	***
	// definition to override the OnDraw from parent GameObject so that the sprite source file can use OnDraw with sprite texture
	void OnDraw() override;


	// *** BOUNDING BOX FUNCTIONS ***
	// Return the centre of the collision hitbox
	Vector3 ReturnCenter();
};


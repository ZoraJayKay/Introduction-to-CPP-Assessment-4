#pragma once
#include "GameObject.h"

class SpriteObject : public GameObject
{
public:
	// ***	CLASS PARAMETERS	***
	// a new image for converting to a texture
	Image image = Image();
	
	// a new texture for the sprite to use on top of the object
	Texture2D texture = Texture2D();


	//	*** CONSTRUCTOR & DESTRUCTOR
	// default constructor function
	SpriteObject();

	// default destructor function
	~SpriteObject();


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
};


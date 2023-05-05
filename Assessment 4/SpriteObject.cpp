#include "SpriteObject.h"
#include <math.h>

//	*** CONSTRUCTOR AND DESTRUCTOR
// default constructor function
SpriteObject::SpriteObject() {};

// default destructor function
SpriteObject::~SpriteObject() {};


//	*** FUNCTIONS	***
// return the width of the texture through its pointer
float SpriteObject::Width() {
	return texture.width;
}

// return the height of the texture through its pointer
float SpriteObject::Height() {
	return texture.height;
}

// load the image and turn it into a texture 
void SpriteObject::Load(string fileName) 
{
	image = LoadImage(fileName);
	texture = LoadTextureFromImage(image);
}

// a virtual override method for implementing specific derived drawing behaviours
void SpriteObject::OnDraw() 
{
	// perform any rotation needed
	// local x-axis y and x get passed into Atan2
	float rotation = (float)atan2(globalTransform->m10, globalTransform->m00);

	// draw the texture
	// needs fixing
	DrawTextureEx(texture, new Vector2(globalTransform->m02, globalTransform->m12), rotation * (float)(180 / PI), 1, Color.WHITE);
}
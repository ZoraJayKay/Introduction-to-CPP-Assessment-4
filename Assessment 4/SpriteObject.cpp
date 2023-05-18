#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "SpriteObject.h"
#include <string>
#include <iostream>

//	*** CONSTRUCTOR AND DESTRUCTOR
// default constructor function
SpriteObject::SpriteObject() {
	std::cout << "---SpriteObject constructor---" << endl;

	objType = Sprite_Type;
};

// default destructor function
SpriteObject::~SpriteObject() {};


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
}

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
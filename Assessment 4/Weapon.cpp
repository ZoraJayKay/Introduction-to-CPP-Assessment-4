#include "Weapon.h"
#include "Vector3.h"
#include <iostream>
//#include "SpriteObject.h"

// Default, unused constructor
Weapon::Weapon() {};

// pass the constructor a type of weapon...
Weapon::Weapon(WeaponType choice){
	std::cout << "---Weapon constructor---" << endl;

	// Set the type of game object as being a weapon
	// objType = Projectile_Type;
	
	// Create this object a sprite
	//spritePtr = new SpriteObject();

	// file paths for new attacks to load textures
	// laserAttackFileName = "x64/Images/laserBlue01.png";
	// option 2
	// option 3

	// use an integer switch case to determine weapon attack speed
	switch (choice) {
	case 0:	// Laser fire
		// Load laser attack texture
		//spritePtr->Load(laserAttackFileName);
		// set spawn point to the end of the barrel of the weapon
		//spritePtr->SetPosition(spritePtr->Height() * 2.5f, -spritePtr->Width() / 2);
		weaponSpeed = 400;
		break;

	case 1:	// name of weapon
		weaponSpeed = 500;
		break;

	case 2:	// name of weapon
		weaponSpeed = 600;
		break;

	case 3:	// name of weapon
		weaponSpeed = 700;
		break;
	}
};

Weapon::~Weapon() {
	delete this;
	// Not sure how to set this to a nullptr...
	// this = nullptr;
};

//void Weapon::OnUpdate(float deltaTime) {
//	// Create a new vector whose elements are the x, y, z of the firing object's X axis (its forward axis) and multiply that by time and speed (set its magnitude in the direction of its forward axis).
//	// This override function goes to the SceneObject, not the SpriteObject, so there's no problem that I rotated the Sprite by 90 degrees in its constructor, because the SceneObject is still facing the right way.
//	MyVector3 facing = MyVector3(
//		this->LocalTransform().m00,
//		this->LocalTransform().m10,
//		0) * deltaTime * this->weaponSpeed;
//	Translate(facing.x, facing.y);
//};
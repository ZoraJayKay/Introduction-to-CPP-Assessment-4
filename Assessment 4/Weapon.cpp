#include "Weapon.h"
#include "Vector3.h"
#include <iostream>

// Default, unused constructor
Weapon::Weapon() {};

// pass the constructor the type of weapon the game object has right now
Weapon::Weapon(GameObject::weaponType weaponEquipped, GameObject::objectType shooter){
//Weapon::Weapon(int weaponEquipped, int shooter){
	std::cout << "---Weapon constructor---" << std::endl;
	weaponSpeed = 0;
	
	// Set whether or not the weapon was fired by the player or an enemy, eg Friendly_Projectile_Type (4) or Enemy_Projectile_Type (5)
	//this->SetObjectType(shooter);
	this->objType = shooter;
	
	// file paths for new attacks to load textures
	laserAttackFileName = "x64/Images/laserBlue01.png";
	// option 2
	// option 3

	// use an integer switch case to determine weapon attack speed
	switch (weaponEquipped) {
	case 0:	// Laser fire
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

	delete laserAttackFileName;
	laserAttackFileName = nullptr;
};

void Weapon::OnUpdate(float deltaTime, Controller& ctrlr) {
	// Create a new vector whose elements are the x, y, z of the firing object's X axis (its forward axis) and multiply that by time and speed (set its magnitude in the direction of its forward axis).
	// This override function goes to the SceneObject, not the SpriteObject, so there's no problem that I rotated the Sprite by 90 degrees in its constructor, because the SceneObject is still facing the right way.

	MyVector3 facing = MyVector3(
		this->LocalTransform().m01,
		this->LocalTransform().m11,
		0)
		* deltaTime
		* this->weaponSpeed;

	if (this->objType == Friendly_Projectile_Type) {
		// Move the object forward to the extent set by the facing vector
		this->Translate(facing.x, -facing.y);
	}

	if (this->objType == Enemy_Projectile_Type) {
		// Move the object forward to the extent set by the facing vector
		this->Translate(facing.x, facing.y);
	}
};
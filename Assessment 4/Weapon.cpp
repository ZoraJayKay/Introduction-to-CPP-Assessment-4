#pragma once

#include "Weapon.h"
#include "Vector3.h"
#include <iostream>
#include "Game.h"
#include "AABB.h"

// Default, unused constructor
Weapon::Weapon() {};

// pass the constructor the type of weapon the game object has right now
Weapon::Weapon(GameObject::weaponType weaponEquipped, GameObject::objectType shooter){
	std::cout << "---Weapon constructor---" << std::endl;
	weaponSpeed = 0;
	drag = 0;
	colliderPtr->ownerObject = this;
	
	// Set whether or not the weapon was fired by the player or an enemy, eg Friendly_Projectile_Type or Enemy_Projectile_Type
	this->objType = shooter;
	
	// use an integer switch case to determine weapon attack speed
	switch (weaponEquipped) {
	case 0:	// Laser fire
		weaponSpeed = 0;
		acceleration = 2000;
		maxWeaponSpeed = 1000;
		drag = 0;
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
	delete playerLaserAttackFileName;
	playerLaserAttackFileName = nullptr;

	delete enemyLaserAttackFileName;
	enemyLaserAttackFileName = nullptr;

	delete laserSound_01FileName;
	laserSound_01FileName = nullptr;

	delete laserSound_02FileName;
	laserSound_02FileName = nullptr;

	UnloadSound(laser_01);
	UnloadSound(laser_02);
};

void Weapon::OnUpdate(float deltaTime, Controller& ctrlr) {
	// *** --- MOVEMENT --- ***
		// Create a new vector whose elements are the x, y, z of the firing object's X axis (its forward axis) and multiply that by time and speed (set its magnitude in the direction of its forward axis).
		// This override function goes to the SceneObject, not the SpriteObject, so there's no problem that I rotated the Sprite by 90 degrees in its constructor, because the SceneObject is still facing the right way.
	
		// Acceleration effect to calculate the new speed
		this->weaponSpeed += this->acceleration * deltaTime;

		MyVector3 facing = MyVector3(
			this->LocalTransform().m01,
			this->LocalTransform().m11,
			0)
			* deltaTime
			* this->weaponSpeed;

		if (this->objType == Friendly_Projectile_Type) {
			// Shoot from the bottom of the screen to the top
			this->Translate(facing.x, -facing.y);
		}

		if (this->objType == Enemy_Projectile_Type) {
			// Shoot from the top of the screen to the bottom
			this->Translate(facing.x, facing.y);
		}

	// *** --- COLLISION DETECTION --- ***
		/*for (GameObject* collider : Game::rootObject) {
			if ()
		}*/
};
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "Controller.h"
#include "Weapon.h"
#include "Vector3.h"
#include "Timer.h"
#include <iostream>

using namespace Utilities;



Controller::Controller() {

};

Controller::~Controller() {
	// delete pointers
	// set pointer to null
};

// Conditionally move the player
void Controller::MoveSideways(GameObject& obj, float deltaTime) {
	if (IsKeyDown(KEY_D)) {
		MyVector3 facing = MyVector3(
			obj.LocalTransform().m00,
			obj.LocalTransform().m10,
			0)
			* deltaTime
			* obj.moveSpeed;

		// Move the object forward to the extent set by the facing vector
		obj.Translate(facing.x, facing.y);
	}

	if (IsKeyDown(KEY_A)) {
		MyVector3 facing = MyVector3(
			obj.LocalTransform().m00,
			obj.LocalTransform().m10,
			0)
			* deltaTime
			* obj.moveSpeed;

		// Move the object forward to the extent set by the facing vector
		obj.Translate(-facing.x, facing.y);
	}
};

//void Controller::Shoot(GameObject::WeaponType ammoType) {
//		if (IsKeyPressed(KEY_SPACE)) {
//		//Instantiate a new object of the type of weapon equipped
//		Weapon* newAttack = new Weapon(ammoType);
//	}
//}
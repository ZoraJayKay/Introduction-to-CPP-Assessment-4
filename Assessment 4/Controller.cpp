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

void Controller::Shoot(GameObject::WeaponType ammoType) {
		if (IsKeyPressed(KEY_SPACE)) {
		//Instantiate a new object of the type of weapon equipped
		Weapon* newAttack = new Weapon(ammoType);
	}
}

//// Conditionally shoot the player's weapon
//void Controller::Shoot() {
//	if (IsKeyPressed(KeyboardKey(KEY_SPACE))) {
//		//Instantiate a new object of the type of weapon equipped
//		Weapon* attack = new Weapon(plyr.GetWeapon());
//	}
//};
//
//// Conditionally move the player
//void Controller::MoveSideways() {
//	if (IsKeyDown(KeyboardKey(KEY_W))) {
//		MyVector3 facing = MyVector3(
//			plyr.LocalTransform().m00,
//			plyr.LocalTransform().m10,
//			0)
//			* 1 // delta time
//			* plyr.moveSpeed;
//
//		facing = facing * 1 * 1;
//	}
//};

//void Controller::Shoot(Player& plyr) {
//	if (IsKeyPressed(KeyboardKey(KEY_SPACE))) {
//		//Instantiate a new object of the type of weapon equipped
//		Weapon* attack = new Weapon(plyr.GetWeapon());
//
//	};
//};
//
//void Controller::MoveSideways(Player& plyr) {
//	// move left and right
//	if (IsKeyDown(KeyboardKey(KEY_W))) {
//		MyVector3 facing = MyVector3(
//			plyr.LocalTransform().m00,
//			plyr.LocalTransform().m10,
//			0)
//			* 1 // delta time
//			* plyr.moveSpeed;
//
//		facing = facing * 1 * 1;
//	}
//}
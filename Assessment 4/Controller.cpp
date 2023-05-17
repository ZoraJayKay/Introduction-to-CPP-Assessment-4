#include "Controller.h"
#include "Weapon.h"
#include "raylib.h"
#include "Vector3.h"
#include "Timer.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

using namespace Utilities;



Controller::Controller() {

};

Controller::~Controller() {
	// delete pointers
	// set pointer to null
};

// Conditionally shoot the player's weapon
void Controller::Shoot() {
	if (IsKeyPressed(KeyboardKey(KEY_SPACE))) {
		//Instantiate a new object of the type of weapon equipped
		Weapon* attack = new Weapon(plyr.GetWeapon());
	}
};

// Conditionally move the player
void Controller::MoveSideways() {
	if (IsKeyDown(KeyboardKey(KEY_W))) {
		MyVector3 facing = MyVector3(
			plyr.LocalTransform().m00,
			plyr.LocalTransform().m10,
			0)
			* 1 // delta time
			* plyr.moveSpeed;

		facing = facing * 1 * 1;
	}
};



void Controller::Shoot(Player& plyr) {
	if (IsKeyPressed(KeyboardKey(KEY_SPACE))) {
		//Instantiate a new object of the type of weapon equipped
		Weapon* attack = new Weapon(plyr.GetWeapon());

	};
};

void Controller::MoveSideways(Player& plyr) {
	// move left and right
	if (IsKeyDown(KeyboardKey(KEY_W))) {
		MyVector3 facing = MyVector3(
			plyr.LocalTransform().m00,
			plyr.LocalTransform().m10,
			0)
			* 1 // delta time
			* plyr.moveSpeed;
		
		facing = facing * 1 * 1;
	}
}







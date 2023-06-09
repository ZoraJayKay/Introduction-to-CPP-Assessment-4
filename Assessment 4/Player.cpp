#pragma once

#include "Player.h"
#include <iostream>
#include "Controller.h"
#include "AABB.h"

// default constructor
Player::Player() {
	std::cout << "---Empty Player constructor---" << endl;
};

// overloaded constructor
Player::Player(int _lives, bool _hasWeapon, int _score, GameObject::weaponType startingWeapon)
{
	std::cout << "---Overloaded Player constructor---" << endl;
	moveAcceleration = 550;
	moveDrag = -800;
	maxSpeed = 500;
	moveSpeed = 0;
	lives = _lives;
	hasWeapon = _hasWeapon;
	score = _score;
	this->SetWeapon(startingWeapon); // Laser by default
	colliderPtr->ownerObject = this;
	this->objType = GameObject::Player_Type;
}


// default destructor
Player::~Player() {}

void Player::OnUpdate(float deltaTime, Controller& ctrlr){
	// PLAYER MOVEMENT
	ctrlr.MoveSideways(*this, deltaTime);

	// Call a function that can shoot if a key is pressed
	ctrlr.Shoot(*this, this->weaponEquipped);

	// progress the reload cycle by 1 frame
	ctrlr.shotTimer++;
	// If 60 frames have passed (approx 1 second)...
	if (ctrlr.shotTimer > 45) {
		ctrlr.shotTimer = 45;
		ctrlr.weaponReloaded = true;
	}

	// Don't let lives regress to maximum value as a result of lives decrementing through collision detection (unsigned int will wrap-around to 4294967295)
	// Max lives set at 5, but player shouldn't be able to accidentally die if they exceed 5 lives through a pick-up, as actual collectable lives will be set to 3
	if (this->lives > 5) {
		this->lives = 0;
	}
};
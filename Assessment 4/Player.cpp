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
	objType = Player_Type;
	colliderPtr->ownerObject = this;
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
};
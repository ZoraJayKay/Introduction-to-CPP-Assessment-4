#include "Player.h"
#include <iostream>

// default constructor
Player::Player() {
	std::cout << "---Player constructor---" << endl;

	objType = Player_Type;
};


// default destructor
Player::~Player() {};


// overloaded constructor
Player::Player(int _lives, bool _hasWeapon, int _score)
{
	std::cout << "---Overloaded Player constructor---" << endl;

	lives = _lives;	
	hasWeapon = _hasWeapon;
	score = _score;
	// weaponEquipped = 0; // Laser by default

	objType = Player_Type;

	// Set movement speed to standard
	moveSpeed = 250;
}

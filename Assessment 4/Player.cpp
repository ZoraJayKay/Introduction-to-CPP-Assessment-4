#include "Player.h"

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

	objType = Player_Type;
}

// a virtual method for implementing specific derived drawing behaviours for the player
//void GameObject::OnUpdate(float deltaTime) 
//{
//
//}

// look up how to override in C++
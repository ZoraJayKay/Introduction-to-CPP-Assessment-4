#include "Player.h"

Player::Player() {};
Player::~Player() {};

// fix enum
Player::Player(int _lives, int _type, bool _hasWeapon, int _score)
{
	std::cout << "---Player constructor---" << endl;

	lives = _lives;	
	objectType = _type;
	hasWeapon = _hasWeapon;
	score = _score;
}

// a virtual method for implementing specific derived drawing behaviours for the player
//void GameObject::OnUpdate(float deltaTime) 
//{
//
//}
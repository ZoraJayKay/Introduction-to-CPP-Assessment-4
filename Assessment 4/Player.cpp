#include "Player.h"
#include "GameObject.cpp"

Player::Player() {};
Player::~Player() {};

// fix enum
Player::Player(int _lives, enum _type, bool _weapon, int _score)
{
	std::cout << "---Player constructor---" << endl;

	lives = _lives;	
	objectType = _type;
	hasWeapon = _weapon;
	score = _score;
}

// a virtual method for implementing specific derived drawing behaviours for the player
//void GameObject::OnUpdate(float deltaTime) 
//{
//
//}
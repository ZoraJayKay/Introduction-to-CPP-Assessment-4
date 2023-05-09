#include "Player.h"

Player::Player() {};

// fix enum
Player::Player(int health, objectType type, bool weapon)
{
	health = lives;
	//type = objectType;
	weapon = hasWeapon;
}

// a virtual method for implementing specific derived drawing behaviours for the player
//void GameObject::OnUpdate(float deltaTime) 
//{
//
//}
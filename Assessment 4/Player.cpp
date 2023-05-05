#include "Player.h"

Player::Player() {};

// fix string / number conversion for enum
Player::Player(int health, enum enumType, bool weapon)
{
	health = lives;
	enumType = objectType;
	weapon = hasWeapon;
}

// a virtual method for implementing specific derived drawing behaviours for the player
void GameObject::OnUpdate(float deltaTime) 
{

}
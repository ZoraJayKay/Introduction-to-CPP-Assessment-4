#pragma once
#include "GameObject.h"
// This class is a container for all of the things that collectively represent the player

class Player : public GameObject
{
public:
	// Player variables

	//	***		CONSTRUCTOR & DESTRUCTOR	***
	// default constructor function
	Player();

	// custom constructor
	Player(int _lives, bool _hasWeapon, int score, GameObject::weaponType startingWeapon);

	// default destructor function
	~Player();
};


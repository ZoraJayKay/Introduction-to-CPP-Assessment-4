#pragma once
#include "GameObject.h"

// This class is a container for all of the things that collectively represent the player

class Player : GameObject
{
public:
	//	***		CONSTRUCTOR & DESTRUCTOR	***
	// default constructor function
	Player() {};

	// custom constructor
	Player(int health, enum enumType, bool weapon) {}

	// default destructor function
	~Player() {};
};


#pragma once
#include "Player.h"
#include "Game.h"
#include "GameObject.h"

class Controller
{
public:
	Controller();

	/*void MoveSideways(Player& plyr);
	void Shoot(Player& plyr);*/

	void MoveSideways();
	void Shoot();

	~Controller();
};


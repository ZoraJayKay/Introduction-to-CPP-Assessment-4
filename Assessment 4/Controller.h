#pragma once
#include "Player.h"
#include "Game.h"

class Controller
{
public:
	Controller();

	void MoveLeft(Player& plyr);
	void Shoot(Player& plyr);

	~Controller();
};


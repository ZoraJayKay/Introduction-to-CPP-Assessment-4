#pragma once
#include "GameObject.h"
#include "Weapon.h"

class Controller
{
public:
	class Game* g;

	Controller();
	Controller(Game& gme);

	

	void MoveSideways(GameObject& obj, float deltaTime);

	void Shoot(GameObject::weaponType weaponEquipped);

	~Controller();
};


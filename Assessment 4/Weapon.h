#pragma once
#include "GameObject.h"

class Weapon
{
public:
	int weaponSpeed;

	Weapon(GameObject::WeaponType choice);
	~Weapon();
};


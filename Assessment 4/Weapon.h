#pragma once
#include "GameObject.h"

class Weapon
// class Weapon : public GameObject
{
protected:
	// class SpriteObject* spritePtr;

public:
	enum WeaponType {
		Laser
	};

	int weaponSpeed;
	const char* laserAttackFileName;
	
	Weapon();
	Weapon(WeaponType choice);
	~Weapon();

	//void OnUpdate(float deltaTime) override;
};


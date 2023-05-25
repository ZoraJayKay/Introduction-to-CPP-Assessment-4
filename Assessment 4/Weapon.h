#pragma once

#include "GameObject.h"

class Weapon : public GameObject
{
protected:
	class SpriteObject* attackSpritePtr;

public:
	//enum WeaponType;	
	int weaponSpeed;
	const char* playerLaserAttackFileName;
	const char* enemyLaserAttackFileName;
	// other weapon 2 file name
	// other weapon 3 file name

	Weapon();
	Weapon(GameObject::weaponType weaponEquipped, GameObject::objectType shooter);
	// Weapon(int weaponEquipped, int shooter);
	~Weapon();

	void OnUpdate(float deltaTime, Controller& ctrlr) override;
};


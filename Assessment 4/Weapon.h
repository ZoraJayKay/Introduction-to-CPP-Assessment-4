#pragma once
#include "GameObject.h"

class Weapon : public GameObject
{
protected:
	class SpriteObject* attackSpritePtr;

public:
	//enum WeaponType;	
	int weaponSpeed;
	const char* laserAttackFileName;
	
	Weapon();
	Weapon(GameObject::weaponType weaponEquipped);
	~Weapon();

	void OnUpdate(float deltaTime) override;
};


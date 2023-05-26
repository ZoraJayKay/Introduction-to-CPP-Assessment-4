#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
protected:
	bool movingRight;

public:
	int shotTimer;
	int advanceTracker;
	bool reachedEarth;

	Enemy();
	Enemy(int _moveSpeed, GameObject::weaponType startingWeapon);
	
	~Enemy();

	void OnUpdate(float deltaTime, Controller& ctrlr) override;
	/*void ShootRandomly(GameObject& obj, GameObject::weaponType weaponEquipped) override;*/

	void MoveSideways(float deltaTime);
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void Advance(float deltaTime);
};


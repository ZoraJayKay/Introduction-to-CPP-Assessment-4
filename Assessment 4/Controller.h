#pragma once
#include "GameObject.h"
#include "Weapon.h"

class Controller
{
public:
	class Game* g;
	bool isMoving;
	bool movingRight;
	bool movingLeft;

	float velocity;
	//float acceleration;
	float speedScale;
	float speedMin;
	float speedMax;

	Controller();
	Controller(Game& gme);
	
	void MoveSideways(GameObject& obj, float deltaTime);

	void Shoot(GameObject& obj, GameObject::weaponType weaponEquipped);
	void ShootRandomly(GameObject& obj, GameObject::weaponType weaponEquipped);
	void InstantiatePlayerAttack(GameObject& obj, GameObject::weaponType weaponEquipped);
	void InstantiateEnemyAttack(GameObject& obj, GameObject::weaponType weaponEquipped);

	~Controller();
};


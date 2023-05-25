#pragma once
#include "GameObject.h"
#include "Weapon.h"

class Controller
{
public:
	// Create a pointer to a game object so that the controller can interact with the hierarchy of objects 
	class Game* g;

	// Variables for 
	bool isMoving;
	bool movingRight;
	bool movingLeft;

	Controller();
	Controller(Game& gme);
	
	void MoveSideways(GameObject& obj, float deltaTime);

	void Shoot(GameObject& obj, GameObject::weaponType weaponEquipped);
	// void Shoot(GameObject& obj, int weaponEquipped);
	void ShootRandomly(GameObject& obj, GameObject::weaponType weaponEquipped);
	void InstantiatePlayerAttack(GameObject& obj, GameObject::weaponType weaponEquipped);
	//void InstantiatePlayerAttack(GameObject& obj, int weaponEquipped);
	void InstantiateEnemyAttack(GameObject& obj, GameObject::weaponType weaponEquipped);

	~Controller();
};


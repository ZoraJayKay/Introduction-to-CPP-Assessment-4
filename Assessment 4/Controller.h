#pragma once

#include "GameObject.h"
#include "Weapon.h"

class Controller
{
public:
	// Create a pointer to a game object so that the controller can interact with the hierarchy of objects 
	class Game* g;

	// Variables for tracking movement
	bool isMoving;

	bool weaponReloaded;
	int shotTimer;

	// 

	Controller();
	Controller(Game& gme);
	~Controller();
	
	// A function to conditionally move the player based on keystrokes
	void MoveSideways(GameObject& player, float deltaTime);

	// Player functions
		// A function to detect whether the player has pressed a key to attack
		void Shoot(GameObject& player, GameObject::weaponType weaponEquipped);
		// Instantiate a player attack
		void InstantiatePlayerAttack(GameObject& player, GameObject::weaponType weaponEquipped);

	// Enemy functions
		// A function to let enemies fire at the player (see Enemy class OnUpdate() for what triggers this function)
		void ShootRandomly(GameObject& enemy, GameObject::weaponType weaponEquipped);
		// Instantiate an enemy attack
		void InstantiateEnemyAttack(GameObject& enemy, GameObject::weaponType weaponEquipped);
};


#pragma once

// Include useful libraries
#include "Matrix3.h"
#include "Vector3.h"
#include <cmath>
#include <vector>
#include "assert.h"

using namespace std;

// Create a blueprint for any object with a transform in the game
class GameObject
{
protected: 
	//	*** PROTECTED GAME PARAMETERS***
	// declare a pointer to a GameObject called parent
	GameObject* parent;

	// declare a vector of GameObject pointers to hold pointers to any child objects
	vector<GameObject*> children;	

	// create pointers to Matrix3's for local and global transform
	Matrix3* localTransform = new Matrix3(1);
	Matrix3* globalTransform = new Matrix3(1);
	
	// Pointer for the controller 
	class Controller* ctrlr;

	// Pointer for use with enemies
	class Enemy* enemyPtr;

public:
	//	*** PUBLIC GAME PARAMETERS	***
	// object type
	enum objectType	{
		Default_Type,
		Sprite_Type,
		Player_Type,
		Enemy_Type,
		Friendly_Projectile_Type,
		Enemy_Projectile_Type,
		Base_Type
	};
	
	// The type of game object
	objectType objType;
	
	enum weaponType {
		Laser,
		DoubleLaser,
	};

	weaponType weaponEquipped;

	// Movement speed of the object
	int moveSpeed;

	// Does this object have a weapon, true or false?
	bool hasWeapon;

	// How many lives does this object have?
	unsigned int lives;

	// The player's score
	unsigned int score;

	//	*** CONSTRUCTOR & DESTRUCTOR	***
		// default constructor function
		GameObject();

		// default destructor function
		~GameObject();

	//	*** FUNCTIONS	***
		// Return the equipped weapon of a game object as an integer
		int GetWeapon();
		// behaviour determined by derivative class, eg enemy, player, base

		void SetWeapon(weaponType chosenWeapon);

		void SetObjectType(int choice);

	// ***	RELATIONSHIP FUNCTIONS	***
		// A method to set the parent of the object that calls this function equal to an object that is passed in (by reference to it)
		void SetParent(GameObject& parent_01);
	
		// A method to return a pointer to the parent of this object
		GameObject& GetParent();

		// A method to count the children of this object
		int CountChildren();

		// A method to add a child to this object
		void AddChild(GameObject& child);

		// A method to remove a child from this object
		void RemoveChild(GameObject& child);


	// ***	UPDATE FUNCTIONS	***
		// CALCULATIONS
			// Create virtual OnUpdate function for use by separate object types. Behaviour determined by derivative class.
			virtual void OnUpdate(float deltaTime, Controller& ctrlr);
			
			// Update for objects that only need time
			virtual void OnUpdate(float deltaTime);

			// a non-virtual method that first calls OnUpdate() on itself, then calls Update() on all children
			void Update(float deltaTime, Controller& ctrlr);

		// ***	DRAW FUNCTIONS		***
			// ON-SCREEN GRAPHICS
			// a virtual method for implementing specific derived drawing behaviours
			virtual void OnDraw();
	
			// a non-virtual method that first calls OnDraw() on itself and then calls Draw() on all children
			void Draw();
	

	//	*** TRANSFORM FUNCTIONS	***
		// MOVE AND ROTATE AN OBJECT
		// get the protected location of local Matrix3
		Matrix3 LocalTransform();

		// get the protected location of global Matrix3
		Matrix3 GlobalTransform();

		// update the global transform of this object
		void UpdateTransform();

		// call the Matrix3 class to set the object's position
		void SetPosition(float x, float y);

		// call the Matrix3 class to set the object's rotation
		void SetRotate(float radians);

		// call the Matrix3 class to incrementally move the object
		void Translate(float x, float y);

		// call the Matrix3 class to incrementally rotate the object
		void Rotate(float radians);

		// Call the Matrix3 class so a child may inherit its parent's global position
		void CopyTransform(GameObject& prnt);
};
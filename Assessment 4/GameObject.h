#pragma once
#include "Matrix3.h"
#include "raylib.h"
#include <cmath>
#include <vector>
#include "assert.h"

// Create a blueprint for any object with a transform in the game

class GameObject
{

private:
	// private stuff here (C++ classes are private by default)
	

protected: 
	//	*** PROTECTED GAME PARAMETERS***
	// declare a pointer to a parent object
	GameObject* parent;

	// declare a vector of GameObject pointers to hold pointers to any child objects
	std::vector<GameObject*> children;	
		// this vector has been 

	// create pointers to Matrix3's for local and global transform
	Matrix3* localTransform = new Matrix3(1);
	Matrix3* globalTransform = new Matrix3(1);
	

public:
	//	*** PUBLIC GAME PARAMETERS	***
	// object type
	enum objectType;

	// is this character armed?
	bool hasWeapon;

	// variable to count object's number of lives
	unsigned int lives;


	//	*** CONSTRUCTOR & DESTRUCTOR	***
	// default constructor function
	GameObject();

	// default destructor function
	~GameObject();

	//	*** FUNCTIONS	***
	// Instantiate a weapon for this object if it is meant to have one, maybe some enemies will, some won't, base won't, etc
	void virtual GetWeapon();
	// behaviour determined by derivative class, eg enemy, player, base

	
	// ***	RELATIONSHIP FUNCTIONS	***
	// A method to set the parent of this object
	void SetParent(GameObject* parent_01);
	
	// A method to return a pointer to the parent of this object
	GameObject* GetParent();

	// A method to count the children of this object
	int CountChildren();

	// A method to add a child to this object
	void AddChild(GameObject* child);

	// A method to remove a child from this object
	void RemoveChild(GameObject* child);


	// ***	UPDATE FUNCTIONS	***
	// CALCULATIONS
	// Create virtual OnUpdate function for use by separate types
	void virtual OnUpdate(float deltaTime);
		// behaviour determined by derivative class eg player, enemy, base

	void Update(float deltaTime);
		// a non-virtual method that first calls OnUpdate() on itself, then calls Update() on all children

	// DRAW
	// a virtual method for implementing specific derived drawing behaviours
	void virtual OnDraw();

	// a non-virtual method that first calls OnDraw() on itself and then calls Draw() on all children
	void Draw();


	//	*** TRANSFORM FUNCTIONS	***
	// get protected location of local Matrix3
	Matrix3* LocalTransform();

	// get protected location of global Matrix3
	Matrix3* GlobalTransform();

	// update the location of this object
	void UpdateTransform();
};
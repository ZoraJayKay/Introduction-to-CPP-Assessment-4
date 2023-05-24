#pragma once
#include "GameObject.h"
#include "Controller.h"
#include <iostream>

// Weapon options
enum WeaponType {
	Laser,
	DoubleLaser,
};

// member function for constructor
GameObject::GameObject() 
{
	std::cout << "---GameObject constructor---" << endl;
};

// member function for destructor
GameObject::~GameObject() {
	// Delete parent object pointer
	delete parent;
	parent = nullptr;

	// Delete controller object pointer
	delete ctrlr;
	ctrlr = nullptr;

	// Delete enemy object pointer
	delete enemyPtr;
	enemyPtr = nullptr;

	// Delete vector of pointers of child objects
	for (GameObject* obj : children) {
		delete obj;
		obj = nullptr;
	}

	// Delete matrices of transforms
	delete localTransform;
	localTransform = nullptr;

	delete globalTransform;
	globalTransform = nullptr;
};

// Return the equipped weapon of a game object as an integer
int GameObject::GetWeapon() {
	return this->weaponEquipped;
};

// a method to set the weapon of this object
void GameObject::SetWeapon(weaponType chosenWeapon) {
	this->weaponEquipped = chosenWeapon;
};

//void GameObject::ShootRandomly(GameObject& obj, weaponType weaponEquipped) {
//	// override this in derivative classes for each object type's functions, if relevant
//};

//	*** PUBLIC GAME PARAMETERS	***



// ***	RELATIONSHIP FUNCTIONS	***
// A method to set the parent of the object that calls this function equal to an object that is passed in (by reference to it)
void GameObject::SetParent(GameObject& parent_01) 
{
	*this->parent = parent_01;
	// in the contents of the object that called this function, set the parent object to the one that was passed in as a parameter
};

// A method to return a pointer to the parent of this object
GameObject& GameObject::GetParent() {
	return *this->parent;
	// we return a dereferenced 'parent' because parent is a pointer, so by dereferencing it we return its contents
	// don't I want to return the object, not its contents?
};

// A method to count the children of this object
int GameObject::CountChildren(){	
	// cout << "This object has " << this->children.size() << " children." << endl;
	return this->children.size();
	// this returns actual volume of elements, not a memory address
};

// A method to add a child to this object
void GameObject::AddChild(GameObject& child) {
	GameObject* child_01 = &child;
	assert(child_01->parent == NULL);
	// check whether or not the child already has a parent object
	child_01->parent = this;
	// assign the object that called this function as the parent object
	children.push_back(child_01);
	// push back adds an element to the END of the vector
};

// A method to remove a child from this object
void GameObject::RemoveChild(GameObject& child) {
	// implement
};


//	***	UPDATE FUNCTIONS	***
// Pass the controller to the game object
void GameObject::OnUpdate(float deltaTime, Controller& ctrlr) {
	// PLAYER MOVEMENT
	if (objType == Player_Type) {
		// Call a function that can move the player
		ctrlr.MoveSideways(*this, deltaTime);

		// Call a function that can shoot if a key is pressed
		ctrlr.Shoot(*this, this->weaponEquipped);
	}

	// Enemy movement comes frm overridden OnUpdate() in Enemy class
}


// Update for objects that only need time
void GameObject::OnUpdate(float deltaTime) {};


// Update for objects that need time and the controller
void GameObject::Update(float deltaTime, Controller& ctrlr) {
	OnUpdate(deltaTime, ctrlr);
	for (GameObject* child : children) {
		child->Update(deltaTime, ctrlr);
	}
};


// ***	DRAW FUNCTIONS	***
	// a virtual method for implementing specific derived drawing behaviours
void GameObject::OnDraw() {};


// a non-virtual method that first calls OnDraw() on itself and then calls Draw() on all children
void GameObject::Draw() 
{
	OnDraw();

	for (GameObject* child : children)	{
		child->Draw();
	}
};


//	*** TRANSFORM FUNCTIONS	***
// get protected location of local Matrix3
Matrix3 GameObject::LocalTransform() {
	return *localTransform;
}

// get protected location of global Matrix3
Matrix3 GameObject::GlobalTransform(){
	return *globalTransform;
}


// update the global transform of this object
void GameObject::UpdateTransform()
{
	// 1: Update own global transform
	// The global transform is a combination of the object’s local transform and its parent’s global transform. 

	if (this->parent != NULL)	{
		*(this->globalTransform) = *(this->parent->globalTransform) * *(this->localTransform);
		// The global transform is a combination of the object’s local transform and its parent’s global transform. 
	}

	else	{
		*(this->globalTransform) = *(this->localTransform);
		// If an object has no parent then its global transform is the same as its local transform.
	}

	// 2: Update global transform of this object's children
	for (GameObject* child : children)	{
		child->UpdateTransform();
	}
};

// call the Matrix3 class to set the object's position
void GameObject::SetPosition(float x, float y){
	localTransform->SetTranslation(x, y);
	UpdateTransform();
}

// call the Matrix3 class to set the object's rotation
void GameObject::SetRotate(float radians) {
	localTransform->SetRotateZ(radians);
	UpdateTransform();
}

// call the Matrix3 class to incrementally move the object
void GameObject::Translate(float x, float y) {
	localTransform->Translate(x, y);
	UpdateTransform();
}

// call the Matrix3 class to incrementally rotate the object
void GameObject::Rotate(float radians) {
	*localTransform = localTransform->RotateZ(radians);
	UpdateTransform();
}

// Call the Matrix3 class so a child may inherit its parent's global position
void GameObject::CopyTransform(GameObject& prnt) {
	Matrix3* m = new Matrix3;
	*m = prnt.GlobalTransform();
	this->localTransform->Set(*m);
	UpdateTransform();

	delete m;
	m = nullptr;
};
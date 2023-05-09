#include "GameObject.h"

// member function for constructor
GameObject::GameObject() {};

// member function for destructor
GameObject::~GameObject() {};

// a method to set the weapon of this object
void GameObject::GetWeapon() {};


//	*** PUBLIC GAME PARAMETERS	***
	// object type
enum GameObject::objectType
{
	Sprite,
	Player,
	Enemy,
	Projectile,
	Base
};


// ***	RELATIONSHIP FUNCTIONS	***
// A method to set the parent of this object as a pointer to another object
void GameObject::SetParent(GameObject* parent_01) 
{
	this->parent = parent_01;
};

// A method to return a pointer to the parent of this object
GameObject* GameObject::GetParent() 
{
	return parent;
};

// A method to count the children of this object
int GameObject::CountChildren()
{	
	return children.size();
	// this returns actual vlume of elements, not a memory address
};

// A method to add a child to this object
void GameObject::AddChild(GameObject* child) 
{
	assert(child->parent == NULL);
	// check whether or not the child already has a parent object
	child->parent = this;
	// assign the object that called this function as the parent object
	children.push_back(child);
	// push back adds an element to the END of the vector
};

// A method to remove a child from this object
void GameObject::RemoveChild(GameObject* child) 
{
	// implement
};


//	***	UPDATE FUNCTIONS	***
// a virtual method for behaviour during updates (to be overwritten by derivative classes)
// OnUpdate() uses the elapsed delta time as a parameter so that behaviours that use time have access to it
void GameObject::OnUpdate(float deltaTime) {};

// a non-virtual recursive method that first calls OnUpdate() on itself, then calls Update() on all children
void GameObject::Update(float deltaTime) 
{
	OnUpdate(deltaTime);
	
	// FIX FOR LISTS 
	for (GameObject* child : children)
	{
		child->Update(deltaTime);
	}
};


// ***	DRAW FUNCTIONS	***
	// a virtual method for implementing specific derived drawing behaviours
void GameObject::OnDraw() {};

// a non-virtual method that first calls OnDraw() on itself and then calls Draw() on all children
void GameObject::Draw() 
{
	OnDraw();

	// FIX FOR LISTS 
	for (GameObject* child : children)
	{
		child->Draw();
	}
};


//	*** TRANSFORM FUNCTIONS	***
// get protected location of local Matrix3
Matrix3* GameObject::LocalTransform() 
{
	return localTransform;
}

// get protected location of global Matrix3
Matrix3* GameObject::GlobalTransform()
{
	return globalTransform;
}

//void GameObject::UpdateTransform() 
//{
//	// 1: Update own global transform
//	// The global transform is a combination of the object’s local transform and its parent’s global transform. 
//	
//	// fix
//	if (this->parent != NULL)
//	{
//		this->globalTransform = parent->globalTransform * this->localTransform;
//		// The global transform is a combination of the object’s local transform and its parent’s global transform. 
//	}
//
//	else
//	{
//		globalTransform = localTransform;
//		// If an object has no parent then its global transform is the same as its local transform.
//	}
//
//	// update global transform of object's children
//	// fix list
//	for (GameObject* child : children)
//	{
//		child->UpdateTransform();
//	}
//
//	// 2: Update global transform of children
//};
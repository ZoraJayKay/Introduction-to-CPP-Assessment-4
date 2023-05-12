#pragma once
#include "GameObject.h"


// member function for constructor
GameObject::GameObject() 
{
	std::cout << "---GameObject constructor---" << endl;
};

// member function for destructor
GameObject::~GameObject() {};

// a method to set the weapon of this object
void GameObject::GetWeapon() {};

//	*** PUBLIC GAME PARAMETERS	***
	// object type
//enum GameObject::objectType
//{
//	Default_Type,
//	Sprite_Type,
//	Player_Type,
//	Enemy_Type,
//	Projectile_Type,
//	Base_Type
//};


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
// a virtual method for behaviour during updates (to be overwritten by derivative classes)
// OnUpdate() uses the elapsed delta time as a parameter so that behaviours that use time have access to it
void GameObject::OnUpdate(float deltaTime) {};

// a non-virtual recursive method that first calls OnUpdate() on itself, then calls Update() on all children
void GameObject::Update(float deltaTime) 
{
	OnUpdate(deltaTime);
	
	// FIX FOR LISTS 
	for (GameObject* child : children)	{
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

}
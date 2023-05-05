#include "GameObject.h"

// member function for constructor
GameObject::GameObject() {};

// member function for destructor
GameObject::~GameObject() {};

// a method to set the weapon of this object
void GameObject::GetWeapon() {};


// ***	RELATIONSHIP FUNCTIONS	***
// A method to return a pointer to the parent of this object
GameObject* GameObject::GetParent() {
	return parent;
};

// A method to count the children of this object
// RESEARCH LISTS
int GameObject::CountChildren()
{
	// return count of List<GameObject* children>
};

// A method to add a child to this object
void GameObject::AddChild(GameObject* child) 
{
	// implementation
};

// A method to remove a child from this object
void GameObject::RemoveChild(GameObject* child) 
{
	// implementation
};


//	***	UPDATE FUNCTIONS	***
// a virtual method for behaviour during updates (to be overwritten by derivative classes)
void GameObject::OnUpdate(float deltaTime) {};

// a non-virtual recursive method that first calls OnUpdate() on itself, then calls Update() on all children
void GameObject::Update(float deltaTime) 
{
	OnUpdate(deltaTime);
	
	// FIX FOR LISTS 
	for (GameObject* child : <List>children)
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
	for (GameObject* child : <List>children)
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

void GameObject::UpdateTransform() 
{
	// 1: Update own global transform
	// The global transform is a combination of the object’s local transform and its parent’s global transform. 
	
	// fix
	if (parent != null)
	{
		globalTransform = parent->globalTransform * localTransform;
		// The global transform is a combination of the object’s local transform and its parent’s global transform. 
	}

	else
	{
		globalTransform = localTransform;
		// If an object has no parent then its global transform is the same as its local transform.
	}

	// update global transform of object's children
	// fix list
	for (GameObject* child : <List>children)
	{
		child->UpdateTransform();
	}

	// 2: Update global transform of children
};
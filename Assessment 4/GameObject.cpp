#pragma once

#include "GameObject.h"
#include "Controller.h"
#include "AABB.h"
#include <iostream>

// member function for constructor
GameObject::GameObject() 
{
	std::cout << "---GameObject constructor---" << endl;
	colliderPtr = new AABB;
	colliderPtr->ownerObject = this;
};

// member function for destructor
GameObject::~GameObject() {
	// AABB pointers are destroyed within the AABB's own destructor

	// Delete vector of pointers of child objects
	/*for (GameObject* obj : children) {
		delete obj;
		obj = nullptr;
	}*/

	// Delete matrices of transforms
	//delete localTransform;
	//localTransform = nullptr;

	//delete globalTransform;
	//globalTransform = nullptr;
};

// Return the equipped weapon of a game object as an integer
int GameObject::GetWeapon() {
	return this->weaponEquipped;
};

// a method to set the weapon of this object
void GameObject::SetWeapon(weaponType chosenWeapon) {
	this->weaponEquipped = chosenWeapon;
};

// A function for setting the enum gameobject type of the calling object using an int
void GameObject::SetObjectType(int choice) {
	switch (choice) {
	case 0: this->objType = Default_Type;
	case 1: this->objType = Sprite_Type;
	case 2: this->objType = Player_Type;
	case 3: this->objType = Enemy_Type;
	case 4: this->objType = Friendly_Projectile_Type;
	case 5: this->objType = Enemy_Projectile_Type;
	case 6: this->objType = Base_Type;
	}	
};

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
void GameObject::RemoveChild(GameObject* child) {
	// Implement
	
	// create an iterator which will find the pointer to remove in the children vector
	vector<GameObject*>::iterator itr = find(children.begin(), children.end(), child);

	// save the position between index 0 and the found pointer
	int index = distance(children.begin(), itr);

	// erase the found pointer from the vector
	children.erase(children.begin() + index);
};

// A method to remove all children from this object
void GameObject::RemoveChildren() {
	for (GameObject* child : GetChildren()) {
		delete child;
		child = nullptr;
	}
};

vector<GameObject*> GameObject::GetChildren() {
	return this->children;
};


//	***	UPDATE FUNCTIONS	***
// Create virtual OnUpdate function for use by separate object types. Behaviour determined by derived class.
void GameObject::OnUpdate(float deltaTime, Controller& ctrlr) {}

// Update for objects that only need time
void GameObject::OnUpdate(float deltaTime) {};


// Update for objects that need time and the controller
void GameObject::Update(float deltaTime, Controller& ctrlr) {
	// Collision detection
	UpdateColliderBoundaries();
	// temporary debug
	if (this->objType == GameObject::Base_Block_Type) {
		this->colliderPtr->debugAlteredBox2D(RED);
	}
	
	else if (this->objType == GameObject::Base_Type) {
		this->colliderPtr->debugBox2D(BLUE);
	}

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

//	*** COLLISION DETECTION	***
	// Update the collision detection boundaries of this game object
void GameObject::UpdateColliderBoundaries() {
	// Bases have their own process for updating their boundary boxes in the OnDraw() of Base.cpp
	if (colliderPtr->ownerObject->objType != Base_Type && 
		colliderPtr->ownerObject->objType != Base_Block_Type) {
		// Overwrite temporary vector3's for updating AABB outer boundaries each update
		// AABB min:
		MyVector3* tempV1 = new MyVector3(
			(this->globalTransform->m02),
			(this->globalTransform->m12),
			0.0f);

		// AABB max:
		MyVector3* tempV2 = new MyVector3(
			(this->globalTransform->m02 + (colliderPtr->AABBtextureWidth)),
			(this->globalTransform->m12 + (colliderPtr->AABBtextureHeight)),
			0.0f);

		// Make projectiles very thin so they won't collide with multiple hit boxes simultaneously
		if (colliderPtr->ownerObject->objType == Friendly_Projectile_Type ||
			colliderPtr->ownerObject->objType == Enemy_Projectile_Type){
				MyVector3* minBuffer = new MyVector3{ 5, 0 , 0 };
				MyVector3* maxBuffer = new MyVector3{ -5, 0, 0 };

				MyVector3 newMin = *minBuffer + *tempV1;
				MyVector3 newMax = *maxBuffer + *tempV2;
			
				colliderPtr->UpdateBoxBoundries(newMin, newMax);

				delete minBuffer;
				minBuffer = nullptr;

				delete maxBuffer;
				maxBuffer = nullptr;
		}

		else {
			// Update using AABB min and max
			colliderPtr->UpdateBoxBoundries(*tempV1, *tempV2);
		}
		
		delete tempV1;
		tempV1 = nullptr;

		delete tempV2;
		tempV2 = nullptr;
	};
}
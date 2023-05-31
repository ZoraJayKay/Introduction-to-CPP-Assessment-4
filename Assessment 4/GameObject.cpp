#pragma once

#include "GameObject.h"
#include "Controller.h"
#include <iostream>

// member function for constructor
GameObject::GameObject() 
{
	std::cout << "---GameObject constructor---" << endl;
};

// member function for destructor
GameObject::~GameObject() {
	// Delete parent object pointer
	/*delete parent;
	parent = nullptr;*/

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
void GameObject::RemoveChild(GameObject& child) {
	// implement
};


//	***	UPDATE FUNCTIONS	***
// Create virtual OnUpdate function for use by separate object types. Behaviour determined by derivative class.
void GameObject::OnUpdate(float deltaTime, Controller& ctrlr) {}

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

//// *** BOUNDING BOX FUNCTIONS ***
//	// Return the centre of the collision hitbox (the point halfway between the miximum and maximum)
//	MyVector3 GameObject::ReturnCenter() {
//		return (*this->minVector3AABB + *this->maxVector3AABB) * 0.5f;
//	};
//
//	// Set the AABB min and max equal to inputs
//	void GameObject::SetAABB(MyVector3& min, MyVector3& max) {
//		*this->minVector3AABB = min;
//		*this->maxVector3AABB = max;
//	};
//
//	// Extents
//	// Calculate the half-extents for each vector component by subtracting the min point from the max point and then halving the absolute value 
//	MyVector3 GameObject::Extents() {
//		return MyVector3(
//			abs(this->maxVector3AABB->x - this->minVector3AABB->x) * 0.5f,
//			abs(this->maxVector3AABB->y - this->minVector3AABB->y) * 0.5f,
//			abs(this->maxVector3AABB->z - this->minVector3AABB->z) * 0.5f);
//	};
//
//	// Return the corners of the AABB as an array of vectors, using min and max. In 2D we would return 4 corners, and in 3D we would return 8 corners. This is taking the XYZ of the min (bottom left) and the XYZ of the max (top right) and inferring the other 2 corners.
//	MyVector3* GameObject::Corners() {
//		MyVector3* cornerPtr_01 = new MyVector3(this->minVector3AABB->x, this->maxVector3AABB->y, this->minVector3AABB->z);
//		MyVector3* cornerPtr_03 = new MyVector3(this->maxVector3AABB->x, this->minVector3AABB->y, this->minVector3AABB->z);
//
//		MyVector3 corners[4];
//		corners[0] = *this->minVector3AABB;
//		//corners[1] = MyVector3(this->minVector3AABB->x, this->maxVector3AABB->y, this->minVector3AABB->z);
//		corners[1] = *cornerPtr_01;
//		corners[2] = *this->maxVector3AABB;
//		//corners[3] = MyVector3(this->maxVector3AABB->x, this->minVector3AABB->y, this->minVector3AABB->z);
//		corners[3] = *cornerPtr_03;
//
//		delete cornerPtr_01;
//		cornerPtr_01 = nullptr;
//
//		delete cornerPtr_03;
//		cornerPtr_03 = nullptr;
//
//		// return the address of the array which contains the vectors. Because an array is contiguous, we only need the address of the start of the array.
//		return corners;
//	};
//
//	// This function will calculate a bounding region that would encapsulate a set of points (corners) and fit an AABB around the points. In 2D this creates a rectangle of space. To do this we need to find the minimum and maximum components from all the points of the rectangle (the outline of the corners).
//	void GameObject::Fit(MyVector3* points[4]) {
//		// First, invalidate our current AABB min and max by setting min to the largest value possible, and by setting max to the smallest value possible.
//		minVector3AABB = new MyVector3(positive, positive, positive);
//		maxVector3AABB = new MyVector3(negative, negative, negative);
//
//		// Second, find the min and max of the passed-in points. I already know that any AABB this program uses will have a 4-element point array (it's a rectangle)
//		// Create a size_t type because it's a safe way to iterate through the array of points, which is a collection of pointers, being memory addresses
//		size_t numberOfPoints = sizeof(points) / sizeof(points[0]);
//
//
//		// For each vector pointer (memory address) in the array called points (the rectangular set of points passed-in for the bounding box), find the min and max.
//		// This will find the bounding box for this one sprite.
//		for (size_t point = 0; point < numberOfPoints; point++) {
//			MyVector3 min = min.Min(*this->minVector3AABB, *points[point]);
//			MyVector3 max = max.Max(*this->maxVector3AABB, *points[point]);
//
//			*this->minVector3AABB = min;
//			*this->maxVector3AABB = max;
//		};
//	};
//
//
//	/* We can test if a point is contained within an AABB by checking if the point is within the range of the min and max corners. If any component of the point is outside of these ranges then there is no overlap and we can return straight away, rather than checking any further component ranges */
//	bool GameObject::Overlaps(MyVector3& point) {
//		// Test for NOT being overlapped (faster)
//		return !(
//			point.x < this->minVector3AABB->x ||	// Is the point to the left of this sprite?
//			point.y < this->minVector3AABB->y ||	// Is the point below the bottom of this sprite?
//			point.x > this->maxVector3AABB->x ||	// Is the point to the right of this sprite?
//			point.y > this->maxVector3AABB->y);		// Is the point above the top of this sprite?
//	};
//
//	bool GameObject::Overlaps(GameObject& otherSprite) {
//		// Test for NOT being overlapped (faster)
//		return !(
//			this->maxVector3AABB->x < otherSprite.minVector3AABB->x ||	// Is my right side NOT touching their left side?
//			this->maxVector3AABB->y < otherSprite.minVector3AABB->y ||	// Is my top side NOT touching their bottom?
//			this->minVector3AABB->x > otherSprite.maxVector3AABB->x ||	// Is my left side NOT touching their right?
//			this->minVector3AABB->y > otherSprite.maxVector3AABB->y);	// Is my bottom side NOT touching their top?
//	};
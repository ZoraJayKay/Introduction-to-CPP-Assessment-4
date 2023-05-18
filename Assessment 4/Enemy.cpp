#include "Enemy.h"
#include <iostream>

// default constructor
Enemy::Enemy()
{		
	std::cout << "---Enemy constructor---" << std::endl;
	objType = Enemy_Type;
}

// default destructor
Enemy::~Enemy()
{
	
}


#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
protected:
	bool movingRight;

public:

	Enemy();
	
	~Enemy();

	void OnUpdate(float deltaTime) override;

	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
};


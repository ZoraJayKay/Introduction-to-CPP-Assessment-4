#pragma once

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raylib.h"

#include "GameObject.h"

class Weapon : public GameObject
{
protected:

public:
	//enum WeaponType;	
	int weaponSpeed = 0;
	int maxWeaponSpeed = 0;
	int acceleration = 0;
	int drag = 0;

	// file paths for new attacks to load textures
	const char* playerLaserAttackFileName = "x64/Images/laserBlue07.png";
	const char* enemyLaserAttackFileName = "x64/Images/laserRed07rotated.png";
	// other weapon 2 file name
	// other weapon 3 file name
	// DEBUG WEAPON NAME
	const char* debugFilePath = "x64/Images/spaceBuilding_009.png";

	// Sound file paths
	const char* laserSound_01FileName = "x64/Sounds/laserLarge_003.ogg";
	const char* laserSound_02FileName = "x64/Sounds/laserLarge_001.ogg";

	// Load sounds
	Sound laser_01 = LoadSound(laserSound_01FileName);
	Sound laser_02 = LoadSound(laserSound_02FileName);

	Weapon();
	Weapon(GameObject::weaponType weaponEquipped, GameObject::objectType shooter);
	~Weapon();

	void OnUpdate(float deltaTime, Controller& ctrlr) override;
};


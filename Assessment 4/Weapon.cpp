#include "Weapon.h"

// pass the constructor a type of weapon...
Weapon::Weapon(GameObject::WeaponType choice){
	
	// use an integer switch case to determine weapon attack speed
	switch (choice) {
	case 0:	// Bullet
		weaponSpeed = 400;
		break;
	case 1:	// name of weapon
		weaponSpeed = 500;
		break;
	case 2:	// name of weapon
		weaponSpeed = 600;
		break;
	case 3:	// name of weapon
		weaponSpeed = 700;
		break;
	}
};

Weapon::~Weapon() {

};
#include "Weapon.h"

// pass the constructor a type of weapon...
Weapon::Weapon(GameObject::WeaponType choice){
	
	// use an integer switch case to determine weapon attack speed
	switch (choice) {
	case 0:	// Bullet
		weaponSpeed = 100;
		break;
	case 1:	// name of weapon
		weaponSpeed = 200;
		break;
	case 2:	// name of weapon
		weaponSpeed = 300;
		break;
	case 3:	// name of weapon
		weaponSpeed = 400;
		break;
	}
};

Weapon::~Weapon() {

};
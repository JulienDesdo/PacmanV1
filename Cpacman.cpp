#include "pch.h"
#include "Cpacman.h"

Cpacman::Cpacman() : Entity(pos{ 15, 9 }, 2) { // on passe par là même pour pacman. //  : Entity(pos{ 15, 9 }, 2) // RENTRE SYSTEMATIQUEMENT DANS CE CONSTRUCTEUR
	life_nbr = 3;
	power = 0;
	score = 0; 
};

Cpacman::Cpacman(pos pos_intiale) : Entity(pos_intiale, 2) { // Appel : Cpacman pacman(pos{x,y}); // 
	entity_id = 2; 
	position = pos_intiale;

	life_nbr = 3;
	power = 1;
	score = 0;
}

Cpacman::~Cpacman() {}

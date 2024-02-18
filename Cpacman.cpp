#include "pch.h"
#include "Cpacman.h"

Cpacman::Cpacman() : Entity(pos{ 15, 9 }, 2) {
	life_nbr = 3;
	power = 0;
	score = 0; 
};

Cpacman::Cpacman(pos pos_intiale) : Entity(pos_intiale, 2) { // Appel : Cpacman pacman(pos{x,y});
	life_nbr = 3;
	power = 0;
	score = 0;
}

Cpacman::~Cpacman() {}

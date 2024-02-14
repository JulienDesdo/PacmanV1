#include "pch.h"
#include "Cpacman.h"

Cpacman::Cpacman() : Entity(pos{ 15, 9 }, 2) {
	life_nbr = 3;
	score = 0;
	pos_pacman = position;
	power = 0;
};

Cpacman::Cpacman(pos pos_intiale) : Entity(pos_intiale, 2) { // Appel : Cpacman pacman(pos{x,y});
	life_nbr = 3;
	score = 0;
	pos_pacman = position;
	power = 0;
}

void Cpacman::set_pos(pos pos_new) {
	pos_pacman = pos_new; 
}

Cpacman::~Cpacman() {}

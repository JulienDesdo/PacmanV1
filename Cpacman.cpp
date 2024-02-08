#include "pch.h"
#include "Cpacman.h"

Cpacman::Cpacman() {
	pos_pacman.x = 15; 
	pos_pacman.y = 9;

	vitesse = 1; 
}

Cpacman::Cpacman(pos pos_initiale) { // pour changer l'endroit où pop pacman. 
	pos_pacman.x = pos_initiale.x; 
	pos_pacman.y = pos_initiale.y; 

	vitesse = 1; 
}

Cpacman::~Cpacman() {

}



/*
void Cpacman::left() {
	pos pos_new; 
	pos_new.x = pos_pacman.x;
	pos_new.y = pos_pacman.y - 1;
	move(pos_new);
}

void Cpacman::right() {
	pos pos_new;
	pos_new.x = pos_pacman.x;
	pos_new.y = pos_pacman.y + 1;
	move(pos_new);
}

void Cpacman::down() {
	pos pos_new;
	pos_new.x = pos_pacman.x + 1;
	pos_new.y = pos_pacman.y;
	move(pos_new);
}

void Cpacman::up() {
	pos pos_new;
	pos_new.x = pos_pacman.x - 1;
	pos_new.y = pos_pacman.y;
	move(pos_new);
}

bool Cpacman::check_left() {
	pos pos_new;
	pos_new.x = pos_pacman.x;
	pos_new.y = pos_pacman.y - 1;
	return check_collision(pos_new);
}

bool Cpacman::check_right() {
	pos pos_new;
	pos_new.x = pos_pacman.x;
	pos_new.y = pos_pacman.y + 1;
	return check_collision(pos_new);
}

bool Cpacman::check_down() {
	pos pos_new;
	pos_new.x = pos_pacman.x + 1;
	pos_new.y = pos_pacman.y;
	return check_collision(pos_new);
}

bool Cpacman::check_up() {
	pos pos_new;
	pos_new.x = pos_pacman.x - 1;
	pos_new.y = pos_pacman.y;
	return check_collision(pos_new);
}
*/
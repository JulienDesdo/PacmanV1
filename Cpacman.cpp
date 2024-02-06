#include "pch.h"
#include "Cpacman.h"

Cpacman::Cpacman() {
	pos_pacman.x = 15; 
	pos_pacman.y = 9;

	graph.set_value(pos_pacman.x, pos_pacman.y, 2);
	// 2 est le chiffre faisant référence à pacman dans la matrice graph (grille du jeu) 
}

Cpacman::Cpacman(pos pos_pacman) { // pour changer l'endroit où pop pacman. 
	graph.set_value(pos_pacman.x, pos_pacman.y, 2); 
}

Cpacman::~Cpacman() {

}

bool check_collision(pos pos_new) {

	return true;
}

void move(pos pos_new) {

}
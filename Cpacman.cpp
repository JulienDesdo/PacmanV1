#include "pch.h"
#include "Cpacman.h"

Cpacman::Cpacman() {
	pos_pacman.x = 15; 
	pos_pacman.y = 9;

	this->graph.initializeGraph();
	this->graph.set_value(pos_pacman.x, pos_pacman.y, 2);
	// 2 est le chiffre faisant référence à pacman dans la matrice graph (grille du jeu) 
}

Cpacman::Cpacman(pos pos_initiale) { // pour changer l'endroit où pop pacman. 
	pos_pacman.x = pos_initiale.x; 
	pos_pacman.y = pos_initiale.y; 
	this->graph.initializeGraph();
	this->graph.set_value(pos_pacman.x, pos_pacman.y, 2); 
}

Cpacman::~Cpacman() {

}

bool Cpacman::check_collision(pos pos_new) {
	if (this->graph.get_value(pos_new.x, pos_new.y) == 1) return true; // si block alors collision
	else return false; 
}

void Cpacman::move(pos pos_new) {
	if (!check_collision(pos_new)) {
		this->graph.set_value(pos_new.x, pos_new.y, 2);
		this->graph.set_value(this->pos_pacman.x, this->pos_pacman.y, 0);  // Utilisez this->pos_pacman
		this->pos_pacman.x = pos_new.x;
		this->pos_pacman.y = pos_new.y;
	}
	// sinon, pas de changement car pacman ne peut pas aller dans cette direction. 
	// La matrice ne change donc pas jusqu'à nouvelle instruction. 
}

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
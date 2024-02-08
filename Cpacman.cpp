#include "pch.h"
#include "Cpacman.h"

Cpacman::Cpacman() {
	pos_pacman.x = 15; 
	pos_pacman.y = 9;

	
	//this->graph.initializeGraph(); 
	//graph.set_value(pos_pacman.x, pos_pacman.y, 2);
	// 2 est le chiffre faisant référence à pacman dans la matrice graph (grille du jeu) 

	vitesse = 1; 
}

Cpacman::Cpacman(pos pos_initiale) { // pour changer l'endroit où pop pacman. 
	pos_pacman.x = pos_initiale.x; 
	pos_pacman.y = pos_initiale.y; 
	//this->graph.initializeGraph();

	vitesse = 1; 
}

Cpacman::~Cpacman() {

}

bool Cpacman::check_collision(matrix graph, pos pos_new) {
	if (graph.get_value(pos_new.x, pos_new.y) == 1) return true; // si block alors collision
	else return false; 
}

void Cpacman::move(matrix graph, pos pos_new) {
	if (!check_collision(graph,pos_new)) {
		graph.set_value(pos_new.x, pos_new.y, 2);
		graph.set_value(this->pos_pacman.x, this->pos_pacman.y, 0);  // Utilisez this->pos_pacman
		this->pos_pacman.x = pos_new.x;
		this->pos_pacman.y = pos_new.y;
	}
	// sinon, pas de changement car pacman ne peut pas aller dans cette direction. 
	// La matrice ne change donc pas jusqu'à nouvelle instruction. 
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
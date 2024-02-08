#include "pch.h"
#include "Cphantom.h"


Cphantom::Cphantom() {
	pos_phantom.x = 7;
	pos_phantom.y = 9;

	this->graph.initializeGraph(); // PROBLEME DU GRAPHE QUI EST REINITIALISE
	this->graph.set_value(pos_phantom.x, pos_phantom.y, 3);
	// 3 est le chiffre faisant référence à une phantom dans la matrice graph (grille du jeu) 

	vitesse = 1;
}

Cphantom::Cphantom(pos pos_initiale) {
	pos_phantom.x = pos_initiale.x;
	pos_phantom.y = pos_initiale.y;

	this->graph.initializeGraph();
	this->graph.set_value(pos_phantom.x, pos_phantom.y, 3);

	vitesse = 1;
}

Cphantom::~Cphantom() {

}

bool Cphantom::check_collision(pos pos_new) {
	if (this->graph.get_value(pos_new.x, pos_new.y) == 1) return true; // si block alors collision
	else return false;
}

void Cphantom::move(pos pos_new) {
	if (!check_collision(pos_new)) {
		this->graph.set_value(pos_new.x, pos_new.y, 2);
		this->graph.set_value(this->pos_phantom.x, this->pos_phantom.y, 0);  // Utilisez this->pos_phantom
		this->pos_phantom.x = pos_new.x;
		this->pos_phantom.y = pos_new.y;
	}
	// sinon, pas de changement car pacman ne peut pas aller dans cette direction. 
	// La matrice ne change donc pas jusqu'à nouvelle instruction. 
}

void Cphantom::left() {
	pos pos_new;
	pos_new.x = pos_phantom.x;
	pos_new.y = pos_phantom.y - 1;
	move(pos_new);
}

void Cphantom::right() {
	pos pos_new;
	pos_new.x = pos_phantom.x;
	pos_new.y = pos_phantom.y + 1;
	move(pos_new);
}

void Cphantom::down() {
	pos pos_new;
	pos_new.x = pos_phantom.x + 1;
	pos_new.y = pos_phantom.y;
	move(pos_new);
}

void Cphantom::up() {
	pos pos_new;
	pos_new.x = pos_phantom.x - 1;
	pos_new.y = pos_phantom.y;
	move(pos_new);
}

bool Cphantom::check_left() {
	pos pos_new;
	pos_new.x = pos_phantom.x;
	pos_new.y = pos_phantom.y - 1;
	return check_collision(pos_new);
}

bool Cphantom::check_right() {
	pos pos_new;
	pos_new.x = pos_phantom.x;
	pos_new.y = pos_phantom.y + 1;
	return check_collision(pos_new);
}

bool Cphantom::check_down() {
	pos pos_new;
	pos_new.x = pos_phantom.x + 1;
	pos_new.y = pos_phantom.y;
	return check_collision(pos_new);
}

bool Cphantom::check_up() {
	pos pos_new;
	pos_new.x = pos_phantom.x - 1;
	pos_new.y = pos_phantom.y;
	return check_collision(pos_new);
}
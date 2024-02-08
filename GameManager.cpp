#include "pch.h"
#include "GameManager.h"


GameManager::GameManager() { 
	graph.initializeGraph(); 
	Cpacman pacman;
	graph.set_value(pacman.pos_pacman.x, pacman.pos_pacman.y, 2);
	// 2 est le chiffre faisant référence à pacman dans la matrice graph (grille du jeu) 
	
}

GameManager::~GameManager() {
	
}

bool GameManager::check_collision(pos pos_new) {
	if (graph.get_value(pos_new.x, pos_new.y) == 1) return true; // si block alors collision 
	else return false;
}

void GameManager::move(pos pos_new) {
	if (!check_collision(pos_new)) {
		graph.set_value(pos_new.x, pos_new.y, 2);
		graph.set_value(pacman.pos_pacman.x, pacman.pos_pacman.y, 0);  
		pacman.pos_pacman.x = pos_new.x;
		pacman.pos_pacman.y = pos_new.y;
	}
	// Sinon, pas de changement car pacman ne peut pas aller dans cette direction. 
	// La matrice ne change donc pas jusqu'à nouvelle instruction. 
}

void GameManager::left() {
	pos pos_new;
	pos_new.x = pacman.pos_pacman.x;
	pos_new.y = pacman.pos_pacman.y - 1;
	move(pos_new);
}

void GameManager::right() {
	pos pos_new;
	pos_new.x = pacman.pos_pacman.x;
	pos_new.y = pacman.pos_pacman.y + 1;
	move(pos_new);
}

void GameManager::down() {
	pos pos_new;
	pos_new.x = pacman.pos_pacman.x + 1;
	pos_new.y = pacman.pos_pacman.y;
	move(pos_new);
}

void GameManager::up() {
	pos pos_new;
	pos_new.x = pacman.pos_pacman.x - 1;
	pos_new.y = pacman.pos_pacman.y;
	move(pos_new);
}

bool GameManager::check_left() {
	pos pos_new;
	pos_new.x = pacman.pos_pacman.x;
	pos_new.y = pacman.pos_pacman.y - 1;
	return check_collision(pos_new);
}

bool GameManager::check_right() {
	pos pos_new;
	pos_new.x = pacman.pos_pacman.x;
	pos_new.y = pacman.pos_pacman.y + 1;
	return check_collision(pos_new);
}

bool GameManager::check_down() {
	pos pos_new;
	pos_new.x = pacman.pos_pacman.x + 1;
	pos_new.y = pacman.pos_pacman.y;
	return check_collision(pos_new);
}

bool GameManager::check_up() {
	pos pos_new;
	pos_new.x = pacman.pos_pacman.x - 1;
	pos_new.y = pacman.pos_pacman.y;
	return check_collision(pos_new);
}
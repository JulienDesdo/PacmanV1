#include "pch.h"
#include "GameManager.h"


GameManager::GameManager() { 
	graph.initializeGraph(); 
	/* 
	Entity pacman(pos{ 15,9 }, 2); // obligé de réecrire ça ici, et ce même si on l'a déjà écrit dans le prototype. 
	graph.set_value(pacman.position.x, pacman.position.y, pacman.entity_id);

	Entity Blinky(pos{ 7,9 }, 3);
	graph.set_value(Blinky.position.x, Blinky.position.y, Blinky.entity_id);
	*/ 

	Cphantom Blinky(pos{ 7,9 }); 
	graph.set_value(Blinky.position.x, Blinky.position.y, Blinky.entity_id); // mise à jour de la présence du phantom sur le graphe. 
	Cpacman pacman(pos{ 15,9 });
	graph.set_value(pacman.position.x, pacman.position.y, pacman.entity_id); // --- du pacman ----
	
}

GameManager::~GameManager() {
	
}

bool GameManager::check_collision(pos pos_new) {
	if (graph.get_value(pos_new.x, pos_new.y) == 1) return true; // si block alors collision 
	else return false;
}

void GameManager::move(pos pos_new, Entity entity) { // Entity est utilisé grâce à l'héritage de Entity pour les classes Cpacman et Cphantom notamment.
	if (!check_collision(pos_new)) {
		graph.set_value(pos_new.x, pos_new.y, entity.entity_id);
		graph.set_value(entity.position.x, entity.position.y, 0);  
		//entity.position.x = pos_new.x;
		//entity.position.y = pos_new.y;
		//entity.set_pos_entity(pos_new); 
		if (entity.entity_id == 2) {
			// pacman  
			pacman.set_pos_entity(pos_new);
			pacman.set_pos(pos_new);
		}
				
	}
	// Sinon, pas de changement car pacman ne peut pas aller dans cette direction.
	// La matrice ne change donc pas jusqu'à nouvelle instruction. 
}



void GameManager::left(Entity entity) {
	pos pos_new;
	pos_new.x = entity.position.x;
	pos_new.y = entity.position.y - 1;
	move(pos_new, entity);
}

void GameManager::right(Entity entity) {
	pos pos_new;
	pos_new.x = entity.position.x;
	pos_new.y = entity.position.y + 1;
	move(pos_new, entity);
}

void GameManager::down(Entity entity) {
	pos pos_new;
	pos_new.x = entity.position.x + 1;
	pos_new.y = entity.position.y;
	move(pos_new, entity);
}

void GameManager::up(Entity entity) {
	pos pos_new;
	pos_new.x = entity.position.x - 1;
	pos_new.y = entity.position.y;
	move(pos_new, entity);
}

bool GameManager::check_left(Entity entity) {
	pos pos_new;
	pos_new.x = entity.position.x;
	pos_new.y = entity.position.y - 1;
	return check_collision(pos_new);
}

bool GameManager::check_right(Entity entity) {
	pos pos_new;
	pos_new.x = entity.position.x;
	pos_new.y = entity.position.y + 1;
	return check_collision(pos_new);
}

bool GameManager::check_down(Entity entity) {
	pos pos_new;
	pos_new.x = entity.position.x + 1;
	pos_new.y = entity.position.y;
	return check_collision(pos_new);
}

bool GameManager::check_up(Entity entity) {
	pos pos_new;
	pos_new.x = entity.position.x - 1;
	pos_new.y = entity.position.y;
	return check_collision(pos_new);
}
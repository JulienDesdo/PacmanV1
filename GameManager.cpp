#include "pch.h"
#include "GameManager.h"


GameManager::GameManager() { 
	graph.initializeGraph(); 
	
	// PACMAN 
	Cpacman pacman(pos{ 15,9 });
	graph.set_value(pacman.position.x, pacman.position.y, pacman.entity_id); // --- du pacman ----

	// PHANTOM

	// Blinky
	Cphantom Blinky(pos{ 7,9 }); 
	Blinky.color_id = 1; // Rouge
	graph.set_value(Blinky.position.x, Blinky.position.y, Blinky.color_id + Blinky.entity_id); // mise à jour de la présence du phantom sur le graphe. 

	// Inky 
	Cphantom Inky(pos{ 9,8 });
	Inky.color_id = 2; // Cyan 
	graph.set_value(Inky.position.x, Inky.position.y, Inky.color_id + Inky.entity_id); // 2 + 3 = 5 ; 5 => phantom Cyan 


	// Pinky 
	Cphantom Pinky(pos{ 9,9 });
	Pinky.color_id = 3; // Rose 
	graph.set_value(Pinky.position.x, Pinky.position.y, Pinky.color_id + Pinky.entity_id); // 3+ 3 = 6 ; 6 => phantom Rose  

	// Clyde 
	Cphantom Clyde(pos{ 9,10 });
	Clyde.color_id = 4; // Orange 
	graph.set_value(Clyde.position.x, Clyde.position.y, Clyde.color_id + Clyde.entity_id); // 3+ 3 = 6 ; 6 => phantom Rose  
	
	// Color ID = 0 => valeur matrice = 3 => phantom grisée (inactif)  
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
		
		if (entity.entity_id == 2) {
			// pacman  
			pacman.set_pos_entity(pos_new);
			pacman.set_pos(pos_new);
		}
		else if(entity.entity_id == 3) { // Problème Identificateur ICI 
			Blinky.set_pos_entity(pos_new);
			Blinky.set_pos(pos_new);
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
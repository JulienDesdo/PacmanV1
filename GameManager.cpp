#include "pch.h"
#include "GameManager.h"


GameManager::GameManager() { 
	graph.initializeGraph(); 
	init_food(); 
	score = 0; 
	life = 3; 
	lvl = 0;
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

bool GameManager::check_basic_food(pos pos_new) {
	if (graph.get_value(pos_new.x, pos_new.y) == basic_food) return true; // basic food entier, = 8
	else return false;
}

bool GameManager::check_high_food(pos pos_new) {
	if (graph.get_value(pos_new.x, pos_new.y) == high_food) return true; // high food entier, = 9
	else return false;
}

void GameManager::reset_food() {
	if (nb_basic_food_restantes <= 0 && nb_high_food_restantes <= 0) {
		init_food();
		nb_basic_food_restantes = 146; 
		nb_high_food_restantes = 4; 
		lvl += 1; // le niveau permettra d'ajuster la difficulté du comportement des fantomes (vitesse, type d'algo), d'ajouter des powers spéciales
	}
}

void GameManager::move(pos pos_new, Entity entity) { // Entity est utilisé grâce à l'héritage de Entity pour les classes Cpacman et Cphantom notamment.
	if (!check_collision(pos_new)) { 
		
		if (entity.entity_id == 2) {
			
			// Vérification Nourriture pour pacman. 
			if (check_basic_food(pos_new)) { 
				graph.set_value(pos_new.x, pos_new.y, entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, 0);
				// pacman  
				pacman.set_pos_entity(pos_new);
				pacman.set_pos(pos_new);

				score += 10; 
				nb_basic_food_restantes -= 1;
			}
			else if (check_high_food(pos_new)) {
				graph.set_value(pos_new.x, pos_new.y, entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, 0);
				// pacman  
				pacman.set_pos_entity(pos_new);
				pacman.set_pos(pos_new);

				score += 50;
				nb_high_food_restantes -= 1;
				// fantome deviennent vulnérables, et pacman prédateur pendant 8 secondes. 
				// Changement de comportement des fantomes
			}
			else {
				graph.set_value(pos_new.x, pos_new.y, entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, 0);
				// pacman  
				pacman.set_pos_entity(pos_new);
				pacman.set_pos(pos_new);

			}

		}
		else if(entity.entity_id == 3) { // Problème Identificateur ICI 
			graph.set_value(pos_new.x, pos_new.y, entity.entity_id);
			graph.set_value(entity.position.x, entity.position.y, 0);
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

void GameManager::init_food() {
	// 8 : food = 10 pts 
	// 9 : food spéciale = 50 pts + pouvoirs
	//int basic_food = 8; 
	//int high_food = 9; 
	// 2ème ligne (indice 1) 
	graph.set_value(1, 1, basic_food);
	graph.set_value(1, 2, basic_food);
	graph.set_value(1, 3, basic_food);
	graph.set_value(1, 4, basic_food);
	graph.set_value(1, 5, basic_food);
	graph.set_value(1, 6, basic_food);
	graph.set_value(1, 7, basic_food);
	graph.set_value(1, 8, basic_food);

	graph.set_value(1, 10, basic_food);
	graph.set_value(1, 11, basic_food);
	graph.set_value(1, 12, basic_food);
	graph.set_value(1, 13, basic_food);
	graph.set_value(1, 14, basic_food);
	graph.set_value(1, 15, basic_food);
	graph.set_value(1, 16, basic_food);
	graph.set_value(1, 17, basic_food);
	
	// 3 ème ligne (indice 2) 
			graph.set_value(2, 1, high_food);
	graph.set_value(2, 4, basic_food);
	graph.set_value(2, 8, basic_food);
	graph.set_value(2, 10, basic_food);
	graph.set_value(2, 14, basic_food);
			graph.set_value(2, 17, high_food);

	// 4 ème ligne (indice 3)
	graph.set_value(3, 1, basic_food);
	graph.set_value(3, 2, basic_food);
	graph.set_value(3, 3, basic_food);
	graph.set_value(3, 4, basic_food);
	graph.set_value(3, 5, basic_food);
	graph.set_value(3, 6, basic_food);
	graph.set_value(3, 7, basic_food);
	graph.set_value(3, 8, basic_food);
	graph.set_value(3, 9, basic_food);
	graph.set_value(3, 10, basic_food);
	graph.set_value(3, 11, basic_food);
	graph.set_value(3, 12, basic_food);
	graph.set_value(3, 13, basic_food);
	graph.set_value(3, 14, basic_food);
	graph.set_value(3, 15, basic_food);
	graph.set_value(3, 16, basic_food);
	graph.set_value(3, 17, basic_food);

	// 5 ème ligne 
	graph.set_value(4, 1, basic_food);
	graph.set_value(4, 4, basic_food);
	graph.set_value(4, 6, basic_food);
	graph.set_value(4, 12, basic_food);
	graph.set_value(4, 14, basic_food);
	graph.set_value(4, 17, basic_food);

	// 6 ème ligne (indice 5)
	graph.set_value(5, 1, basic_food);
	graph.set_value(5, 2, basic_food);
	graph.set_value(5, 3, basic_food);
	graph.set_value(5, 4, basic_food);

	graph.set_value(5, 6, basic_food);
	graph.set_value(5, 7, basic_food);
	graph.set_value(5, 8, basic_food);

	graph.set_value(5, 10, basic_food);
	graph.set_value(5, 11, basic_food);
	graph.set_value(5, 12, basic_food);

	graph.set_value(5, 14, basic_food);
	graph.set_value(5, 15, basic_food);
	graph.set_value(5, 16, basic_food);
	graph.set_value(5, 17, basic_food);

	// 7 ème ligne (indice 6)
	graph.set_value(6, 4, basic_food);
	graph.set_value(6, 14, basic_food);

	// 8ème ligne (indice 7) 
	graph.set_value(7, 4, basic_food);
	graph.set_value(7, 14, basic_food);

	// 9ème ligne (indice 8) 
	graph.set_value(8, 4, basic_food);
	graph.set_value(8, 14, basic_food);

	// 10ème ligne (indice 9) 
	graph.set_value(9, 4, basic_food);
	graph.set_value(9, 14, basic_food);

	// 11ème ligne (indice 10) 
	graph.set_value(10, 4, basic_food);
	graph.set_value(10, 14, basic_food);

	// 12ème ligne (indice 11) 
	graph.set_value(11, 4, basic_food);
	graph.set_value(11, 14, basic_food);

	// 13ème ligne (indice 12) 
	graph.set_value(12, 4, basic_food);
	graph.set_value(12, 14, basic_food);

	// 14ème ligne (indice 13)
	graph.set_value(13, 1, basic_food);
	graph.set_value(13, 2, basic_food);
	graph.set_value(13, 3, basic_food);
	graph.set_value(13, 4, basic_food);
	graph.set_value(13, 5, basic_food);
	graph.set_value(13, 6, basic_food);
	graph.set_value(13, 7, basic_food);
	graph.set_value(13, 8, basic_food);

	graph.set_value(13, 10, basic_food);
	graph.set_value(13, 11, basic_food);
	graph.set_value(13, 12, basic_food);
	graph.set_value(13, 13, basic_food);
	graph.set_value(13, 14, basic_food);
	graph.set_value(13, 15, basic_food);
	graph.set_value(13, 16, basic_food);
	graph.set_value(13, 17, basic_food);

	// 15ème ligne (indice 14)
	graph.set_value(14, 1, basic_food);
	graph.set_value(14, 4, basic_food);
	graph.set_value(14, 8, basic_food);
	graph.set_value(14, 10, basic_food);
	graph.set_value(14, 14, basic_food);
	graph.set_value(14, 17, basic_food);

	// 16ème ligne (indice 15)
	graph.set_value(15, 1, high_food);
	graph.set_value(15, 2, basic_food);

	graph.set_value(15, 4, basic_food);
	graph.set_value(15, 5, basic_food);
	graph.set_value(15, 6, basic_food);
	graph.set_value(15, 7, basic_food);
	graph.set_value(15, 8, basic_food);
	graph.set_value(15, 9, basic_food);
	graph.set_value(15, 10, basic_food);
	graph.set_value(15, 11, basic_food);
	graph.set_value(15, 12, basic_food);
	graph.set_value(15, 13, basic_food);
	graph.set_value(15, 14, basic_food);

	graph.set_value(15, 16, basic_food);
	graph.set_value(15, 17, high_food);

	// 17ème ligne (indice 16)
	graph.set_value(16, 2, basic_food);
	graph.set_value(16, 4, basic_food);
	graph.set_value(16, 6, basic_food);
	graph.set_value(16, 12, basic_food);
	graph.set_value(16, 14, basic_food);
	graph.set_value(16, 16, basic_food);

	// 18ème ligne (indice 17)
	graph.set_value(17, 1, basic_food);
	graph.set_value(17, 2, basic_food);
	graph.set_value(17, 3, basic_food);
	graph.set_value(17, 4, basic_food);
	graph.set_value(17, 6, basic_food);
	graph.set_value(17, 7, basic_food);
	graph.set_value(17, 8, basic_food);
	graph.set_value(17, 10, basic_food);
	graph.set_value(17, 11, basic_food);
	graph.set_value(17, 12, basic_food);
	graph.set_value(17, 14, basic_food);
	graph.set_value(17, 15, basic_food);
	graph.set_value(17, 16, basic_food);
	graph.set_value(17, 17, basic_food);

	// 19ème ligne (indice 18)
	graph.set_value(18, 1, basic_food);
	graph.set_value(18, 8, basic_food);
	graph.set_value(18, 10, basic_food);
	graph.set_value(18, 17, basic_food);

	// 20ème ligne (indice 19)
	graph.set_value(19, 1, basic_food);
	graph.set_value(19, 2, basic_food);
	graph.set_value(19, 3, basic_food);
	graph.set_value(19, 4, basic_food);
	graph.set_value(19, 5, basic_food);
	graph.set_value(19, 6, basic_food);
	graph.set_value(19, 7, basic_food);
	graph.set_value(19, 8, basic_food);
	graph.set_value(19, 9, basic_food);
	graph.set_value(19, 10, basic_food);
	graph.set_value(19, 11, basic_food);
	graph.set_value(19, 12, basic_food);
	graph.set_value(19, 13, basic_food);
	graph.set_value(19, 14, basic_food);
	graph.set_value(19, 15, basic_food);
	graph.set_value(19, 16, basic_food);
	graph.set_value(19, 17, basic_food);
}
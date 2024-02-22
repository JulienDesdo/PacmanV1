#include "pch.h"
#include "GameManager.h"


GameManager::GameManager() { 
	graph.initializeGraph(); 
	init_food(); 
	lvl = 0;
	// PACMAN 
	Cpacman pacman(pos{ 15,9 });
	this->pacman = pacman; // C'était l'erreur fatidique ! LIGNE INDESPENSABLE !!!! 
	graph.set_value(pacman.position.x, pacman.position.y, pacman.entity_id); // --- du pacman ----
	// PHANTOM

	// Blinky
	Cphantom Blinky(pos{ 7,9 }, 4); 
	this->Blinky = Blinky;
	//Blinky.color_id = 1; // Rouge
	graph.set_value(Blinky.position.x, Blinky.position.y, Blinky.entity_id); // mise à jour de la présence du phantom sur le graphe. 

	// Inky 
	Cphantom Inky(pos{ 9,8 }, 5);
	this->Pinky = Pinky; 
	//Inky.color_id = 2; // Cyan 
	graph.set_value(Inky.position.x, Inky.position.y, Inky.entity_id); // 2 + 3 = 5 ; 5 => phantom Cyan 


	// Pinky 
	Cphantom Pinky(pos{ 9,9 }, 6);
	this->Pinky = Pinky; 
	//Pinky.color_id = 3; // Rose 
	graph.set_value(Pinky.position.x, Pinky.position.y, Pinky.entity_id); // 3+ 3 = 6 ; 6 => phantom Rose  

	// Clyde 
	Cphantom Clyde(pos{ 9,10 }, 7);
	this->Clyde = Clyde; // Eh oui ! Il faut évidemmment stocker "this" dans game ! 
	//Clyde.color_id = 4; // Orange 
	graph.set_value(Clyde.position.x, Clyde.position.y, Clyde.entity_id); // 3 + 4 = 7 ; 7 => phantom orange	
	// Color ID = 0 => valeur matrice = 3 => phantom grisée (inactif)  
}

void GameManager::Game_reset() { // si perte de vie alors game_reset s'enclenche 
	// Pacman perd une vie. 
	// Tout le monde revient à sa position initale 
	// Le score n'est pas décompté, le grille reste identique (pour les fruits...) 
	if (pacman.life_nbr > 0) {
		pacman.life_nbr -= 1;

		graph.set_value(Blinky.position.x, Blinky.position.y, 0);
		Blinky.position = pos{ 7,9 }; 
		graph.set_value(7, 9, Blinky.entity_id);


		graph.set_value(Inky.position.x, Inky.position.y, 0);
		Inky.position = pos{ 9,8 };
		graph.set_value(9, 8, Inky.entity_id);

		graph.set_value(Pinky.position.x, Pinky.position.y, 0);
		Pinky.position = pos{ 9,9 };
		graph.set_value(9, 9, Pinky.entity_id);
		

		graph.set_value(Clyde.position.x, Clyde.position.y, 0);
		Clyde.position = pos{ 9,10 };
		graph.set_value(9, 10, Clyde.entity_id);

		graph.set_value(pacman.position.x, pacman.position.y, 0);
		pacman.position = pos{ 15,9 };
		graph.set_value(15, 9, pacman.entity_id);
	}
	else {
		// Reset total. 
		graph.initializeGraph();
		init_food();
		lvl = 0;
		pacman.score = 0; 
		pacman.life_nbr = 3; 

		Blinky.position = pos{ 7,9 };
		graph.set_value(7, 9, Blinky.entity_id);
		Inky.position = pos{ 9,8 };
		graph.set_value(9, 8, Inky.entity_id);
		Pinky.position = pos{ 9,9 };
		graph.set_value(9, 9, Pinky.entity_id);
		Clyde.position = pos{ 9,10 };
		graph.set_value(9, 10, Clyde.entity_id);
		pacman.position = pos{ 15,9 };
		graph.set_value(15, 9, pacman.entity_id);
	}


}

void GameManager::Move_fantome() {
	if (state_fantome == 0) { // cas normal, les fantomes attaquent pacman. 
		if (!check_up(Blinky)) {
			up(Blinky);
		}
		else if (!check_left(Blinky)) {
			left(Blinky);
		}
		else if (!check_down(Blinky)) {
			down(Blinky);
		}

	}
	else { // cas fantomes deviennent bleu, sont vulnérables, changent de comportements. 

	}
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

void GameManager::move(pos pos_new, Entity entity) { // Entity est utilisé grâce à l'héritage de Entity pour les classes Cpacman et Cphantom notamment; on le place ici car il internvient dans les interactions du jeu
	if (!check_collision(pos_new)) {

		// CAS PACMAN 
		if (entity.entity_id == 2) {

			// Vérification Nourriture pour pacman. 
			if (check_basic_food(pos_new)) {
				// Mise à jour du graphe 
				graph.set_value(pos_new.x, pos_new.y, entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, 0);
				// Mise à jour de pacman 
				pacman.set_pos_entity(pos_new);
				// Mise à jour des variables
				pacman.score += 10;
				nb_basic_food_restantes -= 1;
			}
			else if (check_high_food(pos_new)) {
				// Mise à jour du graphe
				graph.set_value(pos_new.x, pos_new.y, entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, 0);
				// Mise à jour de pacman  
				pacman.set_pos_entity(pos_new);
				// Mise à jour des variables 
				pacman.score += 50;
				nb_high_food_restantes -= 1;
				// fantome deviennent vulnérables, et pacman prédateur pendant 8 secondes. 
					// Changement de comportement des fantomes ---------------------------------------------------------------------------
			}
			else {
				// Mise à jour du graphe 
				graph.set_value(pos_new.x, pos_new.y, entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, 0);
				// Mise à jour de pacman  
				pacman.set_pos_entity(pos_new);
			}

		}
		// CAS FANTOMES
		// PROBLEME PROBLEME PROBLEME PROBLEME PROBLEME PROBLEME PROBLEME PROBLEME PROBLEME PROBLEME PROBLEME PROBLEME PROBLEME PROBLEME PROBLEME 
		else if (entity.entity_id == 4 || entity.entity_id == 5 || entity.entity_id == 6 || entity.entity_id == 7) { // PROBLEME ICI, id vaut toujours la valeur de l'ID du constructuer Entity.
			int value = entity.entity_id + graph.get_value(pos_new.x, pos_new.y);
			switch (entity.entity_id + graph.get_value(pos_new.x, pos_new.y)) { 
			case 4: // cas blinky sur vide  4 = 4 + 0 
				graph.set_value(pos_new.x, pos_new.y, 0 + entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 4); // get_value vaut 4,14,24 selon la nourriture qui était présente. Avec la soustraction : 0 (vide), 10 (basic_food), 20 (high_food)
				Blinky.set_pos_entity(pos_new);
				break;
			case 5:
				graph.set_value(pos_new.x, pos_new.y, 0 + entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 5); // get_value vaut 4,14,24 selon la nourriture qui était présente
				Inky.set_pos_entity(pos_new);
				break;
			case 6:
				graph.set_value(pos_new.x, pos_new.y, 0 + entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 6); // get_value vaut 4,14,24 selon la nourriture qui était présente
				Pinky.set_pos_entity(pos_new);
				break;
			case 7:
				graph.set_value(pos_new.x, pos_new.y, 0 + entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 7); // get_value vaut 4,14,24 selon la nourriture qui était présente
				Clyde.set_pos_entity(pos_new);
				break;
			case 14: // cas où il y a de la BASIC_FOOD sur la case suivante. 
				graph.set_value(pos_new.x, pos_new.y, basic_food + entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 4); // get_value vaut 4,14,24 selon la nourriture qui était présente à la case précédente
				Blinky.set_pos_entity(pos_new); // mise à jour de la position de l'entité. 
				break;
			case 15:
				graph.set_value(pos_new.x, pos_new.y, basic_food + entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 5); // get_value vaut 4,14,24 selon la nourriture qui était présente
				Inky.set_pos_entity(pos_new);
				break;
			case 16:
				graph.set_value(pos_new.x, pos_new.y, basic_food + entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 6); // get_value vaut 4,14,24 selon la nourriture qui était présente
				Pinky.set_pos_entity(pos_new);
				break;
			case 17:
				graph.set_value(pos_new.x, pos_new.y, basic_food + entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 7); // get_value vaut 4,14,24 selon la nourriture qui était présente
				Clyde.set_pos_entity(pos_new);
				break;
			case 24: // cas où il y a de la HIGH_FOOD sur la case suivante. 
				graph.set_value(pos_new.x, pos_new.y, high_food + entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 4); // get_value vaut 4,14,24 selon la nourriture qui était présente. Avec la soustraction : 0 (vide), 10 (basic_food), 20 (high_food)
				Blinky.set_pos_entity(pos_new);
				break;
			case 25:
				graph.set_value(pos_new.x, pos_new.y, high_food + entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 5); // get_value vaut 4,14,24 selon la nourriture qui était présente
				Inky.set_pos_entity(pos_new);
				break;
			case 26:
				graph.set_value(pos_new.x, pos_new.y, high_food + entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 6); // get_value vaut 4,14,24 selon la nourriture qui était présente
				Pinky.set_pos_entity(pos_new);
				break;
			case 27:
				graph.set_value(pos_new.x, pos_new.y, high_food + entity.entity_id);
				graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 7); // get_value vaut 4,14,24 selon la nourriture qui était présente
				Clyde.set_pos_entity(pos_new);
				break;
			default:
				break;

			}
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
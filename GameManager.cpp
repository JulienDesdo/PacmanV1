#include "pch.h"
#include "GameManager.h"


GameManager::GameManager() { 
	graph.initializeGraph(); 
	init_food(); 
	lvl = 0;

	horloge = 0;
	horloge_ghost = 0;

	affich_tot = true;


	// PACMAN 
	Cpacman pacman(pos{ 15,9 });
	this->pacman = pacman; 
	graph.set_value(pacman.position.x, pacman.position.y, pacman.entity_id); 

	// PHANTOM
	// Blinky
	Cphantom Blinky(pos{ 7,9 }, 4); 
	this->Blinky = Blinky; // Rouge
	graph.set_value(Blinky.position.x, Blinky.position.y, Blinky.entity_id); // mise à jour de la présence du phantom sur le graphe. 

	// Inky 
	Cphantom Inky(pos{ 9,8 }, 5);
	this->Inky = Inky; // Cyan 
	graph.set_value(Inky.position.x, Inky.position.y, Inky.entity_id); 

	// Pinky 
	Cphantom Pinky(pos{ 9,9 }, 6);
	this->Pinky = Pinky; // Rose 
	graph.set_value(Pinky.position.x, Pinky.position.y, Pinky.entity_id); 

	// Clyde 
	Cphantom Clyde(pos{ 9,10 }, 7);
	this->Clyde = Clyde; // Orange 
	graph.set_value(Clyde.position.x, Clyde.position.y, Clyde.entity_id); 

}

GameManager::~GameManager() {
}

void GameManager::Game_reset() { 
	if (pacman.life_nbr > 0) {
		pacman.life_nbr -= 1;
		
		Respawn_Entity(pacman); 
		Respawn_Entity(Blinky);
		Respawn_Entity(Inky);
		Respawn_Entity(Pinky);
		Respawn_Entity(Clyde);

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

	this->horloge = 0; 
	this->horloge_ghost = 0; 
}

void GameManager::reset_food() {
	if (nb_basic_food_restantes <= 0 && nb_high_food_restantes <= 0) {
		init_food();
		nb_basic_food_restantes = 146; // 146 
		nb_high_food_restantes = 4; // 4 
		lvl += 1; // le niveau permettra d'ajuster la difficulté du comportement des fantomes (vitesse, type d'algo), d'ajouter des powers spéciales
		// Donc ajouter ici une fonction MAJ_game_level()
	}
}

void GameManager::maj_level(int level) {
	if (lvl == 1) { // Rendre un deuxième fantome actif

	}
	else if (lvl == 2) { // Rendre un troisieme fantome actif

	}
	else if (lvl == 3) { // Rendre quatrieme fantome actif

	}

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

bool GameManager::check_entity(Entity entity1, Entity entity2) {
	if (entity1.position.x - entity2.position.x == 0 && entity1.position.y - entity2.position.y == 0) { // dx = 0 & dy = 0 
		return true; 
	}
	
	else if (abs(entity1.position.x - entity2.position.x) == 0 && abs(entity1.position.y - entity2.position.y) == 1) { // dx = 0 & dy = 1
		return true;
	}
	else if (abs(entity1.position.x - entity2.position.x) == 1 && abs(entity1.position.y - entity2.position.y) == 0) { // dx = 1 & dy = 0 
		return true;
	}

	else {
		return false;
	}
}


// Fonction pour le comportement de poursuite
void GameManager::chasePacman() {
	// Calculer la direction vers laquelle Blinky doit se déplacer pour attraper Pacman
	int dx = pacman.position.x - Blinky.position.x;
	int dy = pacman.position.y - Blinky.position.y;

	// Choisissez la direction à privilégier pour attraper Pacman
	if (abs(dx) > abs(dy)) {
		// Priorité pour le déplacement horizontal
		if (dx > 0 && !check_down(Blinky)) {
			down(Blinky);
		}
		else if (dx < 0 && !check_up(Blinky)) {
			up(Blinky);
		}
		else if (!check_left(Blinky)) {
			left(Blinky);
		}
		else if (!check_right(Blinky)) {
			right(Blinky);
		}
	}
	else {
		// Priorité pour le déplacement vertical
		if (dy > 0 && !check_right(Blinky)) {
			right(Blinky);
		}
		else if (dy < 0 && !check_left(Blinky)) {
			left(Blinky);
		}
		else if (!check_up(Blinky)) {
			up(Blinky);
		}
		else if (!check_down(Blinky)) {
			down(Blinky);
		}
	}
}

// Fonction pour le comportement de fuite
void GameManager::fleeFromPacman() {
	// Calculer la direction pour fuir de Pacman (inverse de la logique de poursuite)
	int dx = Blinky.position.x - pacman.position.x;
	int dy = Blinky.position.y - pacman.position.y;

	// Choisissez la direction à privilégier pour fuir de Pacman
	if (abs(dx) > abs(dy)) {
		// Priorité pour le déplacement horizontal
		if (dx > 0 && !check_left(Blinky)) {
			left(Blinky);
		}
		else if (dx < 0 && !check_right(Blinky)) {
			right(Blinky);
		}
		else if (!check_up(Blinky)) {
			up(Blinky);
		}
		else if (!check_down(Blinky)) {
			down(Blinky);
		}
	}
	else {
		// Priorité pour le déplacement vertical
		if (dy > 0 && !check_up(Blinky)) {
			up(Blinky);
		}
		else if (dy < 0 && !check_down(Blinky)) {
			down(Blinky);
		}
		else if (!check_left(Blinky)) {
			left(Blinky);
		}
		else if (!check_right(Blinky)) {
			right(Blinky);
		}
	}
}

// Fonction pour un comportement aléatoire
void GameManager::randomMovement() {
	int random_direction = rand() % 4; // Générer un nombre aléatoire entre 0 et 3 pour choisir une direction
	switch (random_direction) {
	case 0:
		if (!check_up(Blinky)) {
			up(Blinky);
		}
		break;
	case 1:
		if (!check_down(Blinky)) {
			down(Blinky);
		}
		break;
	case 2:
		if (!check_left(Blinky)) {
			left(Blinky);
		}
		break;
	case 3:
		if (!check_right(Blinky)) {
			right(Blinky);
		}
		break;
	}
}

void GameManager::patrol() { // Ne marche pas..........
	// Définir une liste de points de patrouille prédéfinis
	std::vector<Point> patrolPoints = { {3, 4}, {15, 4}, {15, 4}, {3, 14} };

	// Calculer la distance à chaque point de patrouille
	std::vector<double> distances;
	for (const auto& point : patrolPoints) {
		distances.push_back(std::sqrt(std::pow(Blinky.position.x - point.x, 2) + std::pow(Blinky.position.y - point.y, 2)));
	}

	// Trouver le point de patrouille le plus proche
	double minDistance = DBL_MAX;

	int closestPointIndex = 0;
	for (int i = 0; i < distances.size(); ++i) {
		if (distances[i] < minDistance) {
			minDistance = distances[i];
			closestPointIndex = i;
		}
	}

	// Déplacer le fantôme vers le point de patrouille le plus proche
	Point targetPoint = patrolPoints[closestPointIndex];
	int dx = targetPoint.x - Blinky.position.x;
	int dy = targetPoint.y - Blinky.position.y;

	// Choisissez la direction à privilégier pour se déplacer vers le point de patrouille
	if (std::abs(dx) > std::abs(dy)) {
		if (dx > 0 && !check_right(Blinky)) {
			right(Blinky);
		}
		else if (dx < 0 && !check_left(Blinky)) {
			left(Blinky);
		}
		else if (!check_down(Blinky)) {
			down(Blinky);
		}
		else if (!check_up(Blinky)) {
			up(Blinky);
		}
	}
	else {
		if (dy > 0 && !check_down(Blinky)) {
			down(Blinky);
		}
		else if (dy < 0 && !check_up(Blinky)) {
			up(Blinky);
		}
		else if (!check_right(Blinky)) {
			right(Blinky);
		}
		else if (!check_left(Blinky)) {
			left(Blinky);
		}
	}
}

void GameManager::Move_fantome() {
	if (state_fantome == 0) {
		// Cas normal, les fantômes attaquent Pacman
		//chasePacman();
		chasePacman();
	}
	else if (state_fantome == 1) {
		// Cas où les fantômes deviennent bleus, sont vulnérables, comportement de fuite
		fleeFromPacman();
	}
	else {
		// Cas où les fantômes sont dans un état aléatoire
		randomMovement();
	}

}

void GameManager::Respawn_Entity(Entity entity) {
	
	if (entity.entity_id == 2) { // Pacman 
		graph.set_value(pacman.position.x, pacman.position.y, graph.get_value(pacman.position.x, pacman.position.y) - 2);
		//graph.set_value(pacman.position.x, pacman.position.y, 0);
		pacman.position = pos{ 15,9 };
		graph.set_value(pacman.position.x, pacman.position.y, pacman.entity_id);
	}
	else if (entity.entity_id == 4) { // Blinky 
		
		graph.set_value(Blinky.position.x, Blinky.position.y, graph.get_value(Blinky.position.x, Blinky.position.y) - 4);
		//graph.set_value(Blinky.position.x, Blinky.position.y, 0);
		Blinky.position = pos{ 7,9 };
		graph.set_value(Blinky.position.x, Blinky.position.y, Blinky.entity_id);
	}
	else if (entity.entity_id == 5) { // Inky 
		graph.set_value(Inky.position.x, Inky.position.y, graph.get_value(Inky.position.x, Inky.position.y) - 5);
		Inky.position = pos{ 9,8 };
		graph.set_value(Inky.position.x, Inky.position.y, Inky.entity_id);
	}
	else if (entity.entity_id == 6) { // Pinky
		graph.set_value(Pinky.position.x, Pinky.position.y, graph.get_value(Pinky.position.x, Pinky.position.y) - 6);
		Pinky.position = pos{ 9,9 };
		graph.set_value(Pinky.position.x, Pinky.position.y, Pinky.entity_id);
	}
	else if (entity.entity_id == 7) { // Clyde
		graph.set_value(Clyde.position.x, Clyde.position.y, graph.get_value(Clyde.position.x, Clyde.position.y) - 7);
		Clyde.position = pos{ 9,10 };
		graph.set_value(Clyde.position.x, Clyde.position.y, Clyde.entity_id);
	}
}

void GameManager::move(pos pos_new, Entity entity) { // Entity est utilisé grâce à l'héritage de Entity pour les classes Cpacman et Cphantom notamment; on le place ici car il internvient dans les interactions du jeu
	if (!check_collision(pos_new)) {

		// CAS PACMAN 

		if (entity.entity_id == 2) {

			if (pos_new.x == 9 && pos_new.y == 18) { // !! ATTENTION les phantomes sont aussi concernés et n'ont pas de dir, donc implementer dir + faire passer classe.
				// move pacman to 9,0 sans changement de dir
				// Mise à jour du graphe 
				this->graph.set_value(9, 0, entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, 0);
				// Mise à jour de pacman 
				this->pacman.set_pos_entity(pos{ 9,0 });
			}
			else if (pos_new.x == 9 && pos_new.y == 0) {
				// move pacman to 9,18 avec changement de dir

				// Mise à jour du graphe 
				this->graph.set_value(9, 18, entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, 0);
				// Mise à jour de pacman 
				this->pacman.set_pos_entity(pos{9,18});
				
			}
			else if ((check_entity(pacman, Blinky) || check_entity(pacman, Inky) || check_entity(pacman, Pinky) || check_entity(pacman, Clyde)) && state_fantome == 0) {
				Game_reset();
			}
			else if (check_basic_food(pos_new)) {
				// Mise à jour du graphe 
				this->graph.set_value(pos_new.x, pos_new.y, entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, 0);
				// Mise à jour de pacman 
				this->pacman.set_pos_entity(pos_new);
				// Mise à jour des variables
				pacman.score += 10;
				nb_basic_food_restantes -= 1;
			}
			else if (check_high_food(pos_new)) {
				// Mise à jour du graphe
				this->graph.set_value(pos_new.x, pos_new.y, entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, 0);
				// Mise à jour de pacman  
				this->pacman.set_pos_entity(pos_new);
				// Mise à jour des variables 
				pacman.score += 50;
				nb_high_food_restantes -= 1;

				// fantome deviennent vulnérables, et pacman prédateur pendant 8 secondes : 
				this->state_fantome = 1; 
				this->nb_high_food_ingere += 1; // Nombre de high food ingéré simultanément. 
			}
			else {
				// Mise à jour du graphe 
				this->graph.set_value(pos_new.x, pos_new.y, entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, 0);
				// Mise à jour de pacman  
				this->pacman.set_pos_entity(pos_new);
			}

			// Cas où pacman rencontre un fantome en plus de la nourriture. (state_fantome == 1) 
			if (check_entity(Blinky, pacman) && state_fantome == 1) { // cas où pacman mange fantome 
				pacman.score += 200;
				Respawn_Entity(Blinky);
			}
			else if (check_entity(pacman, Inky) && state_fantome == 1) { // cas où pacman mange fantome 
				pacman.score += 200;
				Respawn_Entity(Inky);
			}
			else if (check_entity(pacman, Pinky) && state_fantome == 1) { // cas où pacman mange fantome 
				pacman.score += 200;
				Respawn_Entity(Pinky);
			}
			else if (check_entity(pacman, Clyde) && state_fantome == 1) { // cas où pacman mange fantome
				pacman.score += 200;
				Respawn_Entity(Clyde);
			}

		}

		


		// CAS FANTOMES

		else if (entity.entity_id == 4 || entity.entity_id == 5 || entity.entity_id == 6 || entity.entity_id == 7) { 
			//int value = entity.entity_id + graph.get_value(pos_new.x, pos_new.y);
			switch (entity.entity_id + graph.get_value(pos_new.x, pos_new.y)) { 
			case 4: // cas blinky sur vide  4 = 4 + 0 
				this->graph.set_value(pos_new.x, pos_new.y, 0 + entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 4); // get_value vaut 4,14,24 selon la nourriture qui était présente. Avec la soustraction : 0 (vide), 10 (basic_food), 20 (high_food)
				this->Blinky.set_pos_entity(pos_new);
				break;
			case 5:
				this->graph.set_value(pos_new.x, pos_new.y, 0 + entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 5); // get_value vaut 4,14,24 selon la nourriture qui était présente
				this->Inky.set_pos_entity(pos_new);
				break;
			case 6:
				this->graph.set_value(pos_new.x, pos_new.y, 0 + entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 6); // get_value vaut 4,14,24 selon la nourriture qui était présente
				this->Pinky.set_pos_entity(pos_new);
				break;
			case 7:
				this->graph.set_value(pos_new.x, pos_new.y, 0 + entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 7); // get_value vaut 4,14,24 selon la nourriture qui était présente
				this->Clyde.set_pos_entity(pos_new);
				break;
			case 14: // cas où il y a de la BASIC_FOOD sur la case suivante. 
				this->graph.set_value(pos_new.x, pos_new.y, basic_food + entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 4); // get_value vaut 4,14,24 selon la nourriture qui était présente à la case précédente
				this->Blinky.set_pos_entity(pos_new); // mise à jour de la position de l'entité. 
				break;
			case 15:
				this->graph.set_value(pos_new.x, pos_new.y, basic_food + entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 5); // get_value vaut 4,14,24 selon la nourriture qui était présente
				this->Inky.set_pos_entity(pos_new);
				break;
			case 16:
				this->graph.set_value(pos_new.x, pos_new.y, basic_food + entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 6); // get_value vaut 4,14,24 selon la nourriture qui était présente
				this->Pinky.set_pos_entity(pos_new);
				break;
			case 17:
				this->graph.set_value(pos_new.x, pos_new.y, basic_food + entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 7); // get_value vaut 4,14,24 selon la nourriture qui était présente
				this->Clyde.set_pos_entity(pos_new);
				break;
			case 24: // cas où il y a de la HIGH_FOOD sur la case suivante. 
				this->graph.set_value(pos_new.x, pos_new.y, high_food + entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 4); // get_value vaut 4,14,24 selon la nourriture qui était présente. Avec la soustraction : 0 (vide), 10 (basic_food), 20 (high_food)
				this->Blinky.set_pos_entity(pos_new);
				break;
			case 25:
				this->graph.set_value(pos_new.x, pos_new.y, high_food + entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 5); // get_value vaut 4,14,24 selon la nourriture qui était présente
				this->Inky.set_pos_entity(pos_new);
				break;
			case 26:
				this->graph.set_value(pos_new.x, pos_new.y, high_food + entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 6); // get_value vaut 4,14,24 selon la nourriture qui était présente
				this->Pinky.set_pos_entity(pos_new);
				break;
			case 27:
				this->graph.set_value(pos_new.x, pos_new.y, high_food + entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 7); // get_value vaut 4,14,24 selon la nourriture qui était présente
				this->Clyde.set_pos_entity(pos_new);
				break;
			default:
				break;

			}
		}
	}
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

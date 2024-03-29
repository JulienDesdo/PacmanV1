#include "pch.h"
#include "GameManager.h"


GameManager::GameManager() { 
	graph.initializeGraph(); 
	init_food(); 
	lvl = 0;

	horloge = 0;
	horloge_ghost = 0;
	horloge_score_ghost = 0; 
	
	clock_prison_Blinky = 0;
	clock_prison_Inky = 0;
	clock_prison_Pinky = 0;
	clock_prison_Clyde = 0;

	affich_tot = true;
	vitesse = vitesse_initiale; 

	// PACMAN 
	Cpacman pacman(pos{ 15,9 });
	this->pacman = pacman; 
	graph.set_value(pacman.position.x, pacman.position.y, pacman.entity_id); 

	// PHANTOM
	// Blinky
	Cphantom Blinky(pos{ 7,9 }, 4); 
	this->Blinky = Blinky; // Rouge
	graph.set_value(Blinky.position.x, Blinky.position.y, Blinky.entity_id); // mise � jour de la pr�sence du phantom sur le graphe. 
	this->Blinky.inactif = false; 

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

	
	maj_level(); // ------------------------------------------------------------ TEST ----------------------------------------------
	Respawn_Entity(Inky);
	maj_level(); // ------------------------------------------------------------ TEST ----------------------------------------------
	Respawn_Entity(Pinky);
	maj_level(); // ------------------------------------------------------------ TEST ----------------------------------------------
	Respawn_Entity(Clyde);
	
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
		vitesse = vitesse_initiale;

		Blinky.position = pos{ 7,9 };
		graph.set_value(7, 9, Blinky.entity_id);
		this->Blinky.inactif = false;
		Inky.position = pos{ 9,8 };
		graph.set_value(9, 8, Inky.entity_id);
		this->Inky.inactif = true;
		Pinky.position = pos{ 9,9 };
		graph.set_value(9, 9, Pinky.entity_id);
		this->Pinky.inactif = true;
		Clyde.position = pos{ 9,10 };
		graph.set_value(9, 10, Clyde.entity_id);
		this->Clyde.inactif = true;
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
		maj_level();
	}
}

void GameManager::actu_nourriture_restante() { // + securit� valeurs n�gatives d�es aux valeurs de collisions. (mis ici pour �viter un trop grand ralentissement). 
	count_low_food = 0; 
	count_high_food = 0; 
	for (int i = 0; i <= 20; i++) {
		for (int j = 0; j <= 18; j++) {
			if (graph.get_value(i, j) >= 10 && graph.get_value(i, j) < 20) {
				count_low_food += 1;
			}
			else if (graph.get_value(i, j) >= 20) {
				count_high_food += 1; 
			}
		}
	}
	nb_basic_food_restantes = count_low_food; 
	nb_high_food_restantes = count_high_food; 
}

void GameManager::secure() {
	for (int i = 0; i <= 20; i++) {
		for (int j = 0; j <= 18; j++) {
			if (graph.get_value(i, j) < 0) {
				graph.set_value(i, j, 0);
			}
			if ((i == 9 && (j == 0 || j == 18)) && graph.get_value(i,j) != 0) {
				graph.set_value(i, j, 0);
			}
		}
	}
}

void GameManager::maj_level() {
	lvl += 1;
	// Eventuellemnt, introduire changement de comportement d'un niveau � l'autre. 
	if (lvl == 1) { // Rendre un deuxi�me fantome actif
		this->Inky.inactif = false;
		vitesse = 200; // Augmentation de la vitesse du jeu
		Respawn_Entity(Inky);
	}
	else if (lvl == 2) { // Rendre un troisieme fantome actif
		this->Pinky.inactif = false;
		vitesse = 150; // Augmentation de la vitesse du jeu
		Respawn_Entity(Pinky);
	}
	else if (lvl == 3) { // Rendre quatrieme fantome actif
		this->Clyde.inactif = false;
		Respawn_Entity(Clyde);
	}
	else if (lvl == 4) {
		// prevoir boite de dialogue "FIN DU JEU" : vous pouvez CONTINUEZ INDEFINIMENT ou RECOMMENCER
	}
}

void GameManager::check_level() { 
	// Eventuellemnt, introduire changement de comportement d'un niveau � l'autre. 
	if (lvl == 1) { // Rendre un deuxi�me fantome actif
		this->Inky.inactif = false;
		vitesse = 200; // Augmentation de la vitesse du jeu
		Respawn_Entity(Inky);
	}
	else if (lvl == 2) { // Rendre un troisieme fantome actif
		this->Pinky.inactif = false;
		vitesse = 150; // Augmentation de la vitesse du jeu
		Respawn_Entity(Pinky);

		this->Inky.inactif = false;
		Respawn_Entity(Inky);
	}
	else if (lvl == 3) { // Rendre quatrieme fantome actif
		this->Clyde.inactif = false;
		Respawn_Entity(Clyde);

		this->Pinky.inactif = false;
		vitesse = 150; // Augmentation de la vitesse du jeu
		Respawn_Entity(Pinky);

		this->Inky.inactif = false;
		vitesse = 200; // Augmentation de la vitesse du jeu
		Respawn_Entity(Inky);
	}
	else if (lvl == 4) {
		// prevoir boite de dialogue "FIN DU JEU" : vous pouvez CONTINUEZ INDEFINIMENT ou RECOMMENCER
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

void GameManager::Move_fantome() {
	if (state_fantome == 0) {
		// Cas normal, les fant�mes attaquent Pacman
		
		if (!Blinky.inactif) chasePacman(Blinky);
		if (!Pinky.inactif) randomMovement(Pinky);
		if (!Inky.inactif) patrol(Inky);
		if (!Clyde.inactif) randomMovement(Clyde);
	}
	else if (state_fantome == 1) {
		// Cas o� les fant�mes deviennent bleus, sont vuln�rables, comportement de fuite
		if (!Blinky.inactif) fleeFromPacman(Blinky);
		if (!Pinky.inactif) chasePacman(Pinky); // il est idiot 
		if (!Inky.inactif) fleeFromPacman(Inky);
		if (!Clyde.inactif) randomMovement(Clyde);
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
		if (Blinky.dead || Blinky.inactif) {
			graph.set_value(Blinky.position.x, Blinky.position.y, graph.get_value(Blinky.position.x, Blinky.position.y) - 4);
			Blinky.position = pos{ 7,2 };
			graph.set_value(Blinky.position.x, Blinky.position.y, Blinky.entity_id);
		}
		else {
			graph.set_value(Blinky.position.x, Blinky.position.y, graph.get_value(Blinky.position.x, Blinky.position.y) - 4);
			//graph.set_value(Blinky.position.x, Blinky.position.y, 0);
			Blinky.position = pos{ 7,9 };
			graph.set_value(Blinky.position.x, Blinky.position.y, Blinky.entity_id);
		}
	}
	else if (entity.entity_id == 5) { // Inky 
		if (Inky.inactif) { // soit inactif soit en prison (c'est � dire qu'il est mort) 
			graph.set_value(Inky.position.x, Inky.position.y, graph.get_value(Inky.position.x, Inky.position.y) - 5);
			Inky.position = pos{ 9,8 };
			graph.set_value(Inky.position.x, Inky.position.y, Inky.entity_id);
		}
		else if (Inky.dead) {
			graph.set_value(Inky.position.x, Inky.position.y, graph.get_value(Inky.position.x, Inky.position.y) - 5);
			Inky.position = pos{ 11,2 };
			graph.set_value(Inky.position.x, Inky.position.y, Inky.entity_id);
		}
		else {
			graph.set_value(Inky.position.x, Inky.position.y, graph.get_value(Inky.position.x, Inky.position.y) - 5);
			Inky.position = pos{ 11,6 };
			graph.set_value(Inky.position.x, Inky.position.y, Inky.entity_id);
		}
	}
	else if (entity.entity_id == 6) { // Pinky
		if (Pinky.inactif) {
			graph.set_value(Pinky.position.x, Pinky.position.y, graph.get_value(Pinky.position.x, Pinky.position.y) - 6);
			Pinky.position = pos{9,9};
			graph.set_value(Pinky.position.x, Pinky.position.y, Pinky.entity_id);
		}
		else if (Pinky.dead) {
			graph.set_value(Pinky.position.x, Pinky.position.y, graph.get_value(Pinky.position.x, Pinky.position.y) - 6);
			Pinky.position = pos{ 7,16 };
			graph.set_value(Pinky.position.x, Pinky.position.y, Pinky.entity_id);
		}
		else {
			graph.set_value(Pinky.position.x, Pinky.position.y, graph.get_value(Pinky.position.x, Pinky.position.y) - 6);
			Pinky.position = pos{ 9,2 };
			graph.set_value(Pinky.position.x, Pinky.position.y, Pinky.entity_id);
		}
	}
	else if (entity.entity_id == 7) { // Clyde
		if (Clyde.inactif) {
			graph.set_value(Clyde.position.x, Clyde.position.y, graph.get_value(Clyde.position.x, Clyde.position.y) - 7);
			Clyde.position = pos{ 9,10 };
			graph.set_value(Clyde.position.x, Clyde.position.y, Clyde.entity_id);
		}
		else if (Clyde.dead) {
			graph.set_value(Clyde.position.x, Clyde.position.y, graph.get_value(Clyde.position.x, Clyde.position.y) - 7);
			Clyde.position = pos{ 11,16 };
			graph.set_value(Clyde.position.x, Clyde.position.y, Clyde.entity_id);
		}
		else {
			graph.set_value(Clyde.position.x, Clyde.position.y, graph.get_value(Clyde.position.x, Clyde.position.y) - 7);
			Clyde.position = pos{ 9,12 };
			graph.set_value(Clyde.position.x, Clyde.position.y, Clyde.entity_id);
		}
	}
}

void GameManager::move(pos pos_new, Entity entity) { // Entity est utilis� gr�ce � l'h�ritage de Entity pour les classes Cpacman et Cphantom notamment; on le place ici car il internvient dans les interactions du jeu
	if (!check_collision(pos_new)) {

		// CAS PACMAN 

		if (entity.entity_id == 2) {

			if (pos_new.x == 9 && pos_new.y == 18) { 
				// Mise � jour du graphe 
				this->graph.set_value(9, 0, entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, 0);
				// Mise � jour de pacman 
				this->pacman.set_pos_entity(pos{ 9,0 });
			}
			else if (pos_new.x == 9 && pos_new.y == 0) {
				// Mise � jour du graphe 
				this->graph.set_value(9, 18, entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, 0);
				// Mise � jour de pacman 
				this->pacman.set_pos_entity(pos{9,18});
				
			}
			else if ((check_entity(pacman, Blinky) || check_entity(pacman, Inky) || check_entity(pacman, Pinky) || check_entity(pacman, Clyde)) && state_fantome == 0) {
				Game_reset();
			}
			else if (check_basic_food(pos_new)) {
				// Mise � jour du graphe 
				this->graph.set_value(pos_new.x, pos_new.y, entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, 0);
				// Mise � jour de pacman 
				this->pacman.set_pos_entity(pos_new);
				// Mise � jour des variables
				pacman.score += 10;
				//nb_basic_food_restantes -= 1; 
			}
			else if (check_high_food(pos_new)) {
				// Mise � jour du graphe
				this->graph.set_value(pos_new.x, pos_new.y, entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, 0);
				// Mise � jour de pacman  
				this->pacman.set_pos_entity(pos_new);
				// Mise � jour des variables 
				pacman.score += 50;
				//nb_high_food_restantes -= 1; 

				// fantome deviennent vuln�rables, et pacman pr�dateur pendant 8 secondes : 
				this->state_fantome = 1; 
				this->nb_high_food_ingere += 1; // Nombre de high food ing�r� simultan�ment. 
			}
			else {
				// Mise � jour du graphe 
				this->graph.set_value(pos_new.x, pos_new.y, entity.entity_id);
				this->graph.set_value(entity.position.x, entity.position.y, 0);
				// Mise � jour de pacman  
				this->pacman.set_pos_entity(pos_new);
			}

			// Cas o� pacman rencontre un fantome en plus de la nourriture. (state_fantome == 1) 
			if (check_entity(Blinky, pacman) && state_fantome == 1) { // cas o� pacman mange fantome 
				affich_gain = true; 
				cumul_gain += 200; 
				pos_collision_fantome = pacman.get_pos_entity();

				pacman.score += cumul_gain;
				Blinky.dead = true; // mort => fait un tour en prison pour 4 secondes. 
				Respawn_Entity(Blinky); // Attention respawn prison necessaire 
			}
			else if (check_entity(pacman, Inky) && state_fantome == 1) { // cas o� pacman mange fantome 
				affich_gain = true;
				cumul_gain += 200;
				pos_collision_fantome = pacman.get_pos_entity();

				pacman.score += cumul_gain;
				Inky.dead = true; 
				Respawn_Entity(Inky);
			}
			else if (check_entity(pacman, Pinky) && state_fantome == 1) { // cas o� pacman mange fantome 
				affich_gain = true;
				cumul_gain += 200;
				pos_collision_fantome = pacman.get_pos_entity();

				pacman.score += cumul_gain;
				Pinky.dead = true; 
				Respawn_Entity(Pinky);
			}
			else if (check_entity(pacman, Clyde) && state_fantome == 1) { // cas o� pacman mange fantome
				affich_gain = true;
				cumul_gain += 200;
				pos_collision_fantome = pacman.get_pos_entity();

				pacman.score += cumul_gain;
				Clyde.dead = true; 
				Respawn_Entity(Clyde);
			}

			secure();
			actu_nourriture_restante();
			
		}

		


		// CAS FANTOMES

		else if (entity.entity_id == 4 || entity.entity_id == 5 || entity.entity_id == 6 || entity.entity_id == 7) { 
			if (pos_new.x == 9 && pos_new.y == 18) {
				switch (entity.entity_id + graph.get_value(pos_new.x, pos_new.y)) {
					// Mise � jour du graphe 9 0 puis x,y,0
				case 4: // cas blinky sur vide  4 = 4 + 0 
					this->graph.set_value(9, 0, 0 + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, 0); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente. Avec la soustraction : 0 (vide), 10 (basic_food), 20 (high_food)
					this->Blinky.set_pos_entity(pos_new);
					break;
				case 5:
					this->graph.set_value(9, 0, 0 + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, 0); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente
					this->Inky.set_pos_entity(pos_new);
					break;
				case 6:
					this->graph.set_value(9, 0, 0 + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, 0); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente
					this->Pinky.set_pos_entity(pos_new);
					break;
				case 7:
					this->graph.set_value(9, 0, 0 + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, 0); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente
					this->Clyde.set_pos_entity(pos_new);
				default:
					break;
				}
			}
			else if (pos_new.x == 9 && pos_new.y == 0) {
				// Mise � jour du graphe 9 18
				switch (entity.entity_id + graph.get_value(pos_new.x, pos_new.y)) {
					// Mise � jour du graphe 9 0 puis x,y,0
				case 4: // cas blinky sur vide  4 = 4 + 0 
					this->graph.set_value(9, 18, 0 + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, 0); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente. Avec la soustraction : 0 (vide), 10 (basic_food), 20 (high_food)
					this->Blinky.set_pos_entity(pos_new);
					break;
				case 5:
					this->graph.set_value(9, 18, 0 + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, 0); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente
					this->Inky.set_pos_entity(pos_new);
					break;
				case 6:
					this->graph.set_value(9, 18, 0 + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, 0); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente
					this->Pinky.set_pos_entity(pos_new);
					break;
				case 7:
					this->graph.set_value(9, 18, 0 + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, 0); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente
					this->Clyde.set_pos_entity(pos_new);
				default:
					break;
				}

			}
			else {
				switch (entity.entity_id + graph.get_value(pos_new.x, pos_new.y)) {
				case 4: // cas blinky sur vide  4 = 4 + 0 
					this->graph.set_value(pos_new.x, pos_new.y, 0 + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 4); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente. Avec la soustraction : 0 (vide), 10 (basic_food), 20 (high_food)
					this->Blinky.set_pos_entity(pos_new);
					break;
				case 5:
					this->graph.set_value(pos_new.x, pos_new.y, 0 + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 5); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente
					this->Inky.set_pos_entity(pos_new);
					break;
				case 6:
					this->graph.set_value(pos_new.x, pos_new.y, 0 + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 6); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente
					this->Pinky.set_pos_entity(pos_new);
					break;
				case 7:
					this->graph.set_value(pos_new.x, pos_new.y, 0 + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 7); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente
					this->Clyde.set_pos_entity(pos_new);
					break;
				case 14: // cas o� il y a de la BASIC_FOOD sur la case suivante. 
					this->graph.set_value(pos_new.x, pos_new.y, basic_food + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 4); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente � la case pr�c�dente
					this->Blinky.set_pos_entity(pos_new); // mise � jour de la position de l'entit�. 
					break;
				case 15:
					this->graph.set_value(pos_new.x, pos_new.y, basic_food + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 5); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente
					this->Inky.set_pos_entity(pos_new);
					break;
				case 16:
					this->graph.set_value(pos_new.x, pos_new.y, basic_food + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 6); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente
					this->Pinky.set_pos_entity(pos_new);
					break;
				case 17:
					this->graph.set_value(pos_new.x, pos_new.y, basic_food + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 7); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente
					this->Clyde.set_pos_entity(pos_new);
					break;
				case 24: // cas o� il y a de la HIGH_FOOD sur la case suivante. 
					this->graph.set_value(pos_new.x, pos_new.y, high_food + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 4); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente. Avec la soustraction : 0 (vide), 10 (basic_food), 20 (high_food)
					this->Blinky.set_pos_entity(pos_new);
					break;
				case 25:
					this->graph.set_value(pos_new.x, pos_new.y, high_food + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 5); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente
					this->Inky.set_pos_entity(pos_new);
					break;
				case 26:
					this->graph.set_value(pos_new.x, pos_new.y, high_food + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 6); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente
					this->Pinky.set_pos_entity(pos_new);
					break;
				case 27:
					this->graph.set_value(pos_new.x, pos_new.y, high_food + entity.entity_id);
					this->graph.set_value(entity.position.x, entity.position.y, graph.get_value(entity.position.x, entity.position.y) - 7); // get_value vaut 4,14,24 selon la nourriture qui �tait pr�sente
					this->Clyde.set_pos_entity(pos_new);
					break;
				default:
					break;

				}
			}
		}
	}
}











// Fonction pour le comportement de poursuite
void GameManager::chasePacman(Entity entity) {
	// Calculer la direction vers laquelle Blinky doit se d�placer pour attraper Pacman
	int dx = pacman.position.x - entity.position.x;
	int dy = pacman.position.y - entity.position.y;

	// Choisissez la direction � privil�gier pour attraper Pacman
	if (abs(dx) > abs(dy)) {
		// Priorit� pour le d�placement horizontal
		if (dx > 0 && !check_down(entity)) {
			down(entity);
		}
		else if (dx < 0 && !check_up(entity)) {
			up(entity);
		}
		else if (!check_left(entity)) {
			left(entity);
		}
		else if (!check_right(entity)) {
			right(entity);
		}
	}
	else {
		// Priorit� pour le d�placement vertical
		if (dy > 0 && !check_right(entity)) {
			right(entity);
		}
		else if (dy < 0 && !check_left(entity)) {
			left(entity);
		}
		else if (!check_up(entity)) {
			up(entity);
		}
		else if (!check_down(entity)) {
			down(entity);
		}
	}
}

// Fonction pour le comportement de fuite
void GameManager::fleeFromPacman(Entity entity) {
	// Calculer la direction pour fuir de Pacman (inverse de la logique de poursuite)
	int dx = entity.position.x - pacman.position.x;
	int dy = entity.position.y - pacman.position.y;

	// Choisissez la direction � privil�gier pour fuir de Pacman
	if (abs(dx) > abs(dy)) {
		// Priorit� pour le d�placement horizontal
		if (dx > 0 && !check_left(entity)) {
			left(entity);
		}
		else if (dx < 0 && !check_right(entity)) {
			right(entity);
		}
		else if (!check_up(entity)) {
			up(entity);
		}
		else if (!check_down(entity)) {
			down(entity);
		}
	}
	else {
		// Priorit� pour le d�placement vertical
		if (dy > 0 && !check_up(entity)) {
			up(entity);
		}
		else if (dy < 0 && !check_down(entity)) {
			down(entity);
		}
		else if (!check_left(entity)) {
			left(entity);
		}
		else if (!check_right(entity)) {
			right(entity);
		}
	}
}

// Fonction pour un comportement al�atoire
void GameManager::randomMovement(Entity entity) {
	int random_direction = rand() % 4; // G�n�rer un nombre al�atoire entre 0 et 3 pour choisir une direction
	switch (random_direction) {
	case 0:
		if (!check_up(entity)) {
			up(entity);
		}
		break;
	case 1:
		if (!check_down(entity)) {
			down(entity);
		}
		break;
	case 2:
		if (!check_left(entity)) {
			left(entity);
		}
		break;
	case 3:
		if (!check_right(entity)) {
			right(entity);
		}
		break;
	}
}

void GameManager::patrol(Entity entity) { // Ne marche pas..........
	// D�finir une liste de points de patrouille pr�d�finis
	std::vector<Point> patrolPoints = { {3, 4}, {15, 4}, {15, 4}, {3, 14} };

	// Calculer la distance � chaque point de patrouille
	std::vector<double> distances;
	for (const auto& point : patrolPoints) {
		distances.push_back(std::sqrt(std::pow(entity.position.x - point.x, 2) + std::pow(entity.position.y - point.y, 2)));
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

	// D�placer le fant�me vers le point de patrouille le plus proche
	Point targetPoint = patrolPoints[closestPointIndex];
	int dx = targetPoint.x - entity.position.x;
	int dy = targetPoint.y - entity.position.y;

	// Choisissez la direction � privil�gier pour se d�placer vers le point de patrouille
	if (std::abs(dx) > std::abs(dy)) {
		if (dx > 0 && !check_right(entity)) {
			right(entity);
		}
		else if (dx < 0 && !check_left(entity)) {
			left(entity);
		}
		else if (!check_down(entity)) {
			down(entity);
		}
		else if (!check_up(entity)) {
			up(entity);
		}
	}
	else {
		if (dy > 0 && !check_down(entity)) {
			down(entity);
		}
		else if (dy < 0 && !check_up(entity)) {
			up(entity);
		}
		else if (!check_right(entity)) {
			right(entity);
		}
		else if (!check_left(entity)) {
			left(entity);
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
	// 9 : food sp�ciale = 50 pts + pouvoirs
	//int basic_food = 8; 
	//int high_food = 9; 

	// 2�me ligne (indice 1) 
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

	// 3 �me ligne (indice 2) 
	graph.set_value(2, 1, high_food);
	graph.set_value(2, 4, basic_food);
	graph.set_value(2, 8, basic_food);
	graph.set_value(2, 10, basic_food);
	graph.set_value(2, 14, basic_food);
	graph.set_value(2, 17, high_food);

	// 4 �me ligne (indice 3)
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

	// 5 �me ligne 
	graph.set_value(4, 1, basic_food);
	graph.set_value(4, 4, basic_food);
	graph.set_value(4, 6, basic_food);
	graph.set_value(4, 12, basic_food);
	graph.set_value(4, 14, basic_food);
	graph.set_value(4, 17, basic_food);

	// 6 �me ligne (indice 5)
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

	// 7 �me ligne (indice 6)
	graph.set_value(6, 4, basic_food);
	graph.set_value(6, 14, basic_food);

	// 8�me ligne (indice 7) 
	graph.set_value(7, 4, basic_food);
	graph.set_value(7, 14, basic_food);

	// 9�me ligne (indice 8) 
	graph.set_value(8, 4, basic_food);
	graph.set_value(8, 14, basic_food);

	// 10�me ligne (indice 9) 
	graph.set_value(9, 4, basic_food);
	graph.set_value(9, 14, basic_food);

	// 11�me ligne (indice 10) 
	graph.set_value(10, 4, basic_food);
	graph.set_value(10, 14, basic_food);

	// 12�me ligne (indice 11) 
	graph.set_value(11, 4, basic_food);
	graph.set_value(11, 14, basic_food);

	// 13�me ligne (indice 12) 
	graph.set_value(12, 4, basic_food);
	graph.set_value(12, 14, basic_food);

	// 14�me ligne (indice 13)
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

	// 15�me ligne (indice 14)
	graph.set_value(14, 1, basic_food);
	graph.set_value(14, 4, basic_food);
	graph.set_value(14, 8, basic_food);
	graph.set_value(14, 10, basic_food);
	graph.set_value(14, 14, basic_food);
	graph.set_value(14, 17, basic_food);

	// 16�me ligne (indice 15)
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

	// 17�me ligne (indice 16)
	graph.set_value(16, 2, basic_food);
	graph.set_value(16, 4, basic_food);
	graph.set_value(16, 6, basic_food);
	graph.set_value(16, 12, basic_food);
	graph.set_value(16, 14, basic_food);
	graph.set_value(16, 16, basic_food);

	// 18�me ligne (indice 17)
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

	// 19�me ligne (indice 18)
	graph.set_value(18, 1, basic_food);
	graph.set_value(18, 8, basic_food);
	graph.set_value(18, 10, basic_food);
	graph.set_value(18, 17, basic_food);

	// 20�me ligne (indice 19)
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

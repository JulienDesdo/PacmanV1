#pragma once
#include "matrix.h"
#include "Entity.h"
#include "pos.h"
#include "Cpacman.h"
#include "Cphantom.h"
#include <afxwin.h>

#include <vector>
#include <cmath> // Pour sqrt et pow
#include <limits>
#include <cfloat> // Pour DBL_MAX


struct Point {
	int x;
	int y;
};


class GameManager : public CWnd
{
public:
	// Game Grid
	matrix graph;
	
	// Entities
	Cpacman pacman;
	Cphantom Blinky; // fantome rouge;
	Cphantom Inky;  // fantome cyan;
	Cphantom Pinky; // fantome rose;
	Cphantom Clyde; // fantome orange;
	
	// Food score value
	int basic_food = 10;
	int high_food = 20;

	// Food intial number
	int nb_basic_food_restantes = 146; // Normalement 146 sur la map intiale
	int nb_high_food_restantes = 4; // Normalement 4 sur la map intiale 

	bool state_fantome = 0; // 0 = Phantome attack ; 1 = Phantome vulnérable et pacman attack. 
	int temps_vulnerable = 8000; // 8000 = 8 secondes
	int nb_high_food_ingere = 0; // Si pacman mange plus de 2 high_food pendant la durée state_fantome = 1 (utilisation dans PacmanV1View.cpp) 

	bool affich_tot = 0;
	
	bool admin = 1; // Admin Command to view more information.  

	int lvl; 
	GameManager(); // Game Init. 
	~GameManager(); 

	// "Encapsulation" : right,left,down,up > check_right,check_left,check_down,check_up && move > check_collision, init_food 
	// > check_high_food,check_basic_food, reset_food, check_Entity... 
	// Game Features. 
	bool GameManager::check_collision(pos pos_new);
	void GameManager::move(pos pos_new, Entity entity);

	void GameManager::right(Entity entity);
	void GameManager::left(Entity entity);
	void GameManager::down(Entity entity);
	void GameManager::up(Entity entity);

	bool GameManager::check_left(Entity entity);
	bool GameManager::check_right(Entity entity);
	bool GameManager::check_down(Entity entity);
	bool GameManager::check_up(Entity entity);


	void GameManager::init_food();
	bool GameManager::check_basic_food(pos pos_new);
	bool GameManager::check_high_food(pos pos_new);
	void GameManager::reset_food();

	void GameManager::Game_reset(); // Trigger : Collision with Entity. Content : life pacman control 

	bool GameManager::check_entity(Entity entity1, Entity entity2);
	void GameManager::Move_fantome(); 
 
	// Clocks 
	int horloge; // Horloge du jeu
	int horloge_ghost; // Horloge Ghost quand pacman a mangé nourriture
	int horloge_score_ghost; 
	int vitesse = vitesse_initiale; // Il s'agit de la vitesse du jeu. Variable qui permet de borner "horloge". 
	int vitesse_initiale = 240;

	// Game features
	void GameManager::Respawn_Entity(Entity entity);
	void GameManager::maj_level();
	void GameManager::check_level(); // fonction de vérification. 

	// Ghosts available behavour
	void GameManager::chasePacman(Entity entity);
	void GameManager::fleeFromPacman(Entity entity);
	void GameManager::randomMovement(Entity entity);
	void GameManager::patrol(Entity entity); // not working 

	// Patch : Bug Collision beetwen pacman and ghost. 
	void GameManager::actu_nourriture_restante(); // Another way to reset food (less optimal) 
	int count_low_food; 
	int count_high_food;
	void GameManager::secure(); // To prevent negative values to spawn in the graph due to collision bug. (Patch function) 

	// Pacman mange plusieurs fantome d'un coup. Evolution score ingestion : 200, 400, 600, 800... 
	bool affich_gain = false; 
	int cumul_gain = 0; 
	pos pos_collision_fantome = { 0,0 }; 

};


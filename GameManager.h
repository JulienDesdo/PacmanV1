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
	matrix graph;
	
	Cpacman pacman;
	Cphantom Blinky; // fantome rouge;
	Cphantom Inky;  // fantome cyan;
	Cphantom Pinky; // fantome rose;
	Cphantom Clyde; // fantome orange;
	
	int basic_food = 10;
	int high_food = 20;

	int nb_basic_food_restantes = 146; // Normalement 146 sur la map intiale
	int nb_high_food_restantes = 4; // Normalement 4 sur la map intiale 

	bool state_fantome = 0; // 0 = Phantome attack ; 1 = Phantome vulnérable et pacman attack. 
	int temps_vulnerable = 8000; // 8000 = 8 secondes
	int nb_high_food_ingere = 0;

	bool affich_tot = 0;
	
	bool admin = 1; // commande administrateur pour voir des données en plus. 

	int lvl; 
	GameManager();
	~GameManager(); 

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

	void GameManager::Game_reset(); // Une fois que Pacman est mort; perd une vie. 

	bool GameManager::check_entity(Entity entity1, Entity entity2);
	void GameManager::Move_fantome(); 
 
	//void GameManager::maj_state(bool&);  // probleme : met en pause tout le programme...On veut juste que la variable val true pendant huit secondes. 
	int horloge;
	int horloge_ghost;

	void GameManager::Respawn_Entity(Entity entity);
	void GameManager::maj_level();

	// Comportement fantomes.
	void GameManager::chasePacman(Entity entity);
	void GameManager::fleeFromPacman(Entity entity);
	void GameManager::randomMovement(Entity entity);
	void GameManager::patrol(Entity entity);

	void GameManager::actu_nourriture_restante();
	int count_low_food; 
	int count_high_food;

	void GameManager::secure(); // Pour eviter valeurs négatives. 

};


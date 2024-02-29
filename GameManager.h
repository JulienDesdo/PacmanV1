#pragma once
#include "matrix.h"
#include "Entity.h"
#include "pos.h"
#include "Cpacman.h"
#include "Cphantom.h"
#include <afxwin.h>


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
	bool affich_tot = 0; 

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
 
	void GameManager::maj_state(bool&);  // probleme : met en pause tout le programme...On veut juste que la variable val true pendant huit secondes. 
};


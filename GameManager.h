#pragma once
#include "matrix.h"
#include "Entity.h"
#include "pos.h"
#include "Cpacman.h"
#include "Cphantom.h"

class GameManager
{
public:
	matrix graph;
	Cpacman pacman;
	Cphantom Blinky; // fantome rouge;
	/*
	Entity Inky;  // fantome cyan;
	Entity Pinky; // fantome rose;
	Entity Clyde; // fantome orange;
	*/

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
};


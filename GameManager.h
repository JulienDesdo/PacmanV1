#pragma once
#include "matrix.h"
#include "Cpacman.h"
#include "pos.h"

class GameManager
{
public:
	matrix graph;
	Cpacman pacman;



	GameManager();
	~GameManager(); 

	bool GameManager::check_collision(pos pos_new);
	void GameManager::move(pos pos_new);

	void GameManager::right();
	void GameManager::left();
	void GameManager::down();
	void GameManager::up();

	bool GameManager::check_left();
	bool GameManager::check_right();
	bool GameManager::check_down();
	bool GameManager::check_up();

};


#pragma once
#include "matrix.h"
#include "Cpacman.h"

class GameManager
{
public:
	matrix * graph; 
	GameManager(); 
	~GameManager(); 
	Cpacman pacman; 
};


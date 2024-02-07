#pragma once
#include "matrix.h"
#include "pos.h"
class Cpacman
{
public : 
	matrix graph;
	pos pos_pacman; 
	// Note : plusieurs vitesses permettent d'éviter d'avoir des timers. Surtout quand 
	// pacman mange food : Pacman accelère et fantome ralentissent. 
public : 
	Cpacman(pos pos_initiale); 
	Cpacman(); 
	~Cpacman();  

	bool Cpacman::check_collision(pos pos_new); 
	void Cpacman::move(pos pos_new);
	
	void Cpacman::right(); 
	void Cpacman::left(); 
	void Cpacman::down(); 
	void Cpacman::up();
};



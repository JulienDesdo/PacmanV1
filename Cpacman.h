#pragma once
#include "matrix.h"
#include "pos.h"

class Cpacman
{
public : 
	pos pos_pacman; 
	float vitesse; 
	// Note : plusieurs vitesses permettent d'éviter d'avoir des timers. Surtout quand 
	// pacman mange food : Pacman accelère et fantome ralentissent. 
public : 
	Cpacman(pos pos_initiale); 
	Cpacman(); 
	~Cpacman();  

	bool Cpacman::check_collision(matrix graph, pos pos_new); 
	void Cpacman::move(matrix graph, pos pos_new);
	
	/*
	void Cpacman::right(); 
	void Cpacman::left(); 
	void Cpacman::down(); 
	void Cpacman::up();

	bool Cpacman::check_left();
	bool Cpacman::check_right();
	bool Cpacman::check_down();
	bool Cpacman::check_up();
	*/

};



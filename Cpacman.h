#pragma once
#include "matrix.h"
#include "pos.h"
class Cpacman
{
public : 
	matrix graph;
	pos pos_pacman; 
	// Note : plusieurs vitesses permettent d'�viter d'avoir des timers. Surtout quand 
	// pacman mange food : Pacman accel�re et fantome ralentissent. 
public : 
	Cpacman(pos pos_pacman); 
	Cpacman(); 
	~Cpacman();  

	bool check_collision(pos pos_new); 
	void move(pos pos_new);
	



};


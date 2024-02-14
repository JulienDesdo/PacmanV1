#ifndef PACMAN_H
#define PACMAN_H

#include "pos.h"
#include "Entity.h"

class Cpacman : public Entity 
{
public : 
	pos pos_pacman; 
	int life_nbr; 
	int score; 
	int power; // Pouvoir spéciale que pacman possède. 0 = Etat Normal
public : 
	Cpacman();
	Cpacman(pos pos_initiale);
	virtual ~Cpacman();

};

#endif // PACMAN_H


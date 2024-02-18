#ifndef PACMAN_H
#define PACMAN_H

#include "pos.h"
#include "Entity.h"

class Cpacman : public Entity 
{
public : 
	//pos pos_pacman; 
	int life_nbr;  
	int power; // Pouvoir sp�ciale que pacman poss�de. 0 = Etat Normal
	int score; 
public : 
	Cpacman();
	Cpacman(pos pos_initiale);
	virtual ~Cpacman();

	// void Cpacman::set_pos(pos pos_new); // seulement si pacman � une mise � jour de position sp�cifique. 
};  

#endif // PACMAN_H


#pragma once
#include "pos.h"
#include "Entity.h"

class Cphantom : public Entity 
{
public : 
	pos pos_phantom;
	// type? mode; // definit la mode chasse/fuite du fantom selon que pacman ait mang� un super-fruit ou non. 
	// type? strat�gie; // strat�gie issue de la th�orie des graphes. 

	int color_id; // 0 red, 1 cyan, 2 rose, 3 orange;

	Cphantom();
	Cphantom(pos pos_intiale);
	~Cphantom(); 
};


#pragma once
#include "pos.h"
#include "Entity.h"

class Cphantom : public Entity 
{
public : 
	pos pos_phantom;
	// type? mode; // definit la mode chasse/fuite du fantom selon que pacman ait mangé un super-fruit ou non. 
	// type? stratégie; // stratégie issue de la théorie des graphes. 

	int color_id; // 0 red, 1 cyan, 2 rose, 3 orange;

	Cphantom();
	Cphantom(pos pos_intiale);
	~Cphantom(); 
};


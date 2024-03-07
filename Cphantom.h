#pragma once
#include "pos.h"
#include "Entity.h"

class Cphantom : public Entity 
{
public : 
	//pos pos_phantom;
	// definit la mode chasse/fuite du fantom selon que pacman ait mang� un super-fruit ou non. 
	//bool state = 0; // 0 = predateur , 1 = victime toute d�sign�e.  PAS ICI car valable pour tous les fantomes en m�me temps => on le met dans manager
	// type? strat�gie; // strat�gie issue de la th�orie des graphes. 

	int color_id; // 0 red, 1 cyan, 2 rose, 3 orange;
	bool inactif = true;

	Cphantom();
	Cphantom(pos pos_intiale);
	Cphantom(pos pos_initiale, int ID);
	~Cphantom(); 


};


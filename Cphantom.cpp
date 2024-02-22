#include "pch.h"
#include "Cphantom.h"


Cphantom::Cphantom() : Entity(pos{ 7,9 }, 3) { // Le probleme vient de this (game). 
	//pos_phantom = position;
	color_id = 0;
}

Cphantom::Cphantom(pos pos_initiale) : Entity(pos_initiale, 3) {
	//pos_phantom = position;
	color_id = 0;
}

Cphantom::Cphantom(pos pos_initiale, int ID) : Entity(pos_initiale, ID) { 
	//pos_phantom = position;
	color_id = 0;
}


Cphantom::~Cphantom() {

}




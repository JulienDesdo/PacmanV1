#include "pch.h"
#include "Cphantom.h"


Cphantom::Cphantom() : Entity(pos{ 7,9 }, 4) { // �a vient d'ici... 
	//pos_phantom = position;
	color_id = 0;
}

Cphantom::Cphantom(pos pos_initiale) : Entity(pos_initiale, 3) {
	//pos_phantom = position;
	color_id = 0;
}

Cphantom::Cphantom(pos pos_initiale, int ID) : Entity(pos_initiale, ID) { // celui l� n'est curieusement pas appel�...
	//pos_phantom = position;
	color_id = 0;
}


Cphantom::~Cphantom() {

}




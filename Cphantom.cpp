#include "pch.h"
#include "Cphantom.h"


Cphantom::Cphantom() : Entity(pos{ 7,9 }, 3) {
	pos_phantom = position;
	color_id = 0;
}

Cphantom::Cphantom(pos pos_initiale) : Entity(pos_initiale, 3) {
	pos_phantom = position;
	color_id = 0;
}

Cphantom::~Cphantom() {

}


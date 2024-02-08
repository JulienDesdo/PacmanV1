#pragma once
#include "matrix.h"
#include "pos.h"

class Cphantom
{
public : 
	matrix graph; // probleme même graph. Comment avoir même graphe partout ? graph.pacman OU pacman.graph ? 
	pos pos_phantom;
	float vitesse;

	Cphantom();
	Cphantom(pos pos_initiale);
	~Cphantom(); 

	bool Cphantom::check_collision(pos pos_new);
	void Cphantom::move(pos pos_new);

	void Cphantom::right();
	void Cphantom::left();
	void Cphantom::down();
	void Cphantom::up();

	bool Cphantom::check_left();
	bool Cphantom::check_right();
	bool Cphantom::check_down();
	bool Cphantom::check_up();

	void Cphantom::move_auto1(); // graph theory 
};


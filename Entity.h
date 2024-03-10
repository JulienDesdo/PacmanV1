#ifndef ENTITY_H
#define ENTITY_H
#include "pos.h"

class Entity
{
public : 
	pos position; // Entity position
	float vitesse;  
	int dir; 
	// Note : plusieurs vitesses permettent d'éviter d'avoir des timers. Surtout quand 
	// pacman mange food : Pacman accelère et fantome ralentissent. 
	Entity(pos pos_initiale,int ID);
	Entity();
	virtual ~Entity();

	int entity_id; // 2 pacman, 4 Blinky... to identify entity when fonctions take "Entity entity" in argument. 
	void Entity::set_pos_entity(pos new_pos);
	pos Entity::get_pos_entity();
	
	double interpolation_value_X1 = 0; // store the "loading" value from A state to B state in order to get a continual transition. 
	double interpolation_value_X2 = 0; // X1,X2,Y1,Y2 for each edges of the rectangle associated to the entity. 
	double interpolation_value_Y1 = 0;
	double interpolation_value_Y2 = 0;

	int rectangle_edge_X1 = 0; 
	int rectangle_edge_X2 = 0;
	int rectangle_edge_Y1 = 0;
	int rectangle_edge_Y2 = 0;

};

#endif // ENTITY_H

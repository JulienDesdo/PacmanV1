#ifndef ENTITY_H
#define ENTITY_H
#include "pos.h"

class Entity
{
public : 
	pos position; // Entity position
	float vitesse;
	// Note : plusieurs vitesses permettent d'éviter d'avoir des timers. Surtout quand 
	// pacman mange food : Pacman accelère et fantome ralentissent. 
	Entity(pos pos_initiale,int ID);
	Entity();
	virtual ~Entity();

	int entity_id; // 0 block, 1 vide, 2 pacman, 3 phantom
	void Entity::set_pos_entity(pos new_pos);
};

#endif // ENTITY_H

#include "pch.h"
#include "Entity.h"

Entity::Entity() {
	position.x = 0;
	position.y = 0;
	vitesse = 1;
	entity_id = 0;
}

Entity::Entity(pos pos_initiale, int ID) { // pour changer l'endroit où pop pacman. 
	position.x = pos_initiale.x;
	position.y = pos_initiale.y;
	vitesse = 1;
	entity_id = ID; 
}

Entity::~Entity() {

}

void Entity::set_pos_entity(pos new_pos) {
	position = new_pos;

}
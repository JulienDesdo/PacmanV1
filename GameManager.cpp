#include "pch.h"
#include "GameManager.h"


GameManager::GameManager() {
	this->graph->initializeGraph(); 
	this->graph->set_value(pacman.pos_pacman.x, pacman.pos_pacman.y, 2);
}

GameManager::~GameManager() {

}


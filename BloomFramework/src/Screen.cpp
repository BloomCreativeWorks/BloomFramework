#include "Screen.h"
#include "Game.h"
bloom::Screen::Screen(Game *& gameInstance) : m_gameInstance(gameInstance) {
}

bloom::Screen::~Screen()
{
	for (auto& gameObj : m_gameObjects)
		gameObj.second->~GameObject();
}

void bloom::Screen::update(){
	double dt = m_gameInstance->timer.lap();
	for (auto& sys : m_systems)
		sys->update(dt);
	std::cout << "Delta Time: " << dt << "ms" << std::endl;
}

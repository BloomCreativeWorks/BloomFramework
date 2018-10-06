#include "Screen.h"

bloom::Screen::Screen(Game *& gameInstance) : m_gameInstance(gameInstance) {
}

//bloom::Screen::~Screen()
//{
//	for (auto& gameObj : m_gameObjects)
//		gameObj.second->~GameObject();
//}

void bloom::Screen::update(){
	for (auto& sys : m_systems)
		sys->update(m_gameInstance->timer.lap());
}

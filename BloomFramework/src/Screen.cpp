#include "Screen.h"
#include "Game.h"

namespace bloom {
	Screen::Screen(Game * gameInstance) : m_gameInstance(gameInstance) {}

	Screen::~Screen() {
		for (auto& gameObj : m_gameObjects)
			gameObj.second->~GameObject();
	}

	void Screen::update() {
		double dt = m_gameInstance->timer.lap();
		for (auto& sys : m_systems)
			sys->update(dt);
		std::cout << "Delta Time: " << dt << "ms" << std::endl;
	}
	void Screen::destroyGameObject(std::string tag) {
		m_gameObjects.erase(tag);
	}
}
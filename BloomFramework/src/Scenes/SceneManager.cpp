#include "Scenes\SceneManager.h"
#include "Scenes\Scene.h"
#include "Game.h"

namespace bloom {
	inline SceneManager::SceneManager(Game & gameInstance) : m_gameInstance(gameInstance) {}

	void SceneManager::update(double deltaTime) {
		if (m_currScene != nullptr)
			m_currScene->update(deltaTime);
		else
			std::cerr << "There is no currently active Scene" << std::endl;
	}

	void SceneManager::draw() {
		if (m_currScene != nullptr)
			m_currScene->draw();
	}
}

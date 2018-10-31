#include "Scenes\SceneManager.h"
#include "Scenes/Scene.h"

namespace bloom {
	inline SceneManager::SceneManager(Game & gameInstance) : m_gameInstance(gameInstance) {}
	void SceneManager::changeScene(Scene * newScene) {
		if (m_currScene != nullptr) m_currScene->unload();
		newScene->load();
		m_currScene = newScene;
	}
	void SceneManager::update() {
		if (m_currScene != nullptr) m_currScene->update();
		else std::cerr << "There is currently no active Scene" << std::endl;
	}
	void SceneManager::draw() {
		// Might not need this.
	}
}

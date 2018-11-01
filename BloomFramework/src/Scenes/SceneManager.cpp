#include "Scenes\SceneManager.h"
#include "Scenes\Scene.h"
#include "Game.h"

namespace bloom {
	inline SceneManager::SceneManager(Game & gameInstance) : m_gameInstance(gameInstance) {}
	void SceneManager::changeScene(std::shared_ptr<Scene> newScene) {
		if (m_currScene != nullptr) m_currScene->unload();
		newScene->load();
		m_currScene = newScene;
	}
	void SceneManager::update() {
		if (m_currScene != nullptr) m_currScene->update();
		else std::cerr << "There is currently no active Scene" << std::endl;
	}
	void SceneManager::draw() {
		if (m_currScene != nullptr) 
			SDL_RenderCopyEx(m_gameInstance.getRenderer(), m_currScene->getSceneTexture(), NULL, NULL, NULL, NULL, SDL_FLIP_NONE);
	}
}

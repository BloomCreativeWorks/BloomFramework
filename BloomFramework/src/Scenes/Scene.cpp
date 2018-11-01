#include "Scenes\Scene.h"
#include "Scenes\SceneManager.h"
#include "Game.h"

namespace bloom {
	Scene::Scene(SceneManager & sceneManager) : m_sceneManager(sceneManager), m_gameInstance(sceneManager.m_gameInstance) {
		m_sceneTexture = SDL_CreateTexture(m_gameInstance.getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			m_gameInstance.getScreenWidth(),
			m_gameInstance.getScreenHeight());

		SDL_SetTextureBlendMode(m_sceneTexture, SDL_BLENDMODE_BLEND);
	}
	void Scene::update() {
		SDL_SetRenderTarget(m_gameInstance.getRenderer(), m_sceneTexture);
		SDL_RenderClear(m_gameInstance.getRenderer());
		double dt = m_gameInstance.timer.lap();
		for (auto& sys : m_systems)
			sys->update(dt);
		std::cout << "Delta Time: " << dt << "ms" << std::endl;
	}
	SDL_Texture * Scene::getSceneTexture(){
		return m_sceneTexture;
	}
}


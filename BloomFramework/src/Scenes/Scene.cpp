#include "Scenes\Scene.h"
#include "Scenes\SceneManager.h"
#include "Game.h"

namespace bloom {
	Scene::Scene(SceneManager & sceneManager) :
		m_sceneManager(sceneManager),
		m_gameInstance(sceneManager.m_gameInstance),
		m_sceneRotateCenter(Coord().toSDLPoint(m_gameInstance.getRenderer()))
	{
		m_sceneTexture = SDL_CreateTexture(m_gameInstance.getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			m_gameInstance.getScreenWidth(),
			m_gameInstance.getScreenHeight());

		SDL_SetTextureBlendMode(m_sceneTexture, SDL_BLENDMODE_BLEND);
	}

	Scene::~Scene() {
		SDL_DestroyTexture(m_sceneTexture);
	}

	void Scene::update(double deltaTime) {
		SDL_SetRenderTarget(m_gameInstance.getRenderer(), m_sceneTexture);
		SDL_RenderClear(m_gameInstance.getRenderer());
		for (auto & sys : m_systems)
			if (sys->enabled)
				sys->update(deltaTime);
	}

	void Scene::draw() {
		SDL_RenderCopyEx(m_gameInstance.getRenderer(), m_sceneTexture, nullptr, nullptr, m_sceneRotateAngle, &m_sceneRotateCenter, SDL_FLIP_NONE);
	}

	void Scene::destroyGameObject(const std::string & tag) {
		m_gameObjects.erase(tag);
	}

	void Scene::destroyAllGameObjects() {
		m_gameObjects.clear();
	}

	void Scene::unregisterAllSystems() {
		m_systems.clear();
	}

	void Scene::setSceneRotation(double angle) {
		m_sceneRotateAngle = fmod(angle, 360.0);
	}

	void Scene::adjustSceneRotation(double adjustment) {
		m_sceneRotateAngle = fmod((m_sceneRotateAngle + adjustment), 360.0);
	}

	double Scene::getSceneRotation() {
		return m_sceneRotateAngle;
	}

	void Scene::setSceneRotationCenter(Coord center) {
		m_sceneRotateCenter = center.toSDLPoint(m_gameInstance.getRenderer());
	}

	void Scene::setSceneRotationCenter(SDL_Point center) {
		m_sceneRotateCenter = center;
	}
}


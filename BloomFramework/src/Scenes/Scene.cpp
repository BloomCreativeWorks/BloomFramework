#include "Scenes\Scene.h"
#include "Scenes/SceneManager.h"

namespace bloom {
	Scene::Scene(SceneManager & sceneManager) : m_sceneManager(sceneManager), m_gameInstance(sceneManager.m_gameInstance) {}
}


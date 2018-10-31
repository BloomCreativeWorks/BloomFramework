#include "Scenes\SceneManager.h"
#include "Scenes/Scene.h"

namespace bloom {
	void SceneManager::changeScene(Scene * newScene) {
		if (currScene != nullptr) currScene->unload();
		newScene->load();
		currScene = newScene;
	}
	void SceneManager::update() {
		if (currScene != nullptr) currScene->update();
	}
	void SceneManager::draw() {
		// Might not need this.
	}
}

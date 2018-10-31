#pragma once

#include "stdIncludes.h"
#include <stack>
#include "Scene.h"

namespace bloom {
	class Game;
	class Scene;
	class BLOOMFRAMEWORK_API SceneManager {
		friend Scene::Scene(SceneManager & sceneManager);
	public:
		SceneManager(Game& gameInstance);
		void changeScene(Scene * newScene);
		void update();
		void draw();

	private:
		Scene * m_currScene;
		Game & m_gameInstance;
	};
}
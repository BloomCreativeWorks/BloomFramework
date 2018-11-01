#pragma once

#include "stdIncludes.h"
#include "Scene.h"

namespace bloom {
	class Game; class Scene;

	class BLOOMFRAMEWORK_API SceneManager {
		friend Scene::Scene(SceneManager & sceneManager);

	public:
		SceneManager(Game& gameInstance);

		void changeScene(std::shared_ptr<Scene> newScene);
		void update();
		void draw();
		
		const SceneManager * thisPtr = this;

	private:
		std::shared_ptr<Scene> m_currScene;
		Game & m_gameInstance;
	};
}
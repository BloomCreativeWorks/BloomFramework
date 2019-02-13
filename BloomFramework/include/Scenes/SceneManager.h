#pragma once

#include "stdIncludes.h"
#include "Scene.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Game;

	class BLOOMFRAMEWORK_API SceneManager {
		friend Scene::Scene(SceneManager & sceneManager);

	public:
		SceneManager(Game& gameInstance);

		template<class Scn, typename = std::enable_if_t<std::is_base_of_v<Scene, Scn>>>
		void changeScene(std::shared_ptr<Scn> newScene);
		void update(double deltaTime);
		void draw();

		const SceneManager * thisPtr = this;

	private:
		std::shared_ptr<Scene> m_currScene;
		Game & m_gameInstance;
	};

	template<class Scn, typename>
	void SceneManager::changeScene(std::shared_ptr<Scn> newScene) {
		//static_assert(std::is_base_of_v<Scene, Scn>, "Type Scn passed in is not Scene based");

		newScene->load();
		m_currScene = newScene;
		
		if (!m_currScene->isLoaded())
			m_currScene->start();
	}
}
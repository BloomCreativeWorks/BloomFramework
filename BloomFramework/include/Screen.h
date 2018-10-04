#pragma once
#include "stdIncludes.h"
#include "Game.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Screen {
	public:
		Screen(Game& gameInstance);
		void handleInput();
		void render();

	private:
		// std::vector<GameObject> gameObjects; // GameObject not implemented yet.
		entt::DefaultRegistry registry;
		Game& _gameInstance;
	};
}
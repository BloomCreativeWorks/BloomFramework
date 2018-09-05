#pragma once

#include "stdIncludes.h"
#include <iostream>
#include <vector>
#include "ECS/EntityComponentSystem.h"

namespace BloomFramework {
	class ColliderComponent;
	class BLOOMFRAMEWORK_API Game {
	public:
		Game();
		~Game();

		void init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen);
		void handleEvents();
		void update();
		void render();
		void clean();
		bool running() { return isRunning; };

		void addTile(int id, int x, int y);

		SDL_Renderer * renderer = nullptr;
		SDL_Event event;
		std::vector<ColliderComponent*> colliders;
		Manager * manager;

	private:
		bool isRunning;
		SDL_Window * window = nullptr;
	};
}
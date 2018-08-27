#pragma once

#include "stdIncludes.h"
#include <iostream>
#include <vector>



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

		static SDL_Renderer * renderer;
		static SDL_Event event;
		static std::vector<ColliderComponent*> colliders;
	private:
		int counter = 0;
		bool isRunning;
		SDL_Window * window = nullptr;
	};
}
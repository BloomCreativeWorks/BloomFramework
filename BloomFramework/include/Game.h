#pragma once
#include "stdIncludes.h"
#include <iostream>
#include "SDL_mixer.h"

namespace BloomFramework {
	class Game {
	public:
		Game(int width, int height, int windowFlags, int rendererFlags);
		~Game();

		bool init(const char* title, int xpos, int ypos);
		void update();
		void render();
		void clean();
		void handleEvents();
		bool running();

		int screenWidth, screenHeight;
		int windowFlags, rendererFlags;
	protected:

		SDL_Renderer * renderer = nullptr;
		SDL_Event events;
		bool isRunning;
		SDL_Window * window = nullptr;
	};
}
#pragma once
#include "stdIncludes.h"
#include <iostream>
#include "SDL_mixer.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Game {
	public:
		Game(int width, int height, int windowFlags, int rendererFlags);
		~Game();

		bool init(const std::string & title, int xpos, int ypos);
		void update();
		void render();
		void destroy();
		void handleEvents();
		bool isRunning();

		int getScreenWidth();
		int getScreenHeight();

		int windowFlags, rendererFlags;

	protected:
		int _screenWidth, _screenHeight;
		SDL_Renderer * _renderer = nullptr;
		SDL_Event _events;
		bool _running;
		SDL_Window * _window = nullptr;
	};
}
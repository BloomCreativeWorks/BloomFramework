#pragma once
#include "stdIncludes.h"
#include <iostream>

namespace bloom {
	class BLOOMFRAMEWORK_API Game {
	public:
		Game(int width, int height, int _windowFlags, int _rendererFlags);
		~Game();

		bool init(std::string const& title, int xpos, int ypos);
		void update();
		void render();
		void destroy();
		void handleEvents();
		bool isRunning();

		int getScreenWidth();
		int getScreenHeight();

	protected:
		int _screenWidth, _screenHeight;
		int _windowFlags, _rendererFlags;
		SDL_Renderer * _renderer = nullptr;
		SDL_Event _events;
		bool _running;
		SDL_Window * _window = nullptr;
	};

	class BloomException : public std::exception {
	public:
		BloomException(std::string && _Message) noexcept;
		BloomException(std::string && _Message, int _ErrNo) noexcept;
		BloomException(char const * const _Message) noexcept;
		BloomException(char const * const _Message, int _ErrNo) noexcept;
	};
}
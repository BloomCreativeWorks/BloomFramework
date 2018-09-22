#pragma once
#include "stdIncludes.h"
#include "Exception.h"
#include <iostream>

namespace bloom {
	class BLOOMFRAMEWORK_API Game {
	public:
		Game(int width, int height, int m_windowFlags, int m_rendererFlags);
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
		int m_screenWidth, m_screenHeight;
		int m_windowFlags, m_rendererFlags;
		SDL_Renderer * m_renderer = nullptr;
		SDL_Event m_events;
		bool m_running;
		SDL_Window * m_window = nullptr;
	};
}
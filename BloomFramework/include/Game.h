#pragma once
#include "stdIncludes.h"
#include "Exception.h"
#include <iostream>

namespace bloom {
	class BLOOMFRAMEWORK_API Game {
	public:
		Game(int width, int height, int windowFlags = NULL, int rendererFlags = NULL);
		~Game();

		static void initialize(Uint32 initFlags = SDL_INIT_EVERYTHING,
			int mixerFrequency = 44100, Uint16 mixerformat = MIX_DEFAULT_FORMAT, int mixerChannels = 2, int mixerChunksize = 2048,
			int imageFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
		static void exit();

		void create(std::string const& title, int xpos, int ypos);
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
		SDL_Window * m_window = nullptr;
		SDL_Event m_events;
		bool m_running;
	};
}
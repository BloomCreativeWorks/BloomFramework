#pragma once

#include "stdIncludes.h"
#include "Graphics/TextureStore.h"
#include "Timer.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Game {
		using TextureStore = bloom::graphics::TextureStore;
		friend TextureStore::TextureStore(Game & object);

	public:
		Game(int width, int height, int windowFlags = NULL, int rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		Game(std::nothrow_t, int width, int height, int windowFlags = NULL, int rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		~Game();

		static void initialize(Uint32 initFlags = SDL_INIT_EVERYTHING,
			int mixerFrequency = 44100, Uint16 mixerformat = MIX_DEFAULT_FORMAT, int mixerChannels = 2, int mixerChunksize = 2048,
			int imageFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);


		void create(const std::string & title, int xpos, int ypos);
		void update();
		void clear();
		void delay(int intervalMs);
		void render();
		void destroy();
		void handleEvents();
		bool isRunning();

		void hideWindow();
		void showWindow();

		void setColor(const SDL_Color & color);
		void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		SDL_Color getColor();
		void getColor(Uint8 & r, Uint8 & g, Uint8 & b, Uint8 & a);
		int getScreenWidth();
		int getScreenHeight();
		SDL_Event getEvent();

		TextureStore	textures = TextureStore(m_renderer);
		Timer			timer;

	protected:
		SDL_Renderer *	m_renderer = nullptr;
		SDL_Window *	m_window = nullptr;
		int				m_screenWidth, m_screenHeight;
		const int		m_windowFlags, m_rendererFlags;
		SDL_Color		m_color;
		SDL_Event		m_event;
		bool			m_isRunning;

	private:
		static void exit();
		static int m_runningInstancesQnt;
	};
}
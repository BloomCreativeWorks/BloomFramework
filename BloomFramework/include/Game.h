#pragma once

#include <iostream>
#include "stdIncludes.h"
#include "TextureStore.h"
#include "Timer.h"
#include "Screen.h"
#include "Exception.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Game {
		friend TextureStore::TextureStore(Game & object);

	public:
		Game(int width, int height, int windowFlags = NULL, int rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		Game(std::nothrow_t, int width, int height, int windowFlags = NULL, int rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		~Game();

		static void initialize(Uint32 initFlags = SDL_INIT_EVERYTHING,
			int mixerFrequency = 44100, Uint16 mixerformat = MIX_DEFAULT_FORMAT, int mixerChannels = 2, int mixerChunksize = 2048,
			int imageFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
		static void exit();

		void create(const std::string & title, int xpos, int ypos);
		void update();
		void clear();
		void delay(int intervalMs);
		void render();
		void destroy();
		void handleEvents();
		bool isRunning();

		void setColor(const SDL_Color & color);
		void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		SDL_Color getColor();
		void getColor(Uint8 & r, Uint8 & g, Uint8 & b, Uint8 & a);
		int getScreenWidth();
		int getScreenHeight();
		SDL_Event getEvent();

		TextureStore	textures = TextureStore(m_renderer);
		Timer			timer;

		template <typename T>
		void registerScreen(const std::string & tag) {
			static_assert (std::is_base_of<Screen, T>::value, "Type T passed in is not a Screen");
			if (m_screens.find(tag) != m_screens.end()) {
				m_screens.emplace(tag, std::unique_ptr<T>);
			}
			else {
				throw Exception("Screen with tag " + tag + " has been registered already");
			}
		}

		void unregisterScreen(const std::string & tag) {
				m_screens.erase(tag);
		}
		void setActiveScreen(const std::string & tag) {
			auto tmp = m_screens.find(tag);
			if (tmp != m_screens.end())
				m_activeScreen = tmp->second;
			else
				throw Exception("Can't set Screen with tag " + tag + " as active screen. It is not registered.");
		}

	protected:
		SDL_Renderer *	m_renderer = nullptr;
		SDL_Window *	m_window = nullptr;
		int				m_screenWidth, m_screenHeight;
		const int		m_windowFlags, m_rendererFlags;
		SDL_Color		m_color;
		SDL_Event		m_event;
		bool			m_isRunning;
		std::unordered_map<std::string, ScrPtr> m_screens;
		ScrPtr m_activeScreen;
	};
}
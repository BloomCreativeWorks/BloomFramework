#pragma once
#include <iostream>
#include "stdIncludes.h"
#include "TextureStore.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Game {
		friend TextureStore::TextureStore(Game & object);
	public:
		Game(int width, int height, int windowFlags = NULL, int rendererFlags = NULL);
		~Game();

		static void initialize(Uint32 initFlags = SDL_INIT_EVERYTHING,
			int mixerFrequency = 44100, Uint16 mixerformat = MIX_DEFAULT_FORMAT, int mixerChannels = 2, int mixerChunksize = 2048,
			int imageFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
		static void exit();

		void create(std::string const& title, int xpos, int ypos);
		void update();
		void clear();
		void delay(int intervalMs);
		void render();
		void destroy();
		void handleEvents();
		bool isRunning();

		TexturePtr loadTexture(const std::string & filePath, std::optional<SDL_Color> colorKey = std::nullopt);
		void unloadTexture(const std::string & filePath);

		void setColor(SDL_Color const& color);
		void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		SDL_Color getColor();
		void getColor(Uint8 & r, Uint8 & g, Uint8 & b, Uint8 & a);
		int getScreenWidth();
		int getScreenHeight();
		SDL_Event getEvent();

	protected:
		int m_screenWidth, m_screenHeight;
		const int m_windowFlags, m_rendererFlags;
		SDL_Renderer * m_renderer = nullptr;
		SDL_Window * m_window = nullptr;
		SDL_Color m_color;
		SDL_Event m_event;
		bool m_isRunning;
		TextureStore m_textureStore;
	};
}
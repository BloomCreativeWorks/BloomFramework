#pragma once

#include "stdIncludes.h"
#include "Graphics/TextureStore.h"
#include "Timer.h"

using namespace bloom::graphics;

namespace bloom {
	class BLOOMFRAMEWORK_API Game {
		friend TextureStore::TextureStore(Game & object);

	public:
		Game(int width, int height, int window_flags = NULL, int renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		Game(std::nothrow_t, int width, int height, int window_flags = NULL, int renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		~Game();

		static void initialize(Uint32 init_flags = SDL_INIT_EVERYTHING,
			int mixer_frequency = 44100, Uint16 mixer_format = MIX_DEFAULT_FORMAT, int mixer_channels = 2, int mixer_chunksize = 2048,
			int image_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
		static void exit();

		void create(const std::string & title, int x_pos, int y_pos);
		void update();
		void clear();
		void delay(int interval_ms);
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

		TextureStore	textures = TextureStore(renderer_);
		Timer			timer;

	protected:
		SDL_Renderer *	renderer_ = nullptr;
		SDL_Window *	window_ = nullptr;
		int				screen_width_, screen_height_;
		const int		window_flags_, renderer_flags_;
		SDL_Color		color_;
		SDL_Event		event_;
		bool			is_running_;
	};
}
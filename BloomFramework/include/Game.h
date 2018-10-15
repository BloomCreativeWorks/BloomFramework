#ifndef BLOOM_GAME_H_
#define BLOOM_GAME_H_

#include "stdIncludes.h"
#include "Graphics/TextureStore.h"
#include "Timer.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Game {
		using TextureStore = bloom::graphics::TextureStore;
		friend TextureStore::TextureStore(Game & object);

	public:
		Game(int width, int height, int window_flags = NULL, int renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		Game(std::nothrow_t, int width, int height, int window_flags = NULL, int renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		~Game();

		static void Init(Uint32 init_flags = SDL_INIT_EVERYTHING,
			int mixer_frequency = 44100, Uint16 mixer_format = MIX_DEFAULT_FORMAT, int mixer_channels = 2, int mixer_chunksize = 2048,
			int image_flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
		static void Exit();

		void Create(const std::string & title, int x_pos, int y_pos);
		void Update();
		void Clear();
		void Delay(int interval_ms);
		void Render();
		void Destroy();
		void HandleEvents();
		bool IsRunning();

		void set_color(const SDL_Color & color);
		void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		SDL_Color color();
		void color(Uint8 & r, Uint8 & g, Uint8 & b, Uint8 & a);
		int screen_width();
		int screen_height();
		SDL_Event event();

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
} // namespace bloom

#endif // !BLOOM_GAME_H_
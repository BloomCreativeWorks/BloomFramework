#pragma once

#include "stdIncludes.h"

#include "Graphics/TextureStore.h"
#include "Timer.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Game {
		using TextureStore = bloom::graphics::TextureStore;
		friend TextureStore::TextureStore(Game& object);

	public:
		Game(int width, int height, int windowFlags = 0, int rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		Game(std::nothrow_t, int width, int height, int windowFlags = 0, int rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		Game(const Game&) = delete;
		Game(Game&&) = delete;
		Game& operator=(const Game&) = delete;
		Game& operator=(Game&&) = delete;
		~Game();

		static void init(Uint32 initFlags = SDL_INIT_EVERYTHING,
			int mixerFrequency = 44100, Uint16 mixerformat = MIX_DEFAULT_FORMAT, int mixerChannels = 2, int mixerChunksize = 2048,
			int imageFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
		static void delay(int intervalMs) noexcept;

		void create(const std::string& title, int xpos, int ypos);
		void update();
		void clear() noexcept;
		void render() noexcept;
		void destroy();
		void handleEvents() noexcept;
		bool isRunning() const noexcept;

		void hideWindow() noexcept;
		void showWindow() noexcept;

		void setColor(const SDL_Color& color) noexcept;
		void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) noexcept;

		SDL_Color getColor() const noexcept;
		void getColor(Uint8& r, Uint8& g, Uint8& b, Uint8& a) const noexcept;
		int getScreenWidth() const noexcept;
		int getScreenHeight() const noexcept;
		SDL_Event getEvent() const noexcept;

		TextureStore	textures{ m_renderer };
		Timer			timer;

	protected:
		SDL_Renderer*	m_renderer = nullptr;
		SDL_Window*		m_window = nullptr;
		int				m_screenWidth, m_screenHeight;
		const int		m_windowFlags, m_rendererFlags;
		SDL_Color		m_color{ 0, 0, 0, 0 };
		SDL_Event		m_event{};
		bool			m_isRunning;

	private:
		static void exit() noexcept;
		//static int m_runningInstancesQnt;
	};
}
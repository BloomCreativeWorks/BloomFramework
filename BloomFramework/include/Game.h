#pragma once

#include "stdIncludes.h"
#include "Graphics/TextureStore.h"
#include "Timer.h"
#include "Components/Size.h"
#include "Components/Position.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Game {
	public:
		/**
		 * @param windowSize Required window size
		 * @param flags Window and renderer flags
		 */
		Game(components::Size windowSize, const std::pair<int, int>& flags = { 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC });
		//Game(std::nothrow_t, components::Size windowSize, const std::pair<int, int>& flags = { SDL_WINDOW_FULLSCREEN, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC });
		~Game();

		/**
		 * @brief Initializes SDL subsystems and modules with certain parameters
		 *
		 * @param initFlags Subsystems that need to be initialized
		 * @param mixerParams Frequency, format, number of channels and chunk size needed to init SDL_Mixer
		 * @param imageFlags Flags of image formats to be used, all by default
		 */
		static void initialize(uint32_t initFlags = SDL_INIT_EVERYTHING,
			const std::tuple<int, uint16_t, int, int>& mixerParams = { 44100, MIX_DEFAULT_FORMAT , 2, 2048 },
			int imageFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);

		/**
		 * @brief Cleans up initialized SDL subsystems and modules
		 */
		static void exit();


		/**
		 * @brief Creates a window with certain parameters
		 *
		 * @param title Window title
		 * @param pos Window position
		 */
		void create(std::string_view title, components::Position pos);

		/**
		 * @brief Updates timer
		 */
		void update();

		/**
		 * @brief Clears the window and fills it with the current color
		 */
		void clear();

		/**
		 * @brief Hangs the window for the specified time (in milliseconds)
		 */
		static void delay(int intervalMs);

		/**
		 * @brief Updates the screen with any rendering performed since the previous call
		 */
		void render();

		/**
		 * @brief Destroys renderer and window
		 */
		void destroy();

		/**
		 * @brief Gets the last event and handles it (at least QuitEvent)
		 */
		void handleEvents();

		/**
		 * @brief Hides the current window
		 */
		void hideWindow();

		/**
		 * @brief Shows the current window
		 */
		void showWindow();

		void setColor(const SDL_Color& color);
		//void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

		bool isRunning() const {
			return m_isRunning;
		}

		SDL_Color getColor() const {
			return m_color;
		}

		//void getColor(uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a) const {
		//	r = m_color.r; g = m_color.g; b = m_color.b; a = m_color.a;
		//}

		int getWindowWidth() const {
			return m_windowSize.w;
		}

		int getWindowHeight() const {
			return m_windowSize.h;
		}

		components::Size getWindowSize() const {
			return m_windowSize;
		}

		SDL_Event getEvent() const {
			return m_event;
		}


		/**
		 * @brief THIS IS AN INTERNAL FUNCTION, DON'T CALL IT!
		 */
		SDL_Renderer*& _getRenderer() {
			return m_renderer;
		}

		graphics::TextureStore textures{ m_renderer };
		Timer timer;

	protected:
		SDL_Renderer* m_renderer{ nullptr };
		SDL_Window* m_window{ nullptr };
		components::Size m_windowSize;
		const int c_windowFlags, c_rendererFlags;
		SDL_Color m_color{};
		SDL_Event m_event{};
		bool m_isRunning;

	private:
		static int s_runningInstancesQnt;
	};
}
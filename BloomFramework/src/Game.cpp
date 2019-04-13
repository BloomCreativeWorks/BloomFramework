#include "Game.h"
#include "Exception.h"

// Yeah, I know macros are bad
#define CHECK_IMG_FORMAT_FAILED(format) if (failed & IMG_INIT_##format) \
std::clog << "Failed to initialize " << #format << " format support" << std::endl;

namespace bloom {
	int Game::s_runningInstancesQnt = 0;

	Game::Game(components::Size windowSize, const std::pair<int, int>& flags) :
		m_windowSize(windowSize),
		c_windowFlags(flags.first),
		c_rendererFlags(flags.second),
		m_isRunning(false)
	{
		++s_runningInstancesQnt;

		// Can't reproduce it :(
		//if ((c_windowFlags & (SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP)) == SDL_WINDOW_FULLSCREEN)
		//	throw Exception{ "Game", "SDL_WINDOW_FULLSCREEN flag is used. \
		//		This can lead to graphic oddities when using hardware acceleration! Use SDL_WINDOW_FULLSCREEN_DESKTOP flag instead." };
	}

	//Game::Game(std::nothrow_t, components::Size windowSize, const std::pair<int, int>& flags) :
	//	m_screenWidth(windowSize.w),
	//	m_screenHeight(windowSize.h),
	//	c_windowFlags(flags.first),
	//	c_rendererFlags(flags.second),
	//	m_isRunning(false)
	//{
	//	if (SDL_WasInit(0) == 0)
	//		initialize();

	//	if (c_windowFlags & SDL_WINDOW_FULLSCREEN)
	//		std::clog << "[Game] SDL_WINDOW_FULLSCREEN flag is used. This can lead to graphic oddities when using hardware acceleration!" << std::endl;
	//}

	Game::~Game() {
		destroy();
		--s_runningInstancesQnt;
		//if (s_runningInstancesQnt <= 0)
		//	exit();
	}

	void Game::initialize(uint32_t initFlags,
		const std::tuple<int, uint16_t, int, int>& mixerParams,
		int imageFlags)
	{
		// Initialize SDL
		if (SDL_Init(initFlags))
			throw Exception{ "Game::initialize", SDL_GetError() };
		std::clog << "SDL initialized" << std::endl;

		// Initialize SDL_mixer
		if (Mix_OpenAudio(std::get<0>(mixerParams), std::get<1>(mixerParams),
			std::get<2>(mixerParams), std::get<3>(mixerParams)))
			throw Exception{ "Game::initialize", SDL_GetError() };
		std::clog << "SDL_mixer initialized" << std::endl;

		const auto n = SDL_GetNumAudioDevices(false);
		std::clog << "The number of audio devices: " << n << std::endl;
		for (auto i = 0; i < n; ++i)
			std::clog << "Audio device #" << i + 1 << ": " << SDL_GetAudioDeviceName(i, false) << std::endl;

		// Initialize SDL_ttf
		if (TTF_Init())
			throw Exception{ "Game::initialize", SDL_GetError() };
		std::clog << "SDL_ttf initialized" << std::endl;

		// Initialize SDL_image
		if (const auto formats = IMG_Init(imageFlags); formats != imageFlags) {
			if (!formats)
				throw Exception{ "Game::initialize", SDL_GetError() };
			std::clog << "Not all image formats have been initialized successfully" << std::endl;
			const auto failed = formats ^ imageFlags;
			CHECK_IMG_FORMAT_FAILED(JPG);
			CHECK_IMG_FORMAT_FAILED(PNG);
			CHECK_IMG_FORMAT_FAILED(TIF);
			CHECK_IMG_FORMAT_FAILED(WEBP);
		}
		std::clog << "SDL_image initialized" << std::endl;
	}

	void Game::exit() {
		// Prevent the SDL from being unloaded if there is at least one alive object
		if (!s_runningInstancesQnt) {
			IMG_Quit();
			TTF_Quit();
			Mix_Quit();
			SDL_Quit();
		}
	}

	void Game::create(std::string_view title, components::Position pos) {
		m_window = SDL_CreateWindow(title.data(), pos.x, pos.y, m_windowSize.w, m_windowSize.h, c_windowFlags);
		if (!m_window)
			throw Exception{ "Game::initialize", SDL_GetError() };
		std::clog << "Window created with width of " << m_windowSize.w << " and height of " << m_windowSize.h << std::endl;

		m_renderer = SDL_CreateRenderer(m_window, -1, c_rendererFlags);
		if (!m_renderer)
			throw Exception{ "Game::initialize", SDL_GetError() };
		std::clog << "Renderer initialized." << std::endl;

		m_isRunning = true;
		std::clog << "Game is now running" << std::endl;
	}

	void Game::handleEvents() {
		SDL_PollEvent(&m_event);

		if (m_event.type == SDL_QUIT)
			m_isRunning = false;
	}

	void Game::update() {
		std::clog << "Delta time: " << timer.lap() << std::endl;
	}

	void Game::clear() {
		SDL_RenderClear(m_renderer);
	}

	void Game::delay(int intervalMs) {
		SDL_Delay(intervalMs);
	}

	void Game::render() {
		SDL_RenderPresent(m_renderer);
	}

	void Game::destroy() {
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
		std::clog << "Window destroyed" << std::endl;
	}

	void Game::hideWindow() {
		SDL_HideWindow(m_window);
	}

	void Game::showWindow() {
		SDL_ShowWindow(m_window);
	}

	void Game::setColor(const SDL_Color& color) {
		m_color = color;
		SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b, m_color.a);
	}

	//void Game::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	//	m_color = { r, g, b, a };
	//	SDL_SetRenderDrawColor(m_renderer, m_color.r, m_color.g, m_color.b, m_color.a);
	//}
}
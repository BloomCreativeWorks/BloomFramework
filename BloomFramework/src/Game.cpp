#include <iostream>
#include "Game.h"
#include "Exception.h"

namespace bloom {
	//int Game::m_runningInstancesQnt = 0;

	Game::Game(int width, int height, int windowFlags, int rendererFlags) :
		m_screenWidth(width),
		m_screenHeight(height),
		m_windowFlags(windowFlags),
		m_rendererFlags(rendererFlags),
		m_isRunning(false)
	{
		if (SDL_WasInit(0) == 0)
			init();

		if ((windowFlags & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN && (windowFlags & SDL_WINDOW_FULLSCREEN_DESKTOP) != SDL_WINDOW_FULLSCREEN_DESKTOP)
			throw Exception("[Game] SDL_WINDOW_FULLSCREEN flag is used. This can lead to graphic oddities when using hardware acceleration! Use SDL_WINDOW_FULLSCREEN_DESKTOP flag instead.");

		//m_runningInstancesQnt++;
	}

	Game::Game(std::nothrow_t, int width, int height, int windowFlags, int rendererFlags) :
		m_screenWidth(width),
		m_screenHeight(height),
		m_windowFlags(windowFlags),
		m_rendererFlags(rendererFlags),
		m_isRunning(false)
	{
		if (SDL_WasInit(0) == 0)
			init();

		if ((windowFlags & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN)
			std::clog << "[Game] SDL_WINDOW_FULLSCREEN flag is used. This can lead to graphic oddities when using hardware acceleration!" << std::endl;
	}

	Game::~Game() {
		destroy();
		//m_runningInstancesQnt--;
		//if (m_runningInstancesQnt <= 0)
		//	exit();
	}

	void Game::init(Uint32 initFlags,
		int mixerFrequency, Uint16 mixerFormat, int mixerChannels, int mixerChunksize,
		int imageFlags)
	{
		// Initialize SDL
		if (SDL_Init(initFlags) < 0)
			throw Exception("[SDL_Init] " + std::string(SDL_GetError()));
		else
			std::clog << "Subsystems initialized!" << std::endl;

		// Initialize SDL_mixer
		if (Mix_OpenAudio(mixerFrequency, mixerFormat, mixerChannels, mixerChunksize) < 0)
			throw Exception("[Mix_OpenAudio] " + std::string(SDL_GetError()));
		else
			std::clog << "SDL_mixer initialized." << std::endl;

		const int isCapture = 0;
		const int n = SDL_GetNumAudioDevices(isCapture);
		std::clog << "Audio devices: " << n << std::endl;
		for (int i = 0; i < n; i++)
			std::clog << "Audio: " << SDL_GetAudioDeviceName(i, isCapture) << std::endl;

		// Initialize SDL_ttf
		if (TTF_Init() != 0)
			throw Exception("[TTF_Init] " + std::string(SDL_GetError()));
		else
			std::clog << "SDL_ttf initialized." << std::endl;

		// Initialize SDL_image
		if (IMG_Init(imageFlags) != imageFlags)
			throw Exception("[IMG_Init] " + std::string(SDL_GetError()));
		else
			std::clog << "SDL_image initialized." << std::endl;
	}

	void Game::exit() noexcept {
		IMG_Quit();
		TTF_Quit();
		Mix_Quit();
		SDL_Quit();
	}

	void Game::create(std::string const& title, int xpos, int ypos) {
		m_window = SDL_CreateWindow(title.c_str(), xpos, ypos, m_screenWidth, m_screenHeight, m_windowFlags);
		if (!m_window)
			throw Exception("[SDL_CreateWindow] " + std::string(SDL_GetError()));
		else
			std::clog << "Window created with width of " << m_screenWidth << " and height of " << m_screenHeight << "." << std::endl;

		m_renderer = SDL_CreateRenderer(m_window, -1, m_rendererFlags);
		if (!m_renderer)
			throw Exception("[SDL_CreateRenderer] " + std::string(SDL_GetError()));
		else
			std::clog << "Renderer initialized." << std::endl;

		m_isRunning = true;
		std::clog << "Game is now running!" << std::endl;
	}

	void Game::handleEvents() noexcept {
		SDL_PollEvent(&m_event);

		if (m_event.type == SDL_QUIT)
			m_isRunning = false;
	}

	void Game::update() {
		std::clog << "Delta time: " << timer.lap() << std::endl;
	}

	void Game::clear() noexcept {
		SDL_RenderClear(m_renderer);
	}

	void Game::delay(int intervalMs) noexcept {
		SDL_Delay(intervalMs);
	}

	void Game::render() noexcept {
		SDL_RenderPresent(m_renderer);
	}

	void Game::destroy() {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		m_renderer = nullptr;
		m_window = nullptr;
		std::clog << "Window destroyed!" << std::endl;
	}

	bool Game::isRunning() const noexcept {
		return m_isRunning;
	}

	void Game::hideWindow() noexcept {
		SDL_HideWindow(m_window);
	}

	void Game::showWindow() noexcept {
		SDL_ShowWindow(m_window);
	}

	void Game::setColor(const SDL_Color & color) noexcept {
		m_color = color;
		SDL_SetRenderDrawColor(m_renderer, m_color.a, m_color.g, m_color.b, m_color.a);
	}

	void Game::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) noexcept {
		m_color = { r, g, b, a };
		SDL_SetRenderDrawColor(m_renderer, m_color.a, m_color.g, m_color.b, m_color.a);
	}

	SDL_Color Game::getColor() const noexcept {
		return m_color;
	}

	void Game::getColor(Uint8 & r, Uint8 & g, Uint8 & b, Uint8 & a) const noexcept {
		r = m_color.r; g = m_color.g; b = m_color.b; a = m_color.a;
	}

	int Game::getScreenHeight() const noexcept {
		return m_screenHeight;
	}

	int Game::getScreenWidth() const noexcept {
		return m_screenWidth;
	}

	SDL_Event Game::getEvent() const noexcept {
		return m_event;
	}
}
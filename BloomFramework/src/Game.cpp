#include "..\include\Game.h"

namespace bloom {
	Game::Game(int width, int height, int windowFlags, int rendererFlags) :
		m_screenWidth(width),
		m_screenHeight(height),
		m_windowFlags(windowFlags),
		m_rendererFlags(rendererFlags),
		m_running(false) {

		if (SDL_WasInit(0) == 0)
			initialize();
	}

	Game::~Game() {
		destroy();
	}

	void Game::initialize(Uint32 initFlags, 
		int mixerFrequency, Uint16 mixerFormat, int mixerChannels, int mixerChunksize,
		int imageFlags) {

		// Initialize SDL
		if (SDL_Init(initFlags) < 0) {
			throw Exception("[SDL_Init] " + std::string(SDL_GetError()));
		}
		else {
			std::clog << "Subsystems initialized!" << std::endl;
		}

		// Initialize SDL_mixer
		if (Mix_OpenAudio(mixerFrequency, mixerFormat, mixerChannels, mixerChunksize) < 0) {
			throw Exception("[Mix_OpenAudio] " + std::string(SDL_GetError()));
		}
		else {
			std::clog << "SDL_mixer initialized." << std::endl;
		}

		int isCapture = 0;
		int n = SDL_GetNumAudioDevices(isCapture);
		std::clog << "Audio devices: " << n << std::endl;
		for (int i = 0; i < n; i++) {
			auto name = SDL_GetAudioDeviceName(i, isCapture);
			std::clog << "Audio: " << name << std::endl;
		}

		// Initialize SDL_ttf
		if (TTF_Init() != 0) {
			throw Exception("[TTF_Init] " + std::string(SDL_GetError()));
		}
		else {
			std::clog << "SDL_ttf initialized." << std::endl;
		}

		// Initialize SDL_image
		if (IMG_Init(imageFlags) != imageFlags) {
			throw Exception("[IMG_Init] " + std::string(SDL_GetError()));
		}
		else {
			std::clog << "SDL_image initialized." << std::endl;
		}
	}

	void Game::exit() {
		IMG_Quit();
		TTF_Quit();
		Mix_Quit();
		SDL_Quit();
	}

	void Game::create(std::string const& title, int xpos, int ypos) {
		m_window = SDL_CreateWindow(title.c_str(), xpos, ypos, m_screenWidth, m_screenHeight, m_windowFlags);
		if (m_window == NULL) {
			throw Exception("[SDL_CreateWindow] " + std::string(SDL_GetError()));
		}
		else {
			std::clog << "Window created with width of " << m_screenWidth << " and height of " << m_screenHeight << "." << std::endl;
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, m_rendererFlags);
		if (m_renderer == NULL) {
			throw Exception("[SDL_CreateRenderer] " + std::string(SDL_GetError()));
		}
		else {
			std::clog << "Renderer initialized." << std::endl;
		}

		m_running = true;
		std::clog << "Game is now running!" << std::endl;
	}

	void Game::handleEvents() {
		SDL_PollEvent(&m_events);

		if (m_events.type == SDL_QUIT)
			m_running = false;
	}

	void Game::update() {
		// Nothing here yet.
	}

	void Game::render() {
		SDL_RenderClear(m_renderer);
		// Hopefully draw stuff.
		SDL_RenderPresent(m_renderer);
	}

	void Game::destroy() {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		m_renderer = nullptr;
		m_window = nullptr;
		std::clog << "Window destroyed!" << std::endl;
	}

	bool Game::isRunning() {
		return m_running;
	}

	int Game::getScreenHeight() {
		return m_screenHeight;
	}

	int Game::getScreenWidth() {
		return m_screenWidth;
	}
}
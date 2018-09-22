#include "..\include\Game.h"

namespace bloom {
	Game::Game(int width, int height, int m_windowFlags, int m_rendererFlags) :
		m_screenWidth(width),
		m_screenHeight(height),
		m_windowFlags(m_windowFlags),
		m_rendererFlags(m_rendererFlags),
		m_running(false) {}

	Game::~Game() {
		destroy();
	}

	bool Game::init(std::string const& title, int xpos, int ypos) {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			//std::cerr << "[SDL_Init] " << SDL_GetError() << std::endl;
			throw Exception("[SDL_Init] " + std::string(SDL_GetError()));
			return false;
		}
		else {
			std::clog << "Subsystems initialized!" << std::endl;
		}

		m_window = SDL_CreateWindow(title.c_str(), xpos, ypos, m_screenWidth, m_screenHeight, m_windowFlags);
		if (m_window == NULL) {
			//std::cerr << "[SDL_CreateWindow] " << SDL_GetError() << std::endl;
			throw Exception("[SDL_CreateWindow] " + std::string(SDL_GetError()));
			return false;
		}
		else {
			std::clog << "Window created with width of " << m_screenWidth << " and height of " << m_screenHeight << "." << std::endl;
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, m_rendererFlags);
		if (m_renderer == NULL) {
			//std::cerr << "[SDL_CreateRenderer] " << SDL_GetError() << std::endl;
			throw Exception("[SDL_CreateRenderer] " + std::string(SDL_GetError()));
			return false;
		}
		else {
			std::clog << "Renderer initialized." << std::endl;
		}


		//Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			//std::cerr << "[Mix_OpenAudio] " << SDL_GetError() << std::endl;
			throw Exception("[Mix_OpenAudio] " + std::string(SDL_GetError()));

			SDL_DestroyWindow(m_window); m_window = nullptr;
			SDL_DestroyRenderer(m_renderer); m_renderer = nullptr;
			return false;
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

		// Initialize SDL_TTF 
		if (TTF_Init() != 0) {
			//std::cerr << "[TTF_Init] " << SDL_GetError() << std::endl;
			throw Exception("[TTF_Init] " + std::string(SDL_GetError()));

			SDL_DestroyWindow(m_window); m_window = nullptr;
			SDL_DestroyRenderer(m_renderer); m_renderer = nullptr;
			return false;
		}
		else {
			std::clog << "SDL_ttf initialized." << std::endl;
		}

		m_running = true;
		std::clog << "Game is now running!" << std::endl;
		return true;
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
		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
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
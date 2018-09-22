#include "..\include\Game.h"

namespace bloom {
	Game::Game(int width, int height, int _windowFlags, int _rendererFlags) :
		_screenWidth(width),
		_screenHeight(height),
		_windowFlags(_windowFlags),
		_rendererFlags(_rendererFlags),
		_running(false) {}

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

		_window = SDL_CreateWindow(title.c_str(), xpos, ypos, _screenWidth, _screenHeight, _windowFlags);
		if (_window == NULL) {
			//std::cerr << "[SDL_CreateWindow] " << SDL_GetError() << std::endl;
			throw Exception("[SDL_CreateWindow] " + std::string(SDL_GetError()));
			return false;
		}
		else {
			std::clog << "Window created with width of " << _screenWidth << " and height of " << _screenHeight << "." << std::endl;
		}

		_renderer = SDL_CreateRenderer(_window, -1, _rendererFlags);
		if (_renderer == NULL) {
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

			SDL_DestroyWindow(_window); _window = nullptr;
			SDL_DestroyRenderer(_renderer); _renderer = nullptr;
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

			SDL_DestroyWindow(_window); _window = nullptr;
			SDL_DestroyRenderer(_renderer); _renderer = nullptr;
			return false;
		}
		else {
			std::clog << "SDL_ttf initialized." << std::endl;
		}

		_running = true;
		std::clog << "Game is now running!" << std::endl;
		return true;
	}

	void Game::handleEvents() {
		SDL_PollEvent(&_events);

		if (_events.type == SDL_QUIT)
			_running = false;
	}

	void Game::update() {
		// Nothing here yet.
	}

	void Game::render() {
		SDL_RenderClear(_renderer);
		// Hopefully draw stuff.
		SDL_RenderPresent(_renderer);
	}

	void Game::destroy() {
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
		std::clog << "Window destroyed!" << std::endl;
	}

	bool Game::isRunning() {
		return _running;
	}

	int Game::getScreenHeight() {
		return _screenHeight;
	}

	int Game::getScreenWidth() {
		return _screenWidth;
	}
}
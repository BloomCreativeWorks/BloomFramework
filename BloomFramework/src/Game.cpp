#include "Game.h"
#include "Exception.h"

namespace bloom {
	Game::Game(int width, int height, int window_flags, int renderer_flags) :
		screen_width_(width),
		screen_height_(height),
		window_flags_(window_flags),
		renderer_flags_(renderer_flags),
		is_running_(false)
	{
		if (SDL_WasInit(0) == 0)
			initialize();

		if ((window_flags & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN && (window_flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != SDL_WINDOW_FULLSCREEN_DESKTOP) {
			throw Exception("[Game] SDL_WINDOW_FULLSCREEN flag is used. This can lead to graphic oddities when using hardware acceleration! Use SDL_WINDOW_FULLSCREEN_DESKTOP flag instead.");
		}
	}

	Game::Game(std::nothrow_t, int width, int height, int window_flags, int renderer_flags) :
		screen_width_(width),
		screen_height_(height),
		window_flags_(window_flags),
		renderer_flags_(renderer_flags),
		is_running_(false)
	{
		if (SDL_WasInit(0) == 0)
			initialize();

		if ((window_flags & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN)
			std::clog << "[Game] SDL_WINDOW_FULLSCREEN flag is used. This can lead to graphic oddities when using hardware acceleration!" << std::endl;
	}

	Game::~Game() {
		destroy();
	}

	void Game::initialize(Uint32 init_flags,
		int mixer_frequency, Uint16 mixer_format, int mixer_channels, int mixer_chunksize,
		int image_flags)
	{
		// Initialize SDL
		if (SDL_Init(init_flags) < 0) {
			throw Exception("[SDL_Init] " + std::string(SDL_GetError()));
		}
		else {
			std::clog << "Subsystems initialized!" << std::endl;
		}

		// Initialize SDL_mixer
		if (Mix_OpenAudio(mixer_frequency, mixer_format, mixer_channels, mixer_chunksize) < 0) {
			throw Exception("[Mix_OpenAudio] " + std::string(SDL_GetError()));
		}
		else {
			std::clog << "SDL_mixer initialized." << std::endl;
		}

		int is_capture = 0;
		int n = SDL_GetNumAudioDevices(is_capture);
		std::clog << "Audio devices: " << n << std::endl;
		for (int i = 0; i < n; i++) {
			auto name = SDL_GetAudioDeviceName(i, is_capture);
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
		if (IMG_Init(image_flags) != image_flags) {
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

	void Game::create(std::string const& title, int x_pos, int y_pos) {
		window_ = SDL_CreateWindow(title.c_str(), x_pos, y_pos, screen_width_, screen_height_, window_flags_);
		if (window_ == nullptr) {
			throw Exception("[SDL_CreateWindow] " + std::string(SDL_GetError()));
		}
		else {
			std::clog << "Window created with width of " << screen_width_ << " and height of " << screen_height_ << "." << std::endl;
		}

		renderer_ = SDL_CreateRenderer(window_, -1, renderer_flags_);
		if (renderer_ == nullptr) {
			throw Exception("[SDL_CreateRenderer] " + std::string(SDL_GetError()));
		}
		else {
			std::clog << "Renderer initialized." << std::endl;
		}

		is_running_ = true;
		std::clog << "Game is now running!" << std::endl;
	}

	void Game::handleEvents() {
		SDL_PollEvent(&event_);

		if (event_.type == SDL_QUIT)
			is_running_ = false;
	}

	void Game::update() {
		std::clog << "Delta time: " << timer.lap() << std::endl;
	}

	void Game::clear() {
		SDL_RenderClear(renderer_);
	}

	void Game::delay(int interval_ms) {
		SDL_Delay(interval_ms);
	}

	void Game::render() {
		SDL_RenderPresent(renderer_);
	}

	void Game::destroy() {
		SDL_DestroyRenderer(renderer_);
		SDL_DestroyWindow(window_);
		renderer_ = nullptr;
		window_ = nullptr;
		std::clog << "Window destroyed!" << std::endl;
	}

	bool Game::isRunning() {
		return is_running_;
	}

	void Game::setColor(const SDL_Color & color) {
		color_ = color;
		SDL_SetRenderDrawColor(renderer_, color_.a, color_.g, color_.b, color_.a);
	}

	void Game::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
		color_ = { r, g, b, a };
		SDL_SetRenderDrawColor(renderer_, color_.a, color_.g, color_.b, color_.a);
	}

	SDL_Color Game::getColor() {
		return color_;
	}

	void Game::getColor(Uint8 & r, Uint8 & g, Uint8 & b, Uint8 & a) {
		r = color_.r; g = color_.g; b = color_.b; a = color_.a;
	}

	int Game::getScreenHeight() {
		return screen_height_;
	}

	int Game::getScreenWidth() {
		return screen_width_;
	}

	SDL_Event Game::getEvent() {
		return event_;
	}
}
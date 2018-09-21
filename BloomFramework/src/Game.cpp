#include "..\include\Game.h"

BloomFramework::Game::Game(int width, int height, int windowFlags, int rendererFlags) :
	screenWidth(width),
	screenHeight(height),
	windowFlags(windowFlags),
	rendererFlags(rendererFlags),
	isRunning(false) {}

BloomFramework::Game::~Game()
{
	clean();
}

bool BloomFramework::Game::init(const char* title, int xpos, int ypos)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "[SDL_Init] " << SDL_GetError() << std::endl;
		return false;
	}
	else {
		std::clog << "Subsystems initialized!" << std::endl;
	}

	window = SDL_CreateWindow(title, xpos, ypos, screenWidth, screenHeight, windowFlags);
	if (window == NULL)
	{
		std::cerr << "[SDL_CreateWindow] " << SDL_GetError() << std::endl;
		return false;
	}
	else {
		std::clog << "Window created with width of " << screenWidth << " and height of " << screenHeight << "." << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, rendererFlags);
	if (renderer == NULL)
	{
		std::cerr << "[SDL_CreateRenderer] " <<  SDL_GetError() << std::endl;
		return false;
	}
	else {
		std::clog << "Renderer initialized." << std::endl;
	}


	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "[Mix_OpenAudio] " << SDL_GetError() << std::endl;
		//printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());

		SDL_DestroyWindow(window); window = nullptr;
		SDL_DestroyRenderer(renderer); renderer = nullptr;
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
		std::cerr << "[TTF_Init] " << SDL_GetError() << std::endl;
		//printf("TTF_Init could not initialize! TTF_Init Error: %s\n", TTF_GetError());

		SDL_DestroyWindow(window); window = nullptr;
		SDL_DestroyRenderer(renderer); renderer = nullptr;
		return false;
	}
	else {
		std::clog << "SDL_ttf initialized." << std::endl;
	}

	isRunning = true;
	std::clog << "Game is now running!" << std::endl;
	return true;
}

void BloomFramework::Game::handleEvents() {
	SDL_PollEvent(&events);

	if (events.type == SDL_QUIT)
		isRunning = false;
	/*switch (events.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}*/
}

void BloomFramework::Game::update() {
	// Nothing here yet.
}


void BloomFramework::Game::render()
{
	SDL_RenderClear(renderer);
	// Hopefully draw stuff.
	SDL_RenderPresent(renderer);
}

void BloomFramework::Game::clean() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	std::clog << "Cleaned window!" << std::endl;
}

bool BloomFramework::Game::running()
{
	return isRunning;
}

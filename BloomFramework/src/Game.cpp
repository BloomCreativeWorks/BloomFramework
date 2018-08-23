#include "../inc/Game.h"
#include "../inc/TextureManager.h"

SDL_Texture* playerTex;
SDL_Rect srcRect, destRect;


BloomFramework::Game::Game() {}

BloomFramework::Game::~Game() {}

void BloomFramework::Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;

	if(fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if(!SDL_Init(SDL_INIT_EVERYTHING)) {
		std::clog << "Subsystems initialized!" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if(renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			std::clog << "renderer initialized!" << std::endl;
		}

		isRunning = true;
	}
	playerTex = TextureManager::loadTexture("assets/player.png", renderer);
}

void BloomFramework::Game::handleEvents() {
	SDL_Event event;

	SDL_PollEvent(&event);

	switch(event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void BloomFramework::Game::update() {
	counter++;
	destRect.h = 136;
	destRect.w = 64;
	destRect.x = counter;
	std::cout << counter << std::endl;
}

void BloomFramework::Game::render() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, playerTex, NULL,&destRect);
	SDL_RenderPresent(renderer);
}

void BloomFramework::Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::clog << "Cleaned window!" << std::endl;
}
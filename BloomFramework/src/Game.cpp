#include "../inc/Game.h"
#include "../inc/TextureManager.h"
#include "../inc/GameObject.h"
#include "../inc/Map.h"
#include "../inc/EntityComponentSystem.h"
#include "../inc/Components.h"
using namespace BloomFramework;

GameObject * player;
GameObject * player2;
Map * map;
SDL_Renderer * BloomFramework::Game::renderer = nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());

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
	player = new GameObject("assets/player.png");
	player2 = new GameObject("assets/player2.png", 50, 50);
	map = new Map();

	newPlayer.addComponent<PositionComponent>();
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
	player->update();
	player2->update();
	manager.update();
	std::cout << newPlayer.getComponent<PositionComponent>().x() << ", " << newPlayer.getComponent<PositionComponent>().y() << std::endl;
}

void BloomFramework::Game::render() {
	SDL_RenderClear(renderer);
	map->drawMap();
	player->render();
	player2->render();
	SDL_RenderPresent(renderer);
}

void BloomFramework::Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::clog << "Cleaned window!" << std::endl;
}


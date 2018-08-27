#include "../inc/Game.h"
#include "../inc/TextureManager.h"
#include "../inc/Map.h"
#include "../inc/ECS/Components.h"
#include "../inc/Collision.h"
using namespace BloomFramework;

Map * map;
SDL_Renderer * BloomFramework::Game::renderer = nullptr;
SDL_Event	Game::event;

Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());


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
	map = new Map();

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("assets/dirt.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("Player");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/grass.png");
	wall.addComponent<ColliderComponent>("wall");
}

void BloomFramework::Game::handleEvents() {
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
	manager.update();
	if(Collision::AABB(player.getComponent<ColliderComponent>().collider,
										 wall.getComponent<ColliderComponent>().collider)) {
		player.getComponent<TransformComponent>().scale = 1;
		player.getComponent<TransformComponent>().velocity * -1;
		std::clog << "Player collided with wall" << std::endl;
	}
}

void BloomFramework::Game::render() {
	SDL_RenderClear(renderer);
	map->drawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void BloomFramework::Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::clog << "Cleaned window!" << std::endl;
}


#include "../inc/Game.h"
#include "../inc/TextureManager.h"
#include "../inc/Map.h"
#include "../inc/ECS/Components.h"
#include "../inc/Collision.h"
using namespace BloomFramework;

Map * map;
SDL_Renderer * BloomFramework::Game::renderer = nullptr;
SDL_Event	Game::event;

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabels : std::size_t {
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

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

	Map::loadMap("assets/tilemap.map", 25, 20);

	player.addComponent<TransformComponent>(0.0f, 0.0f, 32, 32, 2);
	player.addComponent<SpriteComponent>("assets/player_anims.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("Player");
	player.addGroup(groupPlayers);

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/grass.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);
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
	for(auto i : colliders) {
		Collision::AABB(player.getComponent<ColliderComponent>(), *i);
	}
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
auto& colliders(manager.getGroup(groupColliders));

void BloomFramework::Game::render() {
	SDL_RenderClear(renderer);
	//manager.draw();
	for(auto& t : tiles) t->draw();
	for(auto& p : players) p->draw();
	for(auto& e : enemies) e->draw();
	for(auto& c : colliders) c->draw();
	SDL_RenderPresent(renderer);
}

void BloomFramework::Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::clog << "Cleaned window!" << std::endl;
}

void BloomFramework::Game::addTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupMap);
}
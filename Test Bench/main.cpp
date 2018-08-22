#include "framework.h"
using namespace BloomFramework;

Game* game = nullptr;

int main() {

	game = new Game();
	game->init("BloomFramework Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, true);
	while(game->running()) {
		game->handleEvents();
		game->update();
		game->render();

	}
	game->clean();
	return 0;

}
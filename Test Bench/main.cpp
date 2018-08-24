#include "Framework.h"
using namespace BloomFramework;

Game* game = nullptr;

int main() {
	const int fps = 60;
	const int framedelay = 1000 / fps;

	Uint32 framestart;
	int frametime;

	game = new Game();
	game->init("BloomFramework Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	while(game->running()) {
		framestart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		frametime = SDL_GetTicks() - framestart;

		if(framedelay > frametime)
			SDL_Delay(framedelay - frametime);
	}
	game->clean();
	return 0;
}
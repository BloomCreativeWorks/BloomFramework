#include "Framework.h"
using namespace bloom;

Game* game = nullptr;

int main() {
	const int fps = 60;
	const int framedelay = 1000 / fps;

	Uint32 framestart;

	game = new Game(800, 600, NULL, NULL);
	game->init("Bloom Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	while(game->isRunning()) {
		framestart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		int frametime = SDL_GetTicks() - framestart;

		if(framedelay > frametime)
			SDL_Delay(framedelay - frametime);
	}
	game->destroy();
	return 0;
}
#include "Framework.h"
#include <ctime>
using namespace bloom;

Game* game = nullptr;

int main() {
	const int fps = 60;
	const int framedelay = (1000 / fps);

	Uint32 framestart;
	try {
		Game::initialize();
	}
	catch (Exception & e) {
		std::cerr << e.what() << std::endl;
		system("pause");
		exit(-1);
	}
	game = new Game(800, 600);
	try {
		game->create("Bloom Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
	catch (Exception & e) {
		std::cerr << e.what() << std::endl;
	}
	srand(static_cast<uint32_t>(time(0)));
	SDL_Color randColor = { static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255),
	static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255) };
	game->setColor(randColor);
	while (game->isRunning()) {
		framestart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		try {
			game->render();
		}
		catch (Exception & e) {
			std::cerr << e.what() << std::endl;
		}
		int frametime = SDL_GetTicks() - framestart;

		if (framedelay > frametime)
			SDL_Delay(framedelay - frametime);
	}
	game->destroy();
	Game::exit();
	//system("pause");
	return 0;
}
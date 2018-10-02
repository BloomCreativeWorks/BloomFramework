#include "Framework.h"
#include <ctime>
using namespace bloom;

Game* game = nullptr;

int main() {
	const int fps = 500;
	const int framedelay = (1000 / fps);

	//Uint32 framestart;
	Uint32 framestart;
	try {
		Game::initialize();
	}
	catch (Exception & e) {
		std::cerr << e.what() << std::endl;
		system("pause");
		exit(-1);
	}
	game = new Game(1000, 800, SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP, 0);
	try {
		game->create("Bloom Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
	catch (Exception & e) {
		std::cerr << e.what() << std::endl;
	}
	game->music.add("Audio/sample_1.mp3", 1, true);
	game->music.add("Audio/sample_2.mp3");
	//game->music.load("Audio/sample_2-full.mp3");
	srand(static_cast<uint32_t>(time(0)));
	SDL_Color randColor = { static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255),
	static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255) };
	game->setColor(randColor);
	game->clear();
	game->render();
	auto testSprite = game->textureStore.load("Assets/OverworldTestSpritesheet.png", SDL_Color{ 64, 176, 104, 113 });
	testSprite->render(SDL_Rect{ 0,0,32,32 }, SDL_Rect{ 0,0,128,128 });
	game->render();
	game->delay(500);
	auto testSprite2 = game->textureStore.load("Assets/TestChar.png", SDL_Color{ 144,168,0,0 });
	testSprite2->render({ 0, 0, 32, 32 }, { 128,0,128,128 });
	game->render();
	game->delay(500);
	game->music.setInfinitePlayback(true);
	game->music.play();
	int w = 0, h = 0;
	while (game->isRunning()) {
		framestart = SDL_GetTicks();
		game->handleEvents();
		game->clear();
		testSprite->render({ 0, 0, 32, 32 }, { rand() % 1700, rand() % 900, 128, 128 });
		testSprite2->render({ 0, 0, 32, 32 }, { w + 128, h, 128, 128 });
		game->render();
		int frametime = SDL_GetTicks() - framestart;

		if (framedelay > frametime)
			game->delay(framedelay - frametime);

		h += 1; w += 1;
		h %= 1080; w %= 1920;
	}
	game->destroy();
	Game::exit();
	return 0;
}
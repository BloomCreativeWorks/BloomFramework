#include "Framework.h"
#include <ctime>


#include "GameObject.h"
#include "Systems/RenderSystem.h"
using namespace bloom;

Game* game = nullptr;

entt::DefaultRegistry testRegistry;
bloom::GameObject testGO = bloom::GameObject(testRegistry);
bloom::RenderSystem renderSysTest;


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
	game->render();
	auto testSprite = game->loadTexture("Assets/OverworldTestSpritesheet.png", SDL_Color{ 64, 176, 104, 113 });
	testSprite->render(SDL_Rect{ 0,0,32,32 }, SDL_Rect{ 0,0,128,128 });
	game->update();
	game->delay(500);
	auto testSprite2 = game->loadTexture("Assets/TestChar.png", SDL_Color{ 144,168,0,0 });
	testSprite2->render(SDL_Rect{ 0, 0, 32, 32 }, SDL_Rect{ 128,0,128,128 });
	game->update();
	game->delay(500);

	// Test Game Object
	testGO.assignComponent<bloom::Position>(50, 50);
	testGO.assignComponent<bloom::Size>(256, 256);
	auto tmp = game->loadTexture("Assets/TestChar.png", SDL_Color{ 144,168,0,0 });
	testGO.assignComponent<bloom::Sprite>(tmp, SDL_Rect{64,96,32,32});
	renderSysTest.update(testRegistry);
	game->delay(500);
	// Test ends here.

	while (game->isRunning()) {
		framestart = SDL_GetTicks();
		game->handleEvents();
		game->clear();
		try {
			game->render();
		}
		catch (Exception & e) {
			std::cerr << e.what() << std::endl;
		}
		testSprite->render(SDL_Rect{ 0, 0, 32, 32 }, SDL_Rect{ static_cast<uint16_t>(rand() % 672), static_cast<uint16_t>(rand() % 472), 128, 128 });
		testSprite2->render(SDL_Rect{ 0, 0, 32, 32 }, SDL_Rect{ static_cast<uint16_t>(rand() % 672), static_cast<uint16_t>(rand() % 472), 128, 128 });
		renderSysTest.update(testRegistry); // Test again.
		game->update();
		int frametime = SDL_GetTicks() - framestart;

		if (framedelay > frametime)
			game->delay(framedelay - frametime);
	}
	game->destroy();
	Game::exit();
	return 0;
}
#include "Framework.h"
#include <ctime>

#include "GameObjectTest/TestGameObject.h"
#include "GameObjectTest/RandomizerSystem.h"

using namespace bloom;
using bloom::components::Position;

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

	game = new Game(std::nothrow, 800, 600);
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
	game->clear();
	game->render();

	// Test Game Object
	entt::DefaultRegistry testRegistry;
	bloom::systems::RenderSystem renderSysTest(testRegistry);
	game->textures.load("Assets/OverworldTestSpritesheet.png", SDL_Color{ 64, 176, 104, 113 });
	game->textures.load("Assets/TestChar.png", SDL_Color{ 144,168,0,0 });
	TestChar testSprite = TestChar(testRegistry, game);
	testSprite.init(SDL_Rect{ 0,0,128,128 }, "Assets/OverworldTestSpritesheet.png", SDL_Rect{ 0,0,32,32 });
	renderSysTest.update();
	game->render();
	game->delay(500);
	TestChar testSprite2 = TestChar(testRegistry, game);
	testSprite2.init(SDL_Rect{ 128,0,128,128 }, "Assets/TestChar.png", SDL_Rect{ 0, 0, 32, 32 });
	renderSysTest.update();
	game->render();
	game->delay(500);
	TestChar testGO = TestChar(testRegistry, game);
	testGO.init(SDL_Rect{ 50,50,256,256 }, "Assets/TestChar.png", SDL_Rect{ 64, 96, 32, 32 });
	testGO.disableRandomPos();
	renderSysTest.update();
	game->render();
	game->delay(500);

	// Randomizes position of entities(excluding those with `NoRandomPos` Component.
	RandomPositionSystem randomizer(testRegistry);

	int testX = 0, testY = 0;
	while (game->isRunning()) {
		// If manual control of entities is required, this is the method to do so.
		auto & testGOpos = testRegistry.get<Position>(testGO.getEntityID());
		testGOpos.x = testX++;
		testGOpos.y = testY++;
		// Demo ends here.
		framestart = SDL_GetTicks();
		game->handleEvents();
		game->clear();
		randomizer.update();
		renderSysTest.update(); // Test again.
		game->render();
		game->update();
		int frametime = SDL_GetTicks() - framestart;

		if (framedelay > frametime)
			game->delay(framedelay - frametime);
	}
	game->destroy();
	Game::exit();
	return 0;
}
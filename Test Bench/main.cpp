#include "Framework.h"
#include <ctime>

#include "GameObjectTest/TestGameObject.h"
#include "GameObjectTest/RandomizerSystem.h"

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

	game = new Game(std::nothrow, 800, 600);
	try {
		game->create("Bloom Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
	catch (Exception & e) {
		std::cerr << e.what() << std::endl;
	}
	srand(static_cast<uint32_t>(time(0)));
	SDL_Color rand_color = { static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255),
		static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255) };
	game->setColor(rand_color);
	game->clear();
	game->render();

	// Test Game Object
	entt::DefaultRegistry test_registry;
	bloom::systems::RenderSystem render_sys_test(test_registry);
	game->textures.load("Assets/OverworldTestSpritesheet.png", SDL_Color{ 64, 176, 104, 113 });
	game->textures.load("Assets/TestChar.png", SDL_Color{ 144,168,0,0 });
	TestChar test_sprite = TestChar(test_registry, game);
	test_sprite.init(SDL_Rect{ 0,0,128,128 }, "Assets/OverworldTestSpritesheet.png", SDL_Rect{ 0,0,32,32 });
	render_sys_test.update();
	game->render();
	game->delay(500);
	TestChar test_sprite2 = TestChar(test_registry, game);
	test_sprite2.init(SDL_Rect{ 128,0,128,128 }, "Assets/TestChar.png", SDL_Rect{ 0, 0, 32, 32 });
	render_sys_test.update();
	game->render();
	game->delay(500);
	TestChar test_GO = TestChar(test_registry, game);
	test_GO.init(SDL_Rect{ 50,50,256,256 }, "Assets/TestChar.png", SDL_Rect{ 64, 96, 32, 32 });
	test_GO.disableRandomPos();
	render_sys_test.update();
	game->render();
	game->delay(500);

	// Randomizes position of entities(excluding those with `NoRandomPos` Component.
	RandomPositionSystem randomizer(test_registry);

	int test_x = 0, test_y = 0;
	while (game->isRunning()) {
		// If manual control of entities is required, this is the method to do so.
		auto & test_GO_pos = test_registry.get<Position>(test_GO.getEntityID());
		test_GO_pos.x = test_x++;
		test_GO_pos.y = test_y++;
		// Demo ends here.
		framestart = SDL_GetTicks();
		game->handleEvents();
		game->clear();
		randomizer.update();
		render_sys_test.update(); // Test again.
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
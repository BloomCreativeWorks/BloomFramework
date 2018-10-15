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
		Game::Init();
	}
	catch (Exception & e) {
		std::cerr << e.what() << std::endl;
		system("pause");
		exit(-1);
	}

	game = new Game(std::nothrow, 800, 600);
	try {
		game->Create("Bloom Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
	catch (Exception & e) {
		std::cerr << e.what() << std::endl;
	}
	srand(static_cast<uint32_t>(time(0)));
	SDL_Color rand_color = { static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255),
		static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255) };
	game->set_color(rand_color);
	game->Clear();
	game->Render();

	// Test Game Object
	entt::DefaultRegistry test_registry;
	bloom::systems::RenderSystem render_sys_test(test_registry);
	game->textures.Load("Assets/OverworldTestSpritesheet.png", SDL_Color{ 64, 176, 104, 113 });
	game->textures.Load("Assets/TestChar.png", SDL_Color{ 144,168,0,0 });
	TestChar test_sprite = TestChar(test_registry, game);
	test_sprite.Init(SDL_Rect{ 0,0,128,128 }, "Assets/OverworldTestSpritesheet.png", SDL_Rect{ 0,0,32,32 });
	render_sys_test.Update();
	game->Render();
	game->Delay(500);
	TestChar test_sprite2 = TestChar(test_registry, game);
	test_sprite2.Init(SDL_Rect{ 128,0,128,128 }, "Assets/TestChar.png", SDL_Rect{ 0, 0, 32, 32 });
	render_sys_test.Update();
	game->Render();
	game->Delay(500);
	TestChar test_GO = TestChar(test_registry, game);
	test_GO.Init(SDL_Rect{ 50,50,256,256 }, "Assets/TestChar.png", SDL_Rect{ 64, 96, 32, 32 });
	test_GO.DisableRandomPos();
	render_sys_test.Update();
	game->Render();
	game->Delay(500);

	// Randomizes position of entities(excluding those with `NoRandomPos` Component.
	RandomPositionSystem randomizer(test_registry);

	int test_x = 0, test_y = 0;
	while (game->IsRunning()) {
		// If manual control of entities is required, this is the method to do so.
		auto & test_GO_pos = test_registry.get<Position>(test_GO.entity_ID());
		test_GO_pos.x = test_x++;
		test_GO_pos.y = test_y++;
		// Demo ends here.
		framestart = SDL_GetTicks();
		game->HandleEvents();
		game->Clear();
		randomizer.Update();
		render_sys_test.Update(); // Test again.
		game->Render();
		game->Update();
		int frametime = SDL_GetTicks() - framestart;

		if (framedelay > frametime)
			game->Delay(framedelay - frametime);
	}
	game->Destroy();
	Game::Exit();
	return 0;
}
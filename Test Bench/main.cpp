#include "Framework.h"
#include <ctime>
#include <Windows.h>

#include "GameObjectTest/TestGameObject.h"
#include "GameObjectTest/RandomizerSystem.h"
#include "getExePath.h"

using namespace bloom;
using bloom::components::Position;
using Font = bloom::graphics::Font;

Game* game = nullptr;

int main() {
	SetConsoleCP(CP_UTF8); SetConsoleOutputCP(CP_UTF8);

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

	namespace fs = std::filesystem;

	fs::path workingDir = fs::path(getExePath());
	fs::path assetsDir = L"data\\Assets";
	fs::path fontsDir = L"data\\Fonts";

	if (!std::filesystem::exists(workingDir / assetsDir))
		throw bloom::Exception("Required assets can't be found.");

	fs::path spriteSheetPath = workingDir / assetsDir / "OverworldTestSpritesheet.png";
	fs::path testCharPath = workingDir / assetsDir / "TestChar.png";
	fs::path fontPath = workingDir / fontsDir / "Fira Code.ttf";

	std::shared_ptr<Font> testFont = std::make_shared<Font>(fontPath, 20,0);
	SDL_Renderer * renderer = game->getRenderer();
	// Test SpriteText(NFont)
	bloom::graphics::SpriteText testText(renderer, testFont); // Must be freed or destroyed before TTF_Quit().
	testText.render(std::nullopt, SDL_Rect{ 0,0, 600, 200 });
	game->render();
	game->delay(500);

	// Test Game Object
	entt::DefaultRegistry testRegistry;
	bloom::systems::RenderSystem renderSysTest(testRegistry);
	game->textures.load(spriteSheetPath, SDL_Color{ 64, 176, 104, 113 });
	game->textures.load(testCharPath, SDL_Color{ 144,168,0,0 });
	TestChar testSprite = TestChar(testRegistry, game);
	testSprite.init(SDL_Rect{ 0,0,128,128 }, spriteSheetPath, SDL_Rect{ 0,0,32,32 });
	renderSysTest.update();
	game->render();
	game->delay(500);
	TestChar testSprite2 = TestChar(testRegistry, game);
	testSprite2.init(SDL_Rect{ 128,0,128,128 }, testCharPath, SDL_Rect{ 0, 0, 32, 32 });
	renderSysTest.update();
	game->render();
	game->delay(500);
	TestChar testGO = TestChar(testRegistry, game);
	testGO.init(SDL_Rect{ 50,50,256,256 }, testCharPath, SDL_Rect{ 64, 96, 32, 32 });
	testGO.disableRandomPos();
	renderSysTest.update();
	game->render();
	game->delay(500);

	// Randomizes position of entities(excluding those with `NoRandomPos` Component.
	RandomPositionSystem randomizer(testRegistry);

	// Test SpriteText2
	std::string deltaTimeText = "Delta time: 0ms";

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
		testText.text = deltaTimeText;
		testText.render(std::nullopt, SDL_Rect{ 0,0, 600, 200 });
		game->render();
		deltaTimeText = "Delta time: " + std::to_string(game->timer.split()) + "ms";
		game->update();
		int frametime = SDL_GetTicks() - framestart;

		if (framedelay > frametime)
			game->delay(framedelay - frametime);
	}
	game->destroy();
	Game::exit();
	return 0;
}
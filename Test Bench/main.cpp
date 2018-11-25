#include "Framework.h"
#include <ctime>
#include <Windows.h>

#include "GameObjectTest/TestGameObject.h"
#include "GameObjectTest/RandomizerSystem.h"
#include "getExePath.h"
#include "TestScene.h"

using namespace bloom;

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

	game = new Game(std::nothrow, 800, 600, SDL_WINDOW_RESIZABLE);
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

	if (!std::filesystem::exists(workingDir / assetsDir))
		throw bloom::Exception("Required assets can't be found.");

	fs::path spriteSheetPath = workingDir / assetsDir / "OverworldTestSpritesheet.png";
	fs::path testCharPath = workingDir / assetsDir / "TestChar.png";
	game->textures.load(spriteSheetPath, SDL_Color{ 64, 176, 104, 113 });
	game->textures.load(testCharPath, SDL_Color{ 144,168,0,0 });
	game->sceneManager.changeScene(std::make_shared<TestScene>(game->sceneManager));

	while (game->isRunning()) {
		framestart = SDL_GetTicks();
		game->handleEvents();
		game->clear();
		game->update();
		game->render();
		int frametime = SDL_GetTicks() - framestart;

		if (framedelay > frametime)
			game->delay(framedelay - frametime);
	}

	game->destroy();
	Game::exit();
	return 0;
}
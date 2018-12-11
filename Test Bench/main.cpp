#include <iostream>
#include <ctime>
#include <Windows.h>
#include <thread>
#include <chrono>
#undef min
#undef max

#include "Framework.h"

#include "GameObjectTest/TestGameObject.h"
#include "GameObjectTest/RandomizerSystem.h"
#include "getExePath.h"

using namespace bloom;
using namespace bloom::audio;
using namespace std::chrono_literals;
using bloom::components::Position;
using bloom::components::Size;


std::shared_ptr<Game> game{ nullptr };

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

void test_player(const std::filesystem::path& musicPath, const std::filesystem::path& soundsPath) {
	//MusicTrack track1{ musicPath / L"music_007.mp3" };
	//track1.stop();

	music.push(musicPath / L"music_001.mp3");
	music.push(musicPath / L"music_002.mp3");
	music.push(musicPath / L"music_003.mp3");
	music.push(musicPath / L"music_003.mp3", 1, 200, true);
	music.push(musicPath / L"music_004.mp3");
	music.push(musicPath / L"music_005.mp3");
	//music.push(musicPath / L"music_006.mp3");
	//music.push(musicPath / L"music_007.mp3");

	sounds.add(soundsPath / L"sound_001.wav"); //0
	sounds.add(soundsPath / L"sound_002.wav"); //1

	sounds[0]->play();
	std::this_thread::sleep_for(3s);

	while (!music.queue.tryActivate())
		std::this_thread::sleep_for(1s);
	music.queue.play();
}

void test_drawer(const std::filesystem::path& assetsPath) {
	const int fps = 60;
	const int framedelay = (1000 / fps);

	//Uint32 framestart;
	Uint32 framestart;

	game = std::make_unique<Game>(WINDOW_WIDTH, WINDOW_HEIGHT);
	try {
		game->create("Bloom Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
	catch (Exception& e) {
		std::cerr << e.what() << std::endl;
	}

	srand(static_cast<uint32_t>(time(0)));
	SDL_Color randColor{ static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255),
	static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255) };
	game->setColor(randColor);
	game->clear();
	game->render();

	if (!std::filesystem::exists(assetsPath))
		throw bloom::Exception("Required assets can't be found.");

	std::filesystem::path spriteSheetPath{ assetsPath / L"OverworldTestSpritesheet.png" };
	std::filesystem::path testCharPath{ assetsPath / L"TestChar.png" };

	// Test Game Object
	entt::DefaultRegistry testRegistry;
	bloom::systems::RenderSystem renderSysTest{ testRegistry };
	game->textures.load(spriteSheetPath, SDL_Color{ 64, 176, 104, 113 });
	game->textures.load(testCharPath, SDL_Color{ 144,168,0,0 });
	TestChar testSprite{ testRegistry, *game };
	testSprite.init(SDL_Rect{ 0,0,128,128 }, spriteSheetPath, SDL_Rect{ 0,0,32,32 });
	renderSysTest.update();
	game->render();
	TestChar testSprite2{ testRegistry, *game };
	testSprite2.init(SDL_Rect{ 128,0,128,128 }, testCharPath, SDL_Rect{ 0, 0, 32, 32 });
	renderSysTest.update();
	game->render();
	TestChar testGO{ testRegistry, *game };
	testGO.init(SDL_Rect{ 50,50,256,256 }, testCharPath, SDL_Rect{ 64, 96, 32, 32 });
	testGO.disableRandomPos();
	renderSysTest.update();
	game->render();

	// Randomizes position of entities(excluding those with `NoRandomPos` Component.
	RandomPositionSystem randomizer{ testRegistry };


	// If manual control of entities is required, this is the method to do so.
	auto& testGOpos{ testRegistry.get<Position>(testGO.getEntityID()) };

	auto& testGOsize = testRegistry.get<Size>(testGO.getEntityID());
	int testX = -testGOsize.w, testY = -testGOsize.h;
	const SDL_Rect randomizer_frame{ WINDOW_WIDTH / 2 - 128 - 64, WINDOW_HEIGHT / 2 - 128 - 64, 256, 256 };

	while (game->isRunning()) {
		testGOpos.x = testX += 3;
		testGOpos.y = testY += 3;
		if (testX >= WINDOW_WIDTH)	testX = -testGOsize.w;
		if (testY >= WINDOW_HEIGHT)	testY = -testGOsize.h;
		// Demo ends here.
		framestart = SDL_GetTicks();
		game->handleEvents();
		game->clear();
		randomizer.update(randomizer_frame);
		renderSysTest.update(); // Test again.
		game->render();
		//game->update();

		int frametime = SDL_GetTicks() - framestart;

		if (framedelay > frametime) {
			game->delay(framedelay - frametime);
		}
	}
	game->destroy();
}


int main() {
	SetConsoleCP(CP_UTF8); SetConsoleOutputCP(CP_UTF8);

	try {
		Game::init();
	}
	catch (Exception& e) {
		std::cerr << e.what() << std::endl;
		abort();
	}
	
	namespace fs = std::filesystem;
	fs::path dataDir{ fs::path(getExePath()) / L"data" };
	fs::path assetsPath{ dataDir / L"Assets" };
	fs::path musicPath{ dataDir / L"Music" };
	fs::path soundsPath{ dataDir / L"Sounds" };

	std::thread player_thread{ test_player, musicPath, soundsPath };
	std::thread drawer_thread{ test_drawer, assetsPath };

	player_thread.join();
	drawer_thread.join();
	music.clear();
	sounds[1]->play();
	std::this_thread::sleep_for(3s);
	sounds.clear();

	return 0;
}
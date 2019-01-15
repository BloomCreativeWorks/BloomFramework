#include "Framework.h"
#include <ctime>
#include <Windows.h>

#include <thread>
#include <chrono>

#include "GameObjectTest/TestGameObject.h"
#include "GameObjectTest/RandomizerSystem.h"
#include "GameObjectTest/TestAnimatedGameObject.h"
#include "GameObjectTest/AnimationChangerSystem.h"
#include "getExePath.h"
#include "TestScene.h"

using namespace bloom;
using namespace bloom::audio;
using namespace std::chrono_literals;

Game* game = nullptr;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

inline int rstep(int n) {
	return (rand() % n + 1);
}

void test_player(const std::filesystem::path& musicPath, const std::filesystem::path& soundsPath) {
	//MusicTrack track1{ musicPath / L"music_007.mp3" };

	music.push(musicPath / L"music_001.mp3");
	music.push(musicPath / L"music_002.mp3");
	music.push(musicPath / L"music_003.mp3");
	music.push(musicPath / L"music_003.mp3", 1, true, 200);
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

	game = new Game(WINDOW_WIDTH, WINDOW_HEIGHT);
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

	if (!std::filesystem::exists(assetsPath))
		throw bloom::Exception("Required assets can't be found.");

	std::filesystem::path spriteSheetPath = assetsPath / L"OverworldTestSpritesheet.png";
	std::filesystem::path testCharPath = assetsPath / L"TestChar.png";
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

		if (framedelay > frametime) {
			game->delay(framedelay - frametime);
		}
	}

	game->destroy();
}

int main() {
	SetConsoleCP(CP_UTF8); SetConsoleOutputCP(CP_UTF8);

	try {
		Game::initialize();
	}
	catch (Exception & e) {
		std::cerr << e.what() << std::endl;
		system("pause");
		exit(-1);
	}

	namespace fs = std::filesystem;
	fs::path dataDir = fs::path(getExePath()) / L"data";
	fs::path assetsPath = dataDir / L"Assets";
	fs::path musicPath = dataDir / L"Music";
	fs::path soundsPath = dataDir / L"Sounds";

	std::thread drawer_thread{ test_drawer, assetsPath };
	std::thread player_thread{ test_player, musicPath, soundsPath };

	drawer_thread.join();
	player_thread.join();
	music.clear();
	sounds[1]->play();
	std::this_thread::sleep_for(3s);
	sounds.clear();

	return 0;
}
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
using namespace bloom::graphics;

Game* game = nullptr;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

inline int rstep(int n) {
	return (rand() % n + 1);
}

namespace fs = std::filesystem;

void test_player(const std::filesystem::path& dataDir) {
	fs::path musicPath = dataDir / L"Music";
	fs::path soundsPath = dataDir / L"Sounds";

	//MusicTrack track1{ musicPath / L"music_007.mp3" };
	music.queue.setVolume(15.0);
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

void test_drawer(const std::filesystem::path& dataDir) {
	const int framedelay = 1000 / 60;

	Uint32 framestart;

	game = new Game(WINDOW_WIDTH, WINDOW_HEIGHT);
	try {
		game->create("Bloom Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
	catch (Exception & e) {
		std::cerr << e.what() << std::endl;
	}
	srand(static_cast<uint32_t>(time(nullptr)));
	SDL_Color randColor = { static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255),
		static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255) };
	game->setColor(randColor);
	game->clear();
	game->render();

	fs::path assetsPath = dataDir / L"Assets";
	fs::path fontsPath = dataDir / L"Fonts";

	if (!std::filesystem::exists(assetsPath))
		throw bloom::Exception("Required assets can't be found.");


	fs::path spriteSheetPath = assetsPath / "OverworldTestSpritesheet.png";
	fs::path testCharPath = assetsPath / "TestChar.png";
	fs::path fontPath = fontsPath / "Fira Code.ttf";
	game->textures.load(spriteSheetPath, SDL_Color{ 64, 176, 104, 113 });
	game->textures.load(testCharPath, SDL_Color{ 144,168,0,0 });
	game->sceneManager.changeScene(std::make_shared<TestScene>(game->sceneManager));

	FontStore fonts;
	constexpr size_t UI_font = 0;
	fonts.load(fontPath, UI_font);

	auto renderer = game->getRenderer();
	// Test SpriteText(NFont)
	bloom::graphics::SpriteText testText(renderer, fonts[UI_font], "Hello, World!");
	{
		auto newStyle = testText.getStyle();
		newStyle.blendingMode = TextStyle::BlendingMode::blended;

		SDL_Color col, curcol = game->getColor();
		std::clog << "current_color: r: " << +curcol.r << ", g: " << +curcol.g << ", b: " << +curcol.b << std::endl;
		if (curcol.r + curcol.g + curcol.b >= 384) {
			col = { 0, 0, 0, 0 };
		}
		else {
			col = { 255, 255, 255, 0 };
		}
		newStyle.foregroundColor = col;

		testText.setStyle(newStyle);
	}
	testText.render(std::nullopt, SDL_Point{ 300, 250 });
	game->render();
	game->delay(500);

	std::string deltaTimeText{ "fps: " };

	while (game->isRunning()) {
		framestart = SDL_GetTicks();
		auto dt = game->timer.split();
		game->handleEvents();
		game->clear();
		game->update();
		auto fps = 1000.0 / dt;
		deltaTimeText.erase(5);
		deltaTimeText += std::to_string(fps);
		testText.setText(deltaTimeText);
		testText.render(std::nullopt, SDL_Point{ 0, 0 });
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
		Game::initialize();
	}
	catch (Exception & e) {
		std::cerr << e.what() << std::endl;
		system("pause");
		exit(-1);
	}

	fs::path dataDir = fs::path(getExePath()) / L"data";

	std::thread drawer_thread{ test_drawer, dataDir };
	std::thread player_thread{ test_player, dataDir };

	drawer_thread.join();
	player_thread.join();
	music.clear();
	sounds[1]->play();
	std::this_thread::sleep_for(3s);
	sounds.clear();

	return 0;
}
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

using namespace bloom;
using namespace bloom::audio;
using namespace std::chrono_literals;
using bloom::components::Position;
using namespace bloom::graphics;
using bloom::components::Size;

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

	// Test Game Object
	entt::DefaultRegistry testRegistry;
	AnimationChangerSystem animChangerTest(testRegistry);
	bloom::systems::AnimationSystem animSysTest(testRegistry);
	bloom::systems::RenderSystem renderSysTest(testRegistry);
	//game->textures.load(spriteSheetPath, SDL_Color{ 64, 176, 104, 113 });
	//game->textures.load(testCharPath, SDL_Color{ 144,168,0,0 });
	TestChar testSprite = TestChar(testRegistry, game);
	testSprite.init(SDL_Rect{ 0, 0, 128, 128 }, spriteSheetPath, SDL_Rect{ 0,0,32,32 });
	renderSysTest.update();
	game->render();
	TestChar testSprite2 = TestChar(testRegistry, game);
	testSprite2.init(SDL_Rect{ 128, 0, 128, 128 }, testCharPath, SDL_Rect{ 0, 0, 32, 32 });
	renderSysTest.update();
	game->render();
	TestChar testGO = TestChar(testRegistry, game);
	testGO.init(SDL_Rect{ 50, 50, 192, 192 }, testCharPath, SDL_Rect{ 64, 96, 32, 32 });
	testGO.disableRandomPos();
	renderSysTest.update();
	game->render();

	// Randomizes position of entities(excluding those with `NoRandomPos` Component.
	RandomPositionSystem randomizer(testRegistry);
	TestAnimChar testAnim(testRegistry, game);
	testAnim.init(testCharPath);

	// Test SpriteText2
	std::string deltaTimeText{ "fps: " };
	

	// If manual control of entities is required, this is the method to do so.
	auto & testGOpos = testRegistry.get<Position>(testGO.getEntityID());

	auto & testGOsize = testRegistry.get<Size>(testGO.getEntityID());
	int testX = rstep(10), testY = rstep(10);


	while (game->isRunning()) {
		testGOpos.x += testX;
		testGOpos.y += testY;
		if (testGOpos.x >= WINDOW_WIDTH) {
			testGOpos.x = -testGOsize.w; testX = rstep(10); testY = rstep(10);
		}
		if (testGOpos.y >= WINDOW_HEIGHT) {
			testGOpos.y = -testGOsize.h; testX = rstep(10); testY = rstep(10);
		}
		// Demo ends here.
		framestart = SDL_GetTicks();
		auto dt = game->timer.lap();
		game->handleEvents();
		game->clear();
		animChangerTest.update();
		animSysTest.update(dt);
		randomizer.update(WINDOW_WIDTH - 128, WINDOW_HEIGHT - 128);
		renderSysTest.update(); // Test again.
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

int main(int argc, char* argv[]) {
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
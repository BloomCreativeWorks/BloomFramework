#include "Framework.h"
#include <ctime>
#include <Windows.h>

#include <thread>
#include <chrono>

#include "GameObjectTest/TestGameObject.h"
#include "GameObjectTest/RandomizerSystem.h"
#include "GameObjectTest/TestAnimatedGameObject.h"
#include "GameObjectTest/AnimationChangerSystem.h"
#include "GameObjectTest/TestControllableObject.h"
#include "getExePath.h"

using namespace bloom;
using namespace bloom::audio;
using namespace std::chrono_literals;
using bloom::components::Position;
using bloom::components::Size;


Game* game = nullptr;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

inline int rstep(int n) {
	return (rand() % n + 1);
}

void test_player(const std::filesystem::path & musicPath, const std::filesystem::path & soundsPath) {
	//MusicTrack track1{ musicPath / L"music_007.mp3" };
	music.queue.setVolume(0.0);
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

void test_drawer(const std::filesystem::path & assetsPath) {
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

	srand(static_cast<uint32_t>(time(nullptr)));
	SDL_Color randColor = { static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255),
	static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255) };
	game->setColor(randColor);
	game->clear();
	game->render();

	if (!std::filesystem::exists(assetsPath))
		throw bloom::Exception("Required assets can't be found.");

	std::filesystem::path spriteSheetPath = assetsPath / L"OverworldTestSpritesheet.png";
	std::filesystem::path testCharPath = assetsPath / L"TestChar.png";
	std::filesystem::path testCursorPath = assetsPath / "testCursor.png";
	std::filesystem::path testBoxPath = assetsPath / "Box.png";

	// Test Game Object
	entt::DefaultRegistry testRegistry;
	AnimationChangerSystem animChangerTest(testRegistry);
	bloom::systems::AnimationSystem animSysTest(testRegistry);
	bloom::systems::RenderSystem renderSysTest(testRegistry);
	game->textures.load(spriteSheetPath, SDL_Color{ 64, 176, 104, 113 });
	game->textures.load(testCharPath, SDL_Color{ 144,168,0,0 });
	game->textures.load(testCursorPath);
	TestChar cursor = TestChar(testRegistry, game);
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

	cursor.init(SDL_Rect{ 0,0,39,55 }, testCursorPath);
	cursor.disableRandomPos();
	TestAnimChar testAnim(testRegistry, game);
	testAnim.init(testCharPath);
	TestMovableObject testMovable(testRegistry, game);
	testMovable.init(SDL_Rect{ 0,0, 50, 50 }, testBoxPath);


	// If manual control of entities is required, this is the method to do so.
	auto& testGOpos = testRegistry.get<Position>(testGO.getEntityID());

	auto& testGOsize = testRegistry.get<Size>(testGO.getEntityID());
	int testX = rstep(10), testY = rstep(10);

	auto& cursorPos = testRegistry.get<Position>(cursor.getEntityID());

	while (game->isRunning()) {
		testGOpos.x += testX;
		testGOpos.y += testY;

		cursorPos.x = game->input.mouse.getX();
		cursorPos.y = game->input.mouse.getY();
		std::cout << game->input.keyboard.getPrintable();

		// vvv	wasUp and wasDown testing	vvv
		if (game->input.keyboard.wasDown(input::KeyboardKey::KEY_0))
			std::cout << std::endl << "zero was pressed" << std::endl;
		if (game->input.keyboard.wasUp(input::KeyboardKey::KEY_0))
			std::cout << std::endl << "zero was released" << std::endl;
		if (game->input.keyboard.wasDown(input::KeyboardKey::KEY_CAPSLOCK))
			std::cout << std::endl << "caps lock was pressed" << std::endl;
		if (game->input.keyboard.wasUp(input::KeyboardKey::KEY_CAPSLOCK))
			std::cout << std::endl << "caps lock was released" << std::endl;
		if (game->input.mouse.wasDown(input::MouseButton::MOUSE_LEFT))
			std::cout << std::endl << "left mouse button was pressed" << std::endl;
		if (game->input.mouse.wasUp(input::MouseButton::MOUSE_LEFT))
			std::cout << std::endl << "left mouse button was released" << std::endl;
		// ^^^	wasUp and wasDown testing	^^^

		// vvv	isPressed testing	vvv
		int xOffset = 0, yOffset = 0;
		if (game->input.keyboard.isPressed(input::KeyboardKey::KEY_W) || game->input.keyboard.isPressed(input::KeyboardKey::KEY_UP))
			yOffset -= 5;
		if (game->input.keyboard.isPressed(input::KeyboardKey::KEY_S) || game->input.keyboard.isPressed(input::KeyboardKey::KEY_DOWN))
			yOffset += 5;
		if (game->input.keyboard.isPressed(input::KeyboardKey::KEY_A) || game->input.keyboard.isPressed(input::KeyboardKey::KEY_LEFT))
			xOffset -= 5;
		if (game->input.keyboard.isPressed(input::KeyboardKey::KEY_D) || game->input.keyboard.isPressed(input::KeyboardKey::KEY_RIGHT))
			xOffset += 5;
		// ^^^	isPressed testing	^^^

		testMovable.updatePos(xOffset, yOffset);


		if (testGOpos.x >= WINDOW_WIDTH) {
			testGOpos.x = -testGOsize.w; testX = rstep(10); testY = rstep(10);
		}
		if (testGOpos.y >= WINDOW_HEIGHT) {
			testGOpos.y = -testGOsize.h; testX = rstep(10); testY = rstep(10);
		}
		// Demo ends here.
		framestart = SDL_GetTicks();
		game->handleEvents();
		game->clear();
		animChangerTest.update();
		animSysTest.update(game->timer.lap());
		randomizer.update(WINDOW_WIDTH - 128, WINDOW_HEIGHT - 128);
		renderSysTest.update(); // Test again.
		game->render();
		//game->update();

		int frametime = SDL_GetTicks() - framestart;

		if (framedelay > frametime) {
			game->delay(framedelay - frametime);
		}
	}
	std::cout << std::endl;
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
#include "Framework.h"
#include <ctime>
#include <Windows.h>

#include <thread>
#include <chrono>

#include "GameObjectTest/TestGameObject.h"
#include "GameObjectTest/RandomizerSystem.h"
#include "getExePath.h"

using namespace bloom;
using namespace bloom::audio;
using bloom::components::Position;
using bloom::components::Size;


Game* game = nullptr;

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

void player(const std::filesystem::path& musicPath, const std::filesystem::path& soundsPath) {

	//MusicTrack track1{ musicPath / L"sample_1.mp3" };

	//music.push("Audio/sample_1.mp3", 1, true, 3000, 3000);
	//music.push("Audio/sample_2.mp3", 2);
	music.push(musicPath / L"sample_3.mp3", 1, false, 5000);
	music.push(musicPath / L"sample_4.mp3", 1, false, 10000);
	music.push(musicPath / L"sample_5.mp3");
	music.push(musicPath / L"sample_6.mp3", 1);
	music.push(musicPath / L"sample_7.mp3", 1, true);
	//music.push(musicPath / L"sample_6.mp3");
	music.push(musicPath / L"sample_8.mp3");

	sounds.add(soundsPath / L"Sound_04684.wav"); //0
	sounds.add(soundsPath / L"Sound_04685.wav"); //1
	//sounds.add(soundsPath / L"Sound_11989.wav"); //2
	//sounds.add(soundsPath / L"Sound_11998.wav"); //3
	//sounds.add(soundsPath / L"Sound_12000.wav"); //4
	//sounds.add(soundsPath / L"Sound_12011.wav"); //5
	//sounds.add(soundsPath / L"Sound_12020.wav"); //6

	sounds[0]->play();
	std::this_thread::sleep_for(std::chrono::milliseconds(2500));

	while (!music.queue.tryActivate())
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	music.queue.play();
}


int main() {
	SetConsoleCP(CP_UTF8); SetConsoleOutputCP(CP_UTF8);

	const int fps = 60;
	const int framedelay = (1000 / fps);

	//Uint32 framestart;
	Uint32 framestart;
	try {
		Game::initialize();
	}
	catch (Exception & e) {
		std::cerr << e.what() << std::endl;
		system("pause");
		exit(-1);
	}
	game = new Game(WINDOW_WIDTH, WINDOW_HEIGHT);
	try {
		game->create("Bloom Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
	catch (Exception & e) {
		std::cerr << e.what() << std::endl;
	}

	namespace fs = std::filesystem;

	fs::path dataPath = L"data";
	fs::path musicPath = dataPath / L"Music";
	fs::path soundsPath = dataPath / L"Sounds";

	std::thread player_thread{ player, musicPath, soundsPath };

	srand(static_cast<uint32_t>(time(0)));
	SDL_Color randColor = { static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255),
	static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255) };
	game->setColor(randColor);
	game->clear();
	game->render();

	fs::path workingDir = fs::path(getExePath());
	fs::path assetsDir = dataPath / L"Assets";

	if (!std::filesystem::exists(workingDir / assetsDir))
		throw bloom::Exception("Required assets can't be found.");

	fs::path spriteSheetPath = workingDir / assetsDir / L"OverworldTestSpritesheet.png";
	fs::path testCharPath = workingDir / assetsDir / L"TestChar.png";

	//std::clog << "Channels " << Mix_AllocateChannels(-1) << std::endl;

	// Test Game Object
	entt::DefaultRegistry testRegistry;
	bloom::systems::RenderSystem renderSysTest(testRegistry);
	game->textures.load(spriteSheetPath, SDL_Color{ 64, 176, 104, 113 });
	game->textures.load(testCharPath, SDL_Color{ 144,168,0,0 });
	TestChar testSprite = TestChar(testRegistry, game);
	testSprite.init(SDL_Rect{ 0,0,128,128 }, spriteSheetPath, SDL_Rect{ 0,0,32,32 });
	renderSysTest.update();
	game->render();
	TestChar testSprite2 = TestChar(testRegistry, game);
	testSprite2.init(SDL_Rect{ 128,0,128,128 }, testCharPath, SDL_Rect{ 0, 0, 32, 32 });
	renderSysTest.update();
	game->render();
	TestChar testGO = TestChar(testRegistry, game);
	testGO.init(SDL_Rect{ 50,50,256,256 }, testCharPath, SDL_Rect{ 64, 96, 32, 32 });
	testGO.disableRandomPos();
	renderSysTest.update();
	game->render();

	// Randomizes position of entities(excluding those with `NoRandomPos` Component.
	RandomPositionSystem randomizer(testRegistry);


	// If manual control of entities is required, this is the method to do so.
	auto & testGOpos = testRegistry.get<Position>(testGO.getEntityID());

	auto & testGOsize = testRegistry.get<Size>(testGO.getEntityID());
	int testX = -testGOsize.w, testY = -testGOsize.h;

	while (game->isRunning()) {
		testGOpos.x = testX += 3;
		testGOpos.y = testY += 3;
		if (testX >= WINDOW_WIDTH)	testX = -testGOsize.w;
		if (testY >= WINDOW_HEIGHT)	testY = -testGOsize.h;
		// Demo ends here.
		framestart = SDL_GetTicks();
		game->handleEvents();
		game->clear();
		randomizer.update(WINDOW_WIDTH - 128, WINDOW_HEIGHT - 128);
		renderSysTest.update(); // Test again.
		game->render();
		//game->update();

		int frametime = SDL_GetTicks() - framestart;

		if (framedelay > frametime) {
			game->delay(framedelay - frametime);
		}
	}
	game->destroy();
	player_thread.join();
	music.clear();
	sounds[1]->play();
	game->delay(2500);
	sounds.clear();

	return 0;
}
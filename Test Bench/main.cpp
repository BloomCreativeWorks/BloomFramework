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
using namespace std::chrono_literals;
using bloom::components::Position;
using namespace bloom::graphics;
using bloom::components::Size;

Game* game = nullptr;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

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

	namespace fs = std::filesystem;

	fs::path workingDir = fs::path(getExePath());
	fs::path assetsDir = L"data\\Assets";
	fs::path fontsDir = L"data\\Fonts";

	if (!std::filesystem::exists(workingDir / assetsDir))
		throw bloom::Exception("Required assets can't be found.");

	fs::path spriteSheetPath = workingDir / assetsDir / "OverworldTestSpritesheet.png";
	fs::path testCharPath = workingDir / assetsDir / "TestChar.png";
	fs::path fontPath = workingDir / fontsDir / "Fira Code.ttf";

	FontStore fonts;
	constexpr size_t UI_font = 0;
	fonts.load(fontPath, UI_font, defaultFontStyle);

	SDL_Renderer * renderer = game->getRenderer();
	// Test SpriteText(NFont)
	bloom::graphics::SpriteText testText(renderer, fonts[UI_font], "Hello, World!");
	testText.style.blendingMode = testText.style.blended;
	testText.refreshTexture();
	testText.render(std::nullopt, SDL_Point{ 300, 250 });
	game->render();
	game->delay(500);

	// Test Game Object
	entt::DefaultRegistry testRegistry;
	bloom::systems::RenderSystem renderSysTest(testRegistry);
	//game->textures.load(spriteSheetPath, SDL_Color{ 64, 176, 104, 113 });
	//game->textures.load(testCharPath, SDL_Color{ 144,168,0,0 });
	TestChar testSprite = TestChar(testRegistry, game);
	testSprite.init(game->textures.load(spriteSheetPath, SDL_Color{ 64, 176, 104, 113 }), SDL_Rect{ 0,0,128,128 }, SDL_Rect{ 0,0,32,32 });
	renderSysTest.update();
	game->render();
	TestChar testSprite2 = TestChar(testRegistry, game);
	testSprite2.init(game->textures.load(testCharPath, SDL_Color{ 144,168,0,0 }), SDL_Rect{ 128,0,128,128 }, SDL_Rect{ 0, 0, 32, 32 });
	renderSysTest.update();
	game->render();
	TestChar testGO = TestChar(testRegistry, game);
	testGO.init(game->textures.load(testCharPath, SDL_Color{ 144,168,0,0 }), SDL_Rect{ 50,50,256,256 }, SDL_Rect{ 64, 96, 32, 32 });
	testGO.disableRandomPos();
	renderSysTest.update();
	game->render();

	// Randomizes position of entities(excluding those with `NoRandomPos` Component.
	RandomPositionSystem randomizer(testRegistry);

	// Test SpriteText2
	std::string deltaTimeText;
	SDL_Color col, curcol = game->getColor();
	std::clog << "current_color: r: " << +curcol.r << ", g: " << +curcol.g << ", b: " << +curcol.b << std::endl;
	if (curcol.r + curcol.g + curcol.b >= 384) {
		col = { 0, 0, 0, 0 };
	}
	else {
		col = { 255, 255, 255, 0 };
	}
	testText.style.foregroundColor = col;

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
		deltaTimeText = "fps: " + std::to_string(1000.0 / game->timer.lap());
		testText.changeText(deltaTimeText);
		testText.render(std::nullopt, SDL_Point{ 0, 0 });
		game->render();
		//game->update();
		int frametime = SDL_GetTicks() - framestart;

		if (framedelay > frametime) {
			game->delay(framedelay - frametime);
		}
	}
	game->destroy();
	fonts.unload(UI_font);
	testText.~SpriteText();
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
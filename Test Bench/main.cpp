#include "Framework.h"
#include <ctime>

#include "GameObjectTest/TestGameObject.h"
#include "GameObjectTest/RandomizerSystem.h"

using namespace bloom;
using namespace bloom::audio;


Game* game = nullptr;

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;


int main() {
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
	music.queue.add(music.store.load("Audio/sample_1.mp3"), 1, true);
	music.queue.add(music.store.load("Audio/sample_2.mp3"), 2);
	music.queue.add(music.store.load("Audio/sample_2-full.mp3"));

	//sounds.store.disableAutoChannels(false);
	//sounds.store.manageExtraChannels(5000);
	sounds.players.emplace_back(sounds.store.load("Audio/Sounds/Sound_04684.wav")); //0
	sounds.players.emplace_back(sounds.store.load("Audio/Sounds/Sound_04685.wav")); //1
	sounds.players.emplace_back(sounds.store.load("Audio/Sounds/Sound_11989.wav")); //2
	sounds.players.emplace_back(sounds.store.load("Audio/Sounds/Sound_11998.wav")); //3
	sounds.players.emplace_back(sounds.store.load("Audio/Sounds/Sound_12000.wav")); //4
	sounds.players.emplace_back(sounds.store.load("Audio/Sounds/Sound_12011.wav")); //5
	sounds.players.emplace_back(sounds.store.load("Audio/Sounds/Sound_12020.wav")); //6

	//game->music.load("Audio/sample_2-full.mp3");
	srand(static_cast<uint32_t>(time(0)));
	SDL_Color randColor = { static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255),
	static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255) };
	game->setColor(randColor);
	game->clear();
	game->render();

	sounds.players[0].play();

	auto testPtr = sounds.players[0].chunk();

	std::clog << testPtr.use_count() << std::endl;

	std::clog << sounds.players[0].chunk().use_count() << std::endl;

	std::clog << testPtr.use_count() << std::endl;
	sounds.players[0].play();
	sounds.players[0].play();
	//sounds[2]->play();

	std::clog << "Channels " << Mix_AllocateChannels(-1) << std::endl;

	// Test Game Object
	entt::DefaultRegistry testRegistry;
	bloom::RenderSystem renderSysTest(testRegistry);
	game->textures.load("Assets/OverworldTestSpritesheet.png", SDL_Color{ 64, 176, 104, 113 });
	game->textures.load("Assets/TestChar.png", SDL_Color{ 144,168,0,0 });
	TestChar testSprite = TestChar(testRegistry, game);
	testSprite.init(SDL_Rect{ 0,0,128,128 }, "Assets/OverworldTestSpritesheet.png", SDL_Rect{ 0,0,32,32 });
	renderSysTest.update();
	game->render();
	game->delay(750);
	TestChar testSprite2 = TestChar(testRegistry, game);
	testSprite2.init(SDL_Rect{ 128,0,128,128 }, "Assets/TestChar.png", SDL_Rect{ 0, 0, 32, 32 });
	renderSysTest.update();
	game->render();
	game->delay(750);
	TestChar testGO = TestChar(testRegistry, game);
	testGO.init(SDL_Rect{ 50,50,256,256 }, "Assets/TestChar.png", SDL_Rect{ 64, 96, 32, 32 });
	testGO.disableRandomPos();
	renderSysTest.update();
	game->render();
	game->delay(1000);

	// Randomizes position of entities(excluding those with `NoRandomPos` Component.
	RandomPositionSystem randomizer(testRegistry);

	int testX = 0, testY = 0;
	music.queue.setVolume(64);
	music.queue.setInfinitePlayback(true);
	music.queue.play();
	while (game->isRunning()) {
		// If manual control of entities is required, this is the method to do so.
		auto & testGOpos = testRegistry.get<Position>(testGO.getEntityID());
		testGOpos.x = testX++;
		testGOpos.y = testY++;
		testX %= WINDOW_WIDTH; testY %= WINDOW_HEIGHT;
		// Demo ends here.
		framestart = SDL_GetTicks();
		game->handleEvents();
		game->clear();
		randomizer.update(WINDOW_WIDTH - 128, WINDOW_HEIGHT - 128);
		renderSysTest.update(); // Test again.
		game->render();
		game->update();

		//sounds[0]->play();
		//sounds[1]->play();
		//sounds[2]->play();
		//sounds[3]->play();
		//sounds[4]->play();
		//sounds[5]->play();
		//sounds[6]->play();

		//if (testX % 5 == 0) {
		//	try {
		//		sounds[3]->play();
		//		std::clog << Mix_AllocateChannels(-1) << std::endl;
		//	}
		//	catch (Exception & e) {
		//		std::cerr << e.what() << std::endl;
		//	}
		//}
		int frametime = SDL_GetTicks() - framestart;

		if (framedelay > frametime) {
			game->delay(framedelay - frametime);
		}
	}
	music.clear();
	game->destroy();
	sounds.players[1].play();
	game->delay(2500);
	sounds.clear();
	std::clog << testPtr.use_count() << std::endl;
	std::clog << "Channels " << Mix_AllocateChannels(-1) << std::endl;

	sounds.players.emplace_back(sounds.store.load("Audio/Sounds/Sound_12000.wav")); //4
	sounds.players.emplace_back(sounds.store.load("Audio/Sounds/Sound_12011.wav")); //5
	sounds.players.emplace_back(sounds.store.load("Audio/Sounds/Sound_12020.wav")); //6


	game->delay(2500);

	//sounds.players[2].play();

	game->delay(2500);

	std::clog << "Channels " << Mix_AllocateChannels(-1) << std::endl;
	//Game::exit();
	return 0;
}
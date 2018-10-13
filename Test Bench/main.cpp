#include "Framework.h"
#include <ctime>

#include "GameObjectTest/TestGameObject.h"
#include "GameObjectTest/RandomizerSystem.h"

using namespace bloom;


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

	//sounds.disableAutoChannels(false);
	//sounds.manageExtraChannels(5000);
	std::vector<SoundControl> sound_vector;
	sound_vector.emplace_back(sounds.load("Audio/Sounds/Sound_04684.wav")); //0
	sound_vector.emplace_back(sounds.load("Audio/Sounds/Sound_04685.wav")); //1
	sound_vector.emplace_back(sounds.load("Audio/Sounds/Sound_11989.wav")); //2
	sound_vector.emplace_back(sounds.load("Audio/Sounds/Sound_11998.wav")); //3
	sound_vector.emplace_back(sounds.load("Audio/Sounds/Sound_12000.wav")); //4
	sound_vector.emplace_back(sounds.load("Audio/Sounds/Sound_12011.wav")); //5
	sound_vector.emplace_back(sounds.load("Audio/Sounds/Sound_12020.wav")); //6

	//game->music.load("Audio/sample_2-full.mp3");
	srand(static_cast<uint32_t>(time(0)));
	SDL_Color randColor = { static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255),
	static_cast<Uint8>(rand() % 255), static_cast<Uint8>(rand() % 255) };
	game->setColor(randColor);
	game->clear();
	game->render();

	sound_vector[0].player.play();

	auto testPtr = sound_vector[0].chunk;

	std::clog << sound_vector[0].chunk.use_count() << std::endl;
	sound_vector[0].player.play();
	sound_vector[0].player.play();
	//sound_vector[2]->play();

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

		//sound_vector[0]->play();
		//sound_vector[1]->play();
		//sound_vector[2]->play();
		//sound_vector[3]->play();
		//sound_vector[4]->play();
		//sound_vector[5]->play();
		//sound_vector[6]->play();

		//if (testX % 5 == 0) {
		//	try {
		//		sound_vector[3]->play();
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
	music.queue.clear();
	game->destroy();
	sound_vector[1].player.play();
	game->delay(2500);
	sound_vector.clear();
	sounds.unload_all();
	std::clog << testPtr.use_count() << std::endl;
	//Game::exit();
	return 0;
}
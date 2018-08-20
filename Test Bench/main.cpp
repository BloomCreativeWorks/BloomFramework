#include "framework.h"

int main() {
	BloomFramework::GraphicsWindow myWindow;
	myWindow.setWindowTitle("Graphics Window");
	myWindow.setHeight(337);
	myWindow.setWidth(600);
	if(!myWindow.initWindow()) {
		std::clog << "[ERROR] Failed to initialize window!" << std::endl;
	}
	BloomFramework::TextureStore testTextures(myWindow.gScreenSurface);
	testTextures.loadTexture("Resources/test.bmp", "base");
	testTextures.loadTexture("Resources/up.bmp", "up");
	testTextures.loadTexture("Resources/down.bmp", "down");
	testTextures.loadTexture("Resources/left.bmp", "left");
	testTextures.loadTexture("Resources/right.bmp", "right");
	myWindow.loadMedia(testTextures.getTexture("base"));

	bool quit = false;

	BloomFramework::EventHandler input;
	while(!quit) {
		myWindow.updateWindow();
		//Handle events on queue
		BloomFramework::Events event = input.getInput();
		switch(event) {
			using namespace BloomFramework;
		case Events::quit:
			quit = true;
			break;
		case Events::up:
			if(!myWindow.loadMedia(testTextures.getTexture("up"))) {
				std::clog << "[ERROR] Failed to load image!" << std::endl;
			}
			break;
		case Events::down:
			if(!myWindow.loadMedia(testTextures.getTexture("down"))) {
				std::clog << "[ERROR] Failed to load image!" << std::endl;
			}
			break;
		case Events::left:
			if(!myWindow.loadMedia(testTextures.getTexture("left"))) {
				std::clog << "[ERROR] Failed to load image!" << std::endl;
			}
			break;
		case Events::right:
			if(!myWindow.loadMedia(testTextures.getTexture("right"))) {
				std::clog << "[ERROR] Failed to load image!" << std::endl;
			}
			break;
		}
	}

	myWindow.destroyWindow();
	return 0;
}
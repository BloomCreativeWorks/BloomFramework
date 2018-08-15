#include "framework.h"

int main() {
	BloomFramework::GraphicsWindow myWindow;

	myWindow.setWindowTitle("Graphics Window");
	myWindow.setHeight(337);
	myWindow.setWidth(600);
	if(!myWindow.initWindow()) {
		std::clog << "[ERROR] Failed to initialize window!" << std::endl;
	} else {
		if(!myWindow.loadMedia("Resources/test.bmp")) {
			std::clog << "[ERROR] Failed to load image!" << std::endl;
		}
	}

	bool quit = false;

	BloomFramework::InputHandler input;
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
			if(!myWindow.loadMedia("Resources/up.bmp")) {
				std::clog << "[ERROR] Failed to load image!" << std::endl;
			}
			break;
		case Events::down:
			if(!myWindow.loadMedia("Resources/down.bmp")) {
				std::clog << "[ERROR] Failed to load image!" << std::endl;
			}
			break;
		case Events::left:
			if(!myWindow.loadMedia("Resources/left.bmp")) {
				std::clog << "[ERROR] Failed to load image!" << std::endl;
			}
			break;
		case Events::right:
			if(!myWindow.loadMedia("Resources/right.bmp")) {
				std::clog << "[ERROR] Failed to load image!" << std::endl;
			}
			break;
		}
	}

	myWindow.destroyWindow();

	return 0;
}
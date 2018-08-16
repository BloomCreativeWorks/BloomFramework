#include "../../inc/framework.h"
using namespace BloomFramework;

Events BloomFramework::EventHandler::getInput() {
	//Handle events on queue
	while(SDL_PollEvent(&e) != 0) {
		//User requests quit
		if(e.type == SDL_QUIT) {
			return quit;
		}
		//User presses a key
		else if(e.type == SDL_KEYDOWN) {
			//Select surfaces based on key press
			switch(e.key.keysym.sym) {
			case SDLK_UP:
				return up;
			case SDLK_DOWN:
				return down;
			case SDLK_LEFT:
				return left;
			case SDLK_RIGHT:
				return right;
			default:
				return empty;
			}
		}
		else {
			return empty;
		}
	}
}

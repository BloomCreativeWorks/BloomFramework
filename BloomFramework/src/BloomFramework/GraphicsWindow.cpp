#include "../../inc/framework.h"
bool BloomFramework::GraphicsWindow::initWindow() {
	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::clog << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	} else {
		//Create window
		gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SCREEN_X_POS, SCREEN_Y_POS, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			std::clog << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		} else {
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return true;
}

bool BloomFramework::GraphicsWindow::loadMedia(const std::string &imagePath) {
	//Load splash image
	gImage = SDL_LoadBMP(imagePath.c_str());
	if(gImage == NULL) {
		std::clog << "Unable to load image " << imagePath << "! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	} 
	return true;
}

bool BloomFramework::GraphicsWindow::loadMedia(SDL_Surface* texture) {
	//Load splash image
	gImage = texture;
	return true;
}

void BloomFramework::GraphicsWindow::updateWindow() {
	if(gImage != NULL) {
		//Apply the image
		SDL_BlitSurface(gImage, NULL, gScreenSurface, NULL);
	}
	
	//Update the surface
	SDL_UpdateWindowSurface(gWindow);
}

void BloomFramework::GraphicsWindow::destroyWindow() {
	//Deallocate surface
	SDL_FreeSurface(gImage);
	gImage = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
void BloomFramework::GraphicsWindow::setWindowTitle(const std::string &title) {
	WINDOW_TITLE = title;
}
void BloomFramework::GraphicsWindow::setHeight(int height) {
	if(height <= 0)
		std::clog << "[WARNING] Window height is set to an invalid value" << std::endl;
	SCREEN_HEIGHT = height;
}
void BloomFramework::GraphicsWindow::setWidth(int width) {
	if(width <= 0)
		std::clog << "[WARNING] Window width is set to an invalid value" << std::endl;
	SCREEN_WIDTH = width;
}
void BloomFramework::GraphicsWindow::setXPos(int xPosition) {
	SCREEN_X_POS = xPosition;
}
void BloomFramework::GraphicsWindow::setYPos(int yPosition) {
	SCREEN_Y_POS = yPosition;
}

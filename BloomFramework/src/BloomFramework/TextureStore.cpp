#include "../../inc/framework.h"

bool BloomFramework::TextureStore::loadTexture(std::string path, std::string nickname) {
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if(loadedSurface == NULL) {
		std::clog << "Unable to load image " << path.c_str() << "%s! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}
	else {
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, TargetScreen->format, NULL);
		if(optimizedSurface == NULL) {
			std::clog << "Unable to optimize image " << path.c_str() << "%s! SDL Error: " << SDL_GetError() << std::endl;
			optimizedSurface = loadedSurface;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	if(nickname == "")
		nickname = path;
	storage.emplace_back(std::make_pair(nickname,optimizedSurface));
	return true;
}

SDL_Surface* BloomFramework::TextureStore::getTexture(std::string nickname) {
	for(std::pair<std::string, SDL_Surface*> i : storage){
		if(i.first == nickname) {
			return i.second;
		}
	}
	std::clog << "[ERROR] Unable to find texture with nickname \"" << nickname << "\", loading first available texture." << std::endl;
	return storage[0].second;
}
#include "../inc/TextureManager.h"

SDL_Texture* BloomFramework::TextureManager::loadTexture(const char* fileName) {
	SDL_Surface* tmpSurface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return texture;
}

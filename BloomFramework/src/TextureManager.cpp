#include "../inc/TextureManager.h"

SDL_Texture* BloomFramework::TextureManager::loadTexture(SDL_Renderer* renderer, const char* fileName) {
	SDL_Surface* tmpSurface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return texture;
}

void BloomFramework::TextureManager::draw(SDL_Renderer* renderer, SDL_Texture * texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(renderer, texture, &src, &dest, NULL, NULL, flip);
}

#include "../inc/GameObject.h"
#include "../inc/TextureManager.h"

BloomFramework::GameObject::GameObject(const char * textureSheet, int x, int y) {
	objectTexture = TextureManager::loadTexture(textureSheet);
	xpos = x;
	ypos = y;
}

BloomFramework::GameObject::~GameObject() {}

void BloomFramework::GameObject::update() {
	xpos++;
	ypos++;

	srcRect.h = 136;
	srcRect.w = 64;
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void BloomFramework::GameObject::render() {
	SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &destRect);
}

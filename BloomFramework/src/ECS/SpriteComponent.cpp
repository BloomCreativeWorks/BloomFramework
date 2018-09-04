#include "..\..\inc\ECS\SpriteComponent.h"

inline BloomFramework::SpriteComponent::SpriteComponent(const char * texturePath) {
	setTexture(texturePath);
}

BloomFramework::SpriteComponent::SpriteComponent(const char * texturePath, int frames, int speed) {
	animated = true;
	this->frames = frames;
	this->speed = speed;
	setTexture(texturePath);
}

inline BloomFramework::SpriteComponent::~SpriteComponent() {
	SDL_DestroyTexture(texture);
}

inline void BloomFramework::SpriteComponent::init() {
	transform = &entity->getComponent<TransformComponent>();

	srcRect.x = srcRect.y = 0;
	srcRect.w = transform->width;
	srcRect.h = transform->height;
}

inline void BloomFramework::SpriteComponent::update() {
	if(animated) {
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
	}

	destRect.x = static_cast<int>(transform->position.x);
	destRect.y = static_cast<int>(transform->position.y);
	destRect.w = transform->width * transform->scale;
	destRect.h = transform->height * transform->scale;
}

inline void BloomFramework::SpriteComponent::draw() {
	TextureManager::draw(texture, srcRect, destRect);
}

inline void BloomFramework::SpriteComponent::setTexture(const char * texturePath) {
	texture = TextureManager::loadTexture(texturePath);
}

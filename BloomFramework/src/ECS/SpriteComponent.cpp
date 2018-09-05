#include "..\..\inc\ECS\SpriteComponent.h"

inline BloomFramework::SpriteComponent::SpriteComponent(Game* gameObject, const char * texturePath) {
	this->gameObject = gameObject;
	setTexture(texturePath);
}

BloomFramework::SpriteComponent::SpriteComponent(Game* gameObject, const char * texturePath, bool isAnimated) {
	this->gameObject = gameObject;
	animated = isAnimated;
	Animation idle = Animation(0, 3, 100);
	Animation walk = Animation(1, 8, 100);

	animations.emplace("Idle", idle);
	animations.emplace("Walk", walk);

	play("Idle");
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
	srcRect.y = animIndex * transform->height;

	destRect.x = static_cast<int>(transform->position.x);
	destRect.y = static_cast<int>(transform->position.y);
	destRect.w = transform->width * transform->scale;
	destRect.h = transform->height * transform->scale;
}

inline void BloomFramework::SpriteComponent::draw() {
	TextureManager::draw(gameObject->renderer, texture, srcRect, destRect, spriteFlip);
}

void BloomFramework::SpriteComponent::play(const char * animationTag) {
	frames = animations[animationTag].frames;
	animIndex = animations[animationTag].index;
	speed = animations[animationTag].speed;
}

inline void BloomFramework::SpriteComponent::setTexture(const char * texturePath) {
	texture = TextureManager::loadTexture(gameObject->renderer, texturePath);
}
#pragma once

#include "../stdIncludes.h"
#include "Components.h"

namespace BloomFramework {
	class BLOOMFRAMEWORK_API SpriteComponent : public Component {
	public:
		SpriteComponent() = default;
		SpriteComponent(const char* texturePath) {
			setTexture(texturePath);
		}

		void init() override {
			position = &entity->getComponent<PositionComponent>();

			srcRect.x = srcRect.y = 0;
			srcRect.w = srcRect.h = 32;

			destRect.w = destRect.h = 64;
		}
		void update() override {
			destRect.x = position->x();
			destRect.y = position->y();
		}
		void draw() override {
			TextureManager::draw(texture, srcRect, destRect);
		}

		void setTexture(const char* texturePath) {
			texture = TextureManager::loadTexture(texturePath);
		}

	private:
		PositionComponent* position;
		SDL_Texture* texture;
		SDL_Rect srcRect, destRect;
	};
}
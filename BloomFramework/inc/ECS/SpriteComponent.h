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
		~SpriteComponent() {
			SDL_DestroyTexture(texture);
		}

		void init() override {
			transform = &entity->getComponent<TransformComponent>();

			srcRect.x = srcRect.y = 0;
			srcRect.w = transform->width;
			srcRect.h = transform->height;
		}
		void update() override {
			destRect.x = (int)transform->position.x;
			destRect.y = (int)transform->position.y;
			destRect.w = transform->width * transform->scale;
			destRect.h = transform->height * transform->scale;
		}
		void draw() override {
			TextureManager::draw(texture, srcRect, destRect);
		}

		void setTexture(const char* texturePath) {
			texture = TextureManager::loadTexture(texturePath);
		}

	private:
		TransformComponent* transform;
		SDL_Texture* texture;
		SDL_Rect srcRect, destRect;
	};
}
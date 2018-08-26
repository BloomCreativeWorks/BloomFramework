#pragma once

#include "../stdIncludes.h"
#include "../TextureManager.h"
#include "EntityComponentSystem.h"
#include "TransformComponent.h"

namespace BloomFramework {
	class BLOOMFRAMEWORK_API SpriteComponent : public Component {
	public:
		SpriteComponent() = default;
		SpriteComponent(const char* texturePath);
		~SpriteComponent();

		void init() override;
		void update() override;
		void draw() override;

		void setTexture(const char* texturePath);

	private:
		TransformComponent* transform;
		SDL_Texture* texture;
		SDL_Rect srcRect, destRect;
	};
}
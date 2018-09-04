#pragma once

#include "../stdIncludes.h"
#include "../TextureManager.h"
#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "Animation.h"
#include <map>



namespace BloomFramework {
	class BLOOMFRAMEWORK_API SpriteComponent : public Component {
	public:
		SpriteComponent() = default;
		SpriteComponent(const char* texturePath);
		SpriteComponent(const char* texturePath, bool isAnimated);
		~SpriteComponent();

		void init() override;
		void update() override;
		void draw() override;
		void play(const char* animationTag);

		void setTexture(const char* texturePath);

		int animIndex = 0;
		std::map<const char*, Animation> animations;
		SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	private:
		TransformComponent* transform;
		SDL_Texture* texture;
		SDL_Rect srcRect, destRect;
		
		bool animated = false;
		int frames = 0;
		int speed = 100;
	};
}
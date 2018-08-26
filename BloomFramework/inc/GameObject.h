#pragma once

#include "stdIncludes.h"
#include "Game.h"

namespace BloomFramework {
	class BLOOMFRAMEWORK_API GameObject {
	public:
		GameObject(const char * textureSheet, int x = 0, int y = 0);
		~GameObject();

		void update();
		void render();
	private:
		int xpos, ypos;

		SDL_Texture* objectTexture;
		SDL_Rect srcRect, destRect;
	};
}
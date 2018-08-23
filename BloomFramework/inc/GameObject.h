#pragma once
#include "stdIncludes.h"

namespace BloomFramework {
	class BLOOMFRAMEWORK_API GameObject {
	public:
		GameObject(const char * textureSheet, SDL_Renderer * rend, int x = 0, int y = 0);
		~GameObject();

		void update();
		void render();
	private:
		int xpos, ypos;

		SDL_Texture* objectTexture;
		SDL_Rect srcRect, destRect;
		SDL_Renderer* renderer;
	};
}
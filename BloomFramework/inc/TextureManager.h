#pragma once

#include "stdIncludes.h"
#include "Game.h"

namespace BloomFramework {
	class BLOOMFRAMEWORK_API TextureManager {
	public:
		static SDL_Texture* loadTexture(const char * fileName);
		static void draw(SDL_Texture * texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
	};
}
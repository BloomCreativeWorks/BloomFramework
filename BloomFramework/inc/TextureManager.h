#pragma once
#include "stdIncludes.h"

namespace BloomFramework {
	class BLOOMFRAMEWORK_API TextureManager {
	public:
		static SDL_Texture* loadTexture(const char * fileName, SDL_Renderer * renderer);
	};
}
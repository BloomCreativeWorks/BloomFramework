#pragma once
#include "stdIncludes.h"
#include "Game.h"
#include "TextureManager.h"

namespace BloomFramework {
	class BLOOMFRAMEWORK_API Map {
	public:
		Map();
		~Map();

		void loadMap(int levelMap[20][25]);
		void drawMap();
	private:
		SDL_Rect srcRect, destRect;
		SDL_Texture* dirt;
		SDL_Texture* grass;
		SDL_Texture* water;

		int map[20][25];
	};
}
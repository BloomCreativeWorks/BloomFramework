#pragma once
#include "stdIncludes.h"
#include "Game.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Texture {
	public:
		Texture() = default;
		Texture(const std::string & filePath, Game* gameInstance);


		void render(int xPos, int yPos, SDL_RendererFlip flip = SDL_FLIP_NONE);
		int getTextureWidth();
		int getTextureHeight();

	private:
		Game* _gameInstance;
		int _textureWidth, _textureHeight;
		int _scale = 3;
		SDL_Texture * _texture;

	};
}
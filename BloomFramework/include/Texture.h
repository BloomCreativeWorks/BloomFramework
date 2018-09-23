#pragma once
#include "stdIncludes.h"
#include "Game.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Texture {
	public:
		Texture() = default;
		Texture(Game* gameInstance, const std::string & filePath);
		Texture(Game* gameInstance, const std::string & filePath, SDL_Color colorKey);
		~Texture();

		void loadTexture(const std::string & filePath);
		void render(SDL_Rect srcRect = { 0,0,0,0 }, SDL_Rect destRect = { 0,0,0,0 }, SDL_RendererFlip flip = SDL_FLIP_NONE);
		int getTextureWidth();
		int getTextureHeight();
		void setColorKey(Uint8 red, Uint8 green, Uint8 blue);
		void setColorKey(bool enabled);
	private:
		SDL_Color _colorKey = { 0,0,0,0 };
		bool _colorKeySet = false;
		Game* _gameInstance;
		int _textureWidth, _textureHeight;
		int _scale = 3;
		SDL_Texture * _texture;

	};
}
#include "..\include\Texture.h"

namespace bloom {
	Texture::Texture(const std::string & filePath, Game* gameInstance) :
		_textureWidth(0),
		_textureHeight(0),
		_texture(nullptr),
		_gameInstance(gameInstance)
	{
		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
		if (loadedSurface == NULL)
		{
			std::cerr << "[SDL_Init] " << IMG_GetError() << std::endl;
		}
		else
		{
			//Color key image
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

			//Create texture from surface pixels
			_texture = SDL_CreateTextureFromSurface(_gameInstance->getRenderer(), loadedSurface);
			if (_texture == nullptr)
			{
				std::cerr << "[SDL_Texture] " << SDL_GetError() << std::endl;
			}
			else
			{
				//Get image dimensions
				_textureWidth = loadedSurface->w;
				_textureHeight = loadedSurface->h;
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}
	}
	void Texture::render(int xPos, int yPos, SDL_RendererFlip flip)
	{
		//Set rendering space and render to screen
		SDL_Rect renderQuad = { xPos, yPos, _textureWidth*_scale, _textureHeight*_scale };

		//Render to screen
		SDL_RenderCopyEx(_gameInstance->getRenderer(), _texture, NULL, &renderQuad, NULL, NULL, flip);
	}
	int Texture::getTextureWidth()
	{
		return _textureWidth;
	}
	int Texture::getTextureHeight()
	{
		return _textureHeight;
	}
}

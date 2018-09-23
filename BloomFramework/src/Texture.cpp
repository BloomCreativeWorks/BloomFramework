#include "..\include\Texture.h"

namespace bloom {
	Texture::Texture(Game* gameInstance, const std::string & filePath) :
		_textureWidth(0),
		_textureHeight(0),
		_texture(nullptr),
		_gameInstance(gameInstance)
	{
		loadTexture(filePath);
	}
	Texture::Texture(Game * gameInstance, const std::string & filePath, SDL_Color colorKey):
		_textureWidth(0),
		_textureHeight(0),
		_texture(nullptr),
		_gameInstance(gameInstance),
		_colorKey(colorKey),
		_colorKeySet(true)
	{
		loadTexture(filePath);
	}
	Texture::~Texture()
	{
		SDL_DestroyTexture(_texture);
	}
	void Texture::loadTexture(const std::string & filePath)
	{
		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
		if (loadedSurface == NULL)
		{
			std::cerr << "[SDL_IMG] " << IMG_GetError() << std::endl;
		}
		else
		{
			if (_colorKeySet) //Color key image
				SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, _colorKey.r, _colorKey.g, _colorKey.b));

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
	void Texture::render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip)
	{
		if (srcRect.w <= 0)
			std::cerr << "[Texture Render] srcRect's width is set to a non-signed positive integer" << std::endl
			<< "                Was that intentional?" << std::endl;
		if (srcRect.h <= 0)
			std::cerr << "[Texture Render] srcRect's height is set to a non-signed positive integer" << std::endl
			<< "                Was that intentional?" << std::endl;
		if (destRect.w <= 0)
			std::cerr << "[Texture Render] destRect's width is set to a non-signed positive integer" << std::endl
			<< "                Was that intentional?" << std::endl;
		if (destRect.h <= 0)
			std::cerr << "[Texture Render] destRect's height is set to a non-signed positive integer" << std::endl
			<< "                Was that intentional?" << std::endl;

		//Set rendering space and render to screen
		//SDL_Rect renderQuad = { xPos, yPos, _textureWidth*_scale, _textureHeight*_scale };

		//Render to screen
		SDL_RenderCopyEx(_gameInstance->getRenderer(), _texture, &srcRect, &destRect, NULL, NULL, flip);
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

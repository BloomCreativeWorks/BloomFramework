#include "..\include\Texture.h"

namespace bloom {
	Texture::Texture(Game* gameInstance, const std::string & filePath) :
		m_textureWidth(0),
		m_textureHeight(0),
		m_texture(nullptr),
		m_gameInstance(gameInstance)
	{
		loadTexture(filePath);
	}
	Texture::Texture(Game * gameInstance, const std::string & filePath, SDL_Color colorKey):
		m_textureWidth(0),
		m_textureHeight(0),
		m_texture(nullptr),
		m_gameInstance(gameInstance),
		m_colorKey(colorKey),
		m_colorKeySet(true)
	{
		loadTexture(filePath);
	}
	Texture::~Texture()
	{
		SDL_DestroyTexture(m_texture);
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
			if (m_colorKeySet) //Color key image
				SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, m_colorKey.r, m_colorKey.g, m_colorKey.b));

			//Create texture from surface pixels
			m_texture = SDL_CreateTextureFromSurface(m_gameInstance->getRenderer(), loadedSurface);
			if (m_texture == nullptr)
			{
				std::cerr << "[SDL_Texture] " << SDL_GetError() << std::endl;
			}
			else
			{
				//Get image dimensions
				m_textureWidth = loadedSurface->w;
				m_textureHeight = loadedSurface->h;
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
		SDL_RenderCopyEx(m_gameInstance->getRenderer(), m_texture, &srcRect, &destRect, NULL, NULL, flip);
	}
	int Texture::getTextureWidth()
	{
		return m_textureWidth;
	}
	int Texture::getTextureHeight()
	{
		return m_textureHeight;
	}
}

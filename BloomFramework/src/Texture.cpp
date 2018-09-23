#include "..\include\Texture.h"

namespace bloom {
	Texture::Texture(SDL_Texture * texture, SDL_Renderer ** targetRenderer) : m_texture(texture), m_renderer(targetRenderer) {}
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
		SDL_RenderCopyEx(*m_renderer, m_texture, &srcRect, &destRect, NULL, NULL, flip);
	}
	void Texture::dispose()
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
	Texture::~Texture() {
		dispose();
	}
}

#include "Graphics/Texture.h"
#include "Exception.h"

namespace bloom::graphics {
	Texture::Texture(SDL_Texture * texture, SDL_Renderer *& targetRenderer) : m_texture(texture), m_renderer(targetRenderer) {}

	void Texture::render(std::optional<SDL_Rect> srcRect, SDL_Rect destRect, SDL_RendererFlip flip) {
		if (destRect.w <= 0)
			throw Exception("[Texture Render] destcRect.w is <= 0.\nIs that intentional?");
		if (destRect.h <= 0)
			throw Exception("[Texture Render] destRect.h is <= 0.\nIs that intentional?");
		if (srcRect.has_value()) {
			if (srcRect->w <= 0)
				throw Exception("[Texture Render] srcRect.w is <= 0.\nIs that intentional?");
			if (srcRect->h <= 0)
				throw Exception("[Texture Render] srcRect.h is <= 0.\nIs that intentional?");

			//Set rendering space and render to screen
			//SDL_Rect renderQuad = { xPos, yPos, _textureWidth*_scale, _textureHeight*_scale };

			//Render to screen
			SDL_RenderCopyEx(m_renderer, m_texture, &srcRect.value(), &destRect, 0.0, nullptr, flip);
		}
		else {
			//Render to screen
			SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &destRect, 0.0, nullptr, flip);
		}
	}

	Texture::~Texture() {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}

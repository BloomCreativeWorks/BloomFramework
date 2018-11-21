#include "Graphics/Drawable.h"

namespace bloom::graphics {
	Drawable::Drawable(SDL_Renderer *& targetRenderer) : m_renderer(targetRenderer) {}

	Drawable::~Drawable() {
		if (m_texture)
			SDL_DestroyTexture(m_texture);
	}

	void Drawable::render(std::optional<SDL_Rect> srcRect, SDL_Rect destRect, SDL_RendererFlip flip) {
		if (destRect.w <= 0)
			throw Exception("[Drawable::render] destcRect.w is <= 0.\nIs that intentional?");
		if (destRect.h <= 0)
			throw Exception("[Drawable::render] destRect.h is <= 0.\nIs that intentional?");

		if (srcRect.has_value()) {
			if (srcRect->w <= 0)
				throw Exception("[Drawable::render] srcRect.w is <= 0.\nIs that intentional?");
			if (srcRect->h <= 0)
				throw Exception("[Drawable::render] srcRect.h is <= 0.\nIs that intentional?");

			//Set rendering space and render to screen
			//SDL_Rect renderQuad = { xPos, yPos, _textureWidth*_scale, _textureHeight*_scale };

			//Render to screen
			SDL_RenderCopyEx(m_renderer, m_texture, &srcRect.value(), &destRect, 0.0, nullptr, flip);
		}
		else
			//Render to screen
			SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &destRect, 0.0, nullptr, flip);
	}
}


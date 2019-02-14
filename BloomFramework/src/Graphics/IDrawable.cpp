#include "Graphics/IDrawable.h"

namespace bloom::graphics {
	IDrawable::IDrawable(SDL_Renderer *& targetRenderer) : m_renderer(targetRenderer) {
		if (!m_renderer)
			throw Exception("[IDrawable] `renderer` pointer can not be nullptr");
	}

	IDrawable::~IDrawable() {
		if (m_texture)
			SDL_DestroyTexture(m_texture);
	}

	void IDrawable::render(std::optional<SDL_Rect> srcRect, SDL_Rect destRect, SDL_RendererFlip flip) {
		if (destRect.w <= 0)
			throw Exception("[IDrawable::render] destcRect.w is <= 0.\nIs that intentional?");
		if (destRect.h <= 0)
			throw Exception("[IDrawable::render] destRect.h is <= 0.\nIs that intentional?");

		if (srcRect.has_value()) {
			if (srcRect->w <= 0)
				throw Exception("[IDrawable::render] srcRect.w is <= 0.\nIs that intentional?");
			if (srcRect->h <= 0)
				throw Exception("[IDrawable::render] srcRect.h is <= 0.\nIs that intentional?");

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


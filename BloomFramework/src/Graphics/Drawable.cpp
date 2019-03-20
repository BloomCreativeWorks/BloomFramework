#include "Graphics/Drawable.h"

namespace bloom::graphics {
	Drawable::Drawable(SDL_Renderer* const& targetRenderer) : c_renderer(targetRenderer) {
		if (!c_renderer)
			throw Exception("[Drawable] `renderer` pointer can not be nullptr");
	}

	Drawable::~Drawable() {
		if (m_texture)
			SDL_DestroyTexture(m_texture);
	}

	void Drawable::render(std::optional<SDL_Rect> srcRect, SDL_Rect destRect, SDL_RendererFlip flip) {
		if (!m_texture)
			return;

		if (destRect.w <= 0)
			throw Exception("[Drawable::render] destRect.w is <= 0");
		if (destRect.h <= 0)
			throw Exception("[Drawable::render] destRect.h is <= 0");

		auto sRectPtr = (srcRect.has_value() && srcRect->w > 0 && srcRect->h > 0) ? &srcRect.value() : nullptr;
		if (SDL_RenderCopyEx(c_renderer, m_texture, sRectPtr, &destRect, 0.0, nullptr, flip))
			throw Exception("[Drawable::render] -> " + std::string{ SDL_GetError() });

		//if (srcRect.has_value()) {
		//	if (srcRect->w <= 0)
		//		throw Exception("[Drawable::render] srcRect.w is <= 0");
		//	if (srcRect->h <= 0)
		//		throw Exception("[Drawable::render] srcRect.h is <= 0");

		//	//Set rendering space and render to screen
		//	//SDL_Rect renderQuad = { xPos, yPos, _textureWidth*_scale, _textureHeight*_scale };

		//	//Render to screen
		//	SDL_RenderCopyEx(m_renderer, m_texture, &srcRect.value(), &destRect, 0.0, nullptr, flip);
		//}
		//else
		//	//Render to screen
		//	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &destRect, 0.0, nullptr, flip);
	}
}


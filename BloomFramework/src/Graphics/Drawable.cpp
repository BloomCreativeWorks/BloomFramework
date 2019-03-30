#include "Graphics/Drawable.h"
#include "Exception.h"

namespace bloom::graphics {
	Drawable::Drawable(SDL_Renderer* targetRenderer) : c_renderer(targetRenderer) {
		if (!c_renderer)
			throw Exception("[Drawable] `renderer` pointer can not be nullptr");
	}

	Drawable::~Drawable() {
		if (m_texture)
			SDL_DestroyTexture(m_texture);
	}

	void Drawable::render(std::optional<SDL_Rect> srcRect, SDL_Rect destRect, double rotationAngle, SDL_RendererFlip flip) {
		if (!m_texture)
			return;

		if (destRect.w <= 0)
			throw Exception("[Drawable::render] destRect.w is <= 0");
		if (destRect.h <= 0)
			throw Exception("[Drawable::render] destRect.h is <= 0");

		auto sRectPtr = (srcRect.has_value() && srcRect->w > 0 && srcRect->h > 0) ? &srcRect.value() : nullptr;
		// Render to screen
		if (SDL_RenderCopyEx(c_renderer, m_texture, sRectPtr, &destRect, rotationAngle, nullptr, flip))
			throw Exception("[Drawable::render] -> " + std::string{ SDL_GetError() });
	}
}


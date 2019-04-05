#pragma once
#include <optional>
#include "stdIncludes.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API Drawable {
	public:
		Drawable(SDL_Renderer* const& targetRenderer);
		virtual ~Drawable() = 0;

		virtual void render(std::optional<SDL_Rect> srcRect, SDL_Rect destRect, SDL_RendererFlip flip = SDL_FLIP_NONE);

	protected:
		SDL_Renderer* const& c_renderer;
		SDL_Texture* m_texture = nullptr;
	};
}
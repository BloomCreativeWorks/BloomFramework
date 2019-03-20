#pragma once

#include <optional>
#include "stdIncludes.h"
#include "Exception.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API Drawable {
	public:
		Drawable() = delete;
		Drawable(SDL_Renderer* const& targetRenderer);
		virtual ~Drawable() = 0;

		virtual void render(std::optional<SDL_Rect> srcRect, SDL_Rect destRect, SDL_RendererFlip flip = SDL_FLIP_NONE);

	protected:
		SDL_Texture* m_texture = nullptr;
		SDL_Renderer* const& c_renderer;
	};
}
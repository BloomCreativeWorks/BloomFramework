#pragma once
#include <optional>
#include "stdIncludes.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API Drawable {
	public:
		virtual ~Drawable();

		virtual void render(std::optional<SDL_Rect> srcRect, SDL_Rect destRect, SDL_RendererFlip flip = SDL_FLIP_NONE);

	protected:
		explicit Drawable(SDL_Renderer* const& targetRenderer);

		SDL_Renderer* const& c_renderer;
		SDL_Texture* m_texture = nullptr;
	};
}
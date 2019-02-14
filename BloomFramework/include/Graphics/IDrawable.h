#pragma once

#include <optional>
#include "stdIncludes.h"
#include "Exception.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API IDrawable {
	public:
		IDrawable() = delete;
		IDrawable(SDL_Renderer *& targetRenderer);
		virtual ~IDrawable() = 0;

		virtual void render(std::optional<SDL_Rect> srcRect, SDL_Rect destRect, SDL_RendererFlip flip = SDL_FLIP_NONE);

	protected:
		SDL_Texture *	m_texture = nullptr;
		SDL_Renderer *&	m_renderer;
	};
}
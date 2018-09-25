#pragma once
#include "stdIncludes.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Texture {
	public:
		Texture() = default;
		explicit Texture(SDL_Texture * texture, SDL_Renderer *& targetRenderer);
		~Texture();
		void render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void dispose();
	private:
		SDL_Texture *	m_texture;
		SDL_Renderer *&	m_renderer;
	};
}
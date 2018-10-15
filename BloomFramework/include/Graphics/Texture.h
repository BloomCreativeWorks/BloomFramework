#pragma once

#include "stdIncludes.h"
#include <optional>

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API Texture {
	public:
		Texture() = default;
		explicit Texture(SDL_Texture * texture, SDL_Renderer *& target_renderer);
		~Texture();

		void Render(std::optional<SDL_Rect> src_rect, SDL_Rect dest_rect, SDL_RendererFlip flip = SDL_FLIP_NONE);

	private:
		SDL_Texture *	texture_;
		SDL_Renderer *&	renderer_;
	};

	using TexturePtr = std::shared_ptr<Texture>;
} // namespace bloom::graphics
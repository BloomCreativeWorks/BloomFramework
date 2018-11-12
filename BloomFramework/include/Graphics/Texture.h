#pragma once

#include <optional>
#include "stdIncludes.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API Texture {
	public:
		explicit Texture(SDL_Renderer *& targetRenderer, const std::filesystem::path & filePath, std::optional<SDL_Color> colorKey = std::nullopt);
		~Texture();

		void render(std::optional<SDL_Rect> srcRect, SDL_Rect destRect, SDL_RendererFlip flip = SDL_FLIP_NONE);

	private:
		SDL_Texture *	m_texture;
		SDL_Renderer *&	m_renderer;
	};

	using TexturePtr = std::shared_ptr<Texture>;
}
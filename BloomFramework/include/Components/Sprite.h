#pragma once

#include "stdIncludes.h"

#include "Graphics/Texture.h"

namespace bloom::components {
	struct Sprite {
		using TexturePtr = bloom::graphics::TexturePtr;

		Sprite(TexturePtr texture, std::optional<SDL_Rect> srcRect = std::nullopt) : texture(texture), srcRect(srcRect) {}

		TexturePtr texture;
		std::optional<SDL_Rect> srcRect;
	};
}
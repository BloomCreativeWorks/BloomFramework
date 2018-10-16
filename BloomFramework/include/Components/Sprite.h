#pragma once

#include "Graphics/TextureStore.h"
#include <optional>

namespace bloom::components {
	struct Sprite {
		using TexturePtr = bloom::graphics::TexturePtr;

		Sprite(TexturePtr texture, std::optional<SDL_Rect> srcRect = std::nullopt) : _texture(texture), srcRect(srcRect) {}

		TexturePtr texture;
		std::optional<SDL_Rect> srcRect;
	};
}
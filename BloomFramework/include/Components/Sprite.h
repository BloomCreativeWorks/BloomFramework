#pragma once

#include "Graphics/TextureStore.h"
#include <optional>

namespace bloom::components {
	struct Sprite {
		using TexturePtr = bloom::graphics::TexturePtr;

		Sprite(bloom::graphics::TexturePtr texture, std::optional<SDL_Rect> src_rect = std::nullopt) : texture(texture), src_rect(src_rect) {}

		bloom::graphics::TexturePtr texture;
		std::optional<SDL_Rect> src_rect;
	};
} // namespace bloom::components
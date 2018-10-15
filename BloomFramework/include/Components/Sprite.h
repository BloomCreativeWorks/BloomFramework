#pragma once

#include "Graphics/TextureStore.h"
#include <optional>

using namespace bloom::graphics;

namespace bloom::components {
	struct Sprite {
		Sprite(TexturePtr texture, std::optional<SDL_Rect> src_rect = std::nullopt) : texture(texture), src_rect(src_rect) {}

		TexturePtr texture;
		std::optional<SDL_Rect> src_rect;
	};
}
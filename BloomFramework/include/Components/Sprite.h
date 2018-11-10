#pragma once

#include <optional>
#include "Graphics/TextureStore.h"

namespace bloom::components {
	struct Sprite {
		using TexturePtr = bloom::graphics::TexturePtr;

		Sprite(TexturePtr texture, std::optional<SDL_Rect> srcRect = std::nullopt) : texture(texture), srcRect(srcRect) {}

		TexturePtr texture;
		std::optional<SDL_Rect> srcRect;
		double rotation = 0.0;
	};
}
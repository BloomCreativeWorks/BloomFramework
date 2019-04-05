#pragma once
#include <optional>
#include <utility>
#include "TextureStore.h"

namespace bloom::graphics {
	struct Sprite {
		Sprite(TexturePtr texture, std::optional<SDL_Rect> srcRect = std::nullopt) : texture(std::move(texture)), srcRect(srcRect) {}

		TexturePtr texture;
		std::optional<SDL_Rect> srcRect;
	};
}
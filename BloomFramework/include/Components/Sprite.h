#pragma once

#include "TextureStore.h"
#include <optional>

namespace bloom {
	struct Sprite {
		Sprite(TexturePtr texture, std::optional<SDL_Rect> srcRect = std::nullopt) : _texture(texture), _srcRect(srcRect) {}
		TexturePtr _texture;
		std::optional<SDL_Rect> _srcRect;
	};
}
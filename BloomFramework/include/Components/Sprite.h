#pragma once

#include "stdIncludes.h"
#include "Graphics/TextureStore.h"
#include <optional>

using namespace bloom::graphics;

namespace bloom::components {
	struct Sprite {
		Sprite(TexturePtr texture, std::optional<SDL_Rect> srcRect = std::nullopt) : _texture(texture), _srcRect(srcRect) {}
		TexturePtr _texture;
		std::optional<SDL_Rect> _srcRect;
	};
}
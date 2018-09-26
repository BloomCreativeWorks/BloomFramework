#pragma once

#include "stdIncludes.h"
#include "TextureStore.h"

namespace bloom {
	struct Sprite {
		Sprite(TexturePtr texture) : _texture(texture) {}
		Sprite(TexturePtr texture, const SDL_Rect & srcRect) : _texture(texture), _srcRect(srcRect), _cropTexture(true) {}
		TexturePtr _texture;
		SDL_Rect _srcRect;
		bool _cropTexture;
	};
}
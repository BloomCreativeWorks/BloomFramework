#pragma once

#include "stdIncludes.h"
#include "Components/Components.h"
#include "DefaultSystem.h"

namespace bloom::systems {
	class RenderSystem : public System {
		using Position = bloom::components::Position;
		using Size = bloom::components::Size;
		using Sprite = bloom::components::Sprite;
		using System::DefaultSystem;

	public:
		void update(uint64_t = 0) override {
			m_registry.view<Position, Size, Sprite>().each(
				[](auto, Position& position, Size& size, Sprite& sprite) {
					sprite.texture->render(sprite.srcRect, SDL_Rect{ position.x, position.y, size.w, size.h });
				});
		}
	};
}
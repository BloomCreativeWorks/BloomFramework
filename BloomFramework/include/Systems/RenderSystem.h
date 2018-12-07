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
		void update(std::optional<double> deltaTime = std::nullopt) override {
			m_registry.view<Position, Size, Sprite>().each(
				[](auto entity, Position & pos, Size & size, Sprite & spr) {
				SDL_Rect destRect{ pos.x, pos.y, size.w, size.h };
				spr.texture->render(spr.srcRect, destRect);
			});
		}
	};
}
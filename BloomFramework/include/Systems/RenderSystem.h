#pragma once

#include "stdIncludes.h"
#include "DefaultSystem.h"
#include "Components/Components.h"

namespace bloom::systems {
	using namespace components;

	class RenderSystem : public System {
		using System::DefaultSystem;
	public:
		void Update(std::optional<double> delta_time = std::nullopt) override;
	};

	void RenderSystem::Update (std::optional<double> delta_time) {
			registry_.view<Position, Size, Sprite>().each(
				[](auto entity, Position & pos, Size& size, Sprite & spr) {
				SDL_Rect destRect{
					static_cast<int>(pos.x),
					static_cast<int>(pos.y),
					static_cast<int>(size.w),
					static_cast<int>(size.h)
				};
				spr.texture->Render(spr.src_rect, destRect);
			});
	}
} 
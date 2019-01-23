#pragma once

#include <utility>
#include "stdIncludes.h"
#include "Components/Components.h"
#include "DefaultSystem.h"
#include "Components/Components.h"

namespace bloom::systems {
	class RenderSystem : public DefaultSystem {
		using Transform = bloom::components::Transform;
		using Rotation = double;
		using Sprite = bloom::components::Sprite;
		using LayerGroup = bloom::components::LayerGroup;
		using DefaultSystem::System;

	public:
		~RenderSystem() = default;

		void update(std::optional<double> deltaTime = std::nullopt) override {
			m_registry.view<Transform, Sprite>().each(
				[&](auto entity, Transform& trans, Sprite& spr) {

				if (trans.size.w < 0)
					trans.size.w = 0;
				if (trans.size.h < 0)
					trans.size.h = 0;

				Coord actualPos = trans.position.getSDLPos(parentScene.getGameInstance().getRenderer(), trans.size.w, trans.size.h);
				SDL_Rect destRect{
					actualPos.x,
					actualPos.y,
					trans.size.w,
					trans.size.h
				};

				// Draw sprite to scene texture
				spr.texture->render(spr.srcRect, destRect, trans.rotation);
			});
		}

	private:
		SDL_Renderer* renderer;
	};
}
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
			std::list<std::tuple<Sprite, Rotation, SDL_Rect, LayerGroup>> renderQueue;

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

				LayerGroup layerNo = (m_registry.has<LayerGroup>(entity) ? m_registry.get<LayerGroup>(entity) : 0);

				// Place sprites into queue for sorting later.
				renderQueue.emplace_back(std::make_tuple(spr, trans.rotation, destRect, layerNo));
			});

			// Sort the sprites based on priority, higher number means rendered later. Same layer may fight 
			renderQueue.sort([](const auto& lhs, const auto& rhs) {
				return std::get<3>(lhs) < std::get<3>(rhs);
			});

			// Render
			for (auto& [spr, rot, destRect, lg] : renderQueue)
				spr.texture->render(spr.srcRect, destRect, rot);
		}

	private:
		SDL_Renderer* renderer;
	};
}
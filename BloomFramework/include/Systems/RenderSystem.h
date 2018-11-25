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
			std::vector<std::tuple<Sprite,Rotation, SDL_Rect, LayerGroup>> renderQueue{};

			m_registry.view<Transform, Sprite>().each(
				[&](auto entity, Transform & trans, Sprite & spr) {

				if (trans.size.w < 0)
					trans.size.w = 0;
				if (trans.size.h < 0)
					trans.size.h = 0;

				Coord actualPos = trans.position.getSDLPos(parentScene.getGameInstance().getRenderer(), trans.size.w, trans.size.h);
				SDL_Rect destRect{
					static_cast<int>(actualPos.x),
					static_cast<int>(actualPos.y),
					static_cast<int>(trans.size.w),
					static_cast<int>(trans.size.h)
				};

				LayerGroup layerNo;
				if (m_registry.has<LayerGroup>(entity))
					layerNo = m_registry.get<LayerGroup>(entity);
				else
					layerNo = 0;

				// Place sprites into queue for sorting later.
				renderQueue.emplace_back(std::make_tuple(spr, trans.rotation, destRect, layerNo));
			});

			// Sort the sprites based on priority, higher number means rendered later. Same layer may fight 
			std::sort(renderQueue.begin(), renderQueue.end(), [](const auto& lhs, const auto& rhs) {
				return std::get<3>(lhs) < std::get<3>(rhs);
			});

			// Render
			for (auto i : renderQueue) {
				auto & spr = std::get<0>(i);
				auto & rot = std::get<1>(i);
				auto & destRect = std::get<2>(i);
				spr.texture->render(spr.srcRect, destRect, rot);
			}
		}

	private:
		SDL_Renderer * renderer;
	};
}
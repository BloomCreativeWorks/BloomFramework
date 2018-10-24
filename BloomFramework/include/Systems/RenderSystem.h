#pragma once

#include "stdIncludes.h"
#include "Components/Components.h"
#include "DefaultSystem.h"
#include "Components/Components.h"
#include <utility>

namespace bloom::systems {
	class RenderSystem : public System {
		using Position = bloom::components::Position;
		using Size = bloom::components::Size;
		using Sprite = bloom::components::Sprite;
		using LayerGroup = bloom::components::LayerGroup;
		using System::DefaultSystem;

	public:
		void update(std::optional<double> deltaTime = std::nullopt) override {
			std::vector<std::tuple<Sprite, SDL_Rect, LayerGroup>> renderQueue{};

			m_registry.view<Position, Size, Sprite>().each(
				[&](auto entity, Position & pos, Size& size, Sprite & spr) {
				SDL_Rect destRect{
					static_cast<int>(pos.x),
					static_cast<int>(pos.y),
					static_cast<int>(size.w),
					static_cast<int>(size.h)
				};

				LayerGroup layerNo;
				if (m_registry.has<LayerGroup>(entity))
					layerNo = m_registry.get<LayerGroup>(entity);
				else
					layerNo = 0;

				// Place sprites into queue for sorting later.
				renderQueue.emplace_back(std::make_tuple(spr,destRect,layerNo));
			});
			
			// Sort the sprites based on priority, higher number means rendered later. Same layer may fight 
			std::sort(renderQueue.begin(), renderQueue.end(), [](const auto& lhs, const auto& rhs) {
				return std::get<2>(lhs) < std::get<2>(rhs);
			});

			// Render
			for (auto i : renderQueue) {
				auto & spr = std::get<0>(i);
				auto & destRect = std::get<1>(i);
				spr.texture->render(spr.srcRect, destRect);
			}
		}
	};
} 
#pragma once

#include "stdIncludes.h"
#include "DefaultSystem.h"
#include "Components/Components.h"
#include <utility>

namespace bloom {
	class RenderSystem : public System {
		using System::DefaultSystem;
	public:
		void System::update(std::optional<double> deltaTime)
		{
			std::vector<std::tuple<Sprite, SDL_Rect, LayerGroup>> renderQueue{};

			m_registry.view<Position, Size, Sprite>().each(
				[&](auto entity, Position & pos, Size& size, Sprite & spr) {
				SDL_Rect destRect{
					static_cast<int>(pos.x),
					static_cast<int>(pos.y),
					static_cast<int>(size.w),
					static_cast<int>(size.h)
				};

				LayerGroup tmp2;
				if (m_registry.has<LayerGroup>(entity))
					tmp2 = m_registry.get<LayerGroup>(entity);
				else
					tmp2 = 0;

				// Place sprites into queue for sorting later.
				renderQueue.emplace_back(std::make_tuple(spr,destRect,tmp2));
			});
			
			// Sort the sprites based on priority, higher number means rendered later. Same layer may fight 
			std::sort(renderQueue.begin(), renderQueue.end(), [](const auto& lhs, const auto& rhs) {
				return std::get<2>(lhs) < std::get<2>(rhs);
			});

			// Render
			for (auto i : renderQueue) {
				auto & spr = std::get<0>(i);
				auto & destRect = std::get<1>(i);
				spr._texture->render(spr._srcRect, destRect);
			}
		}
	};
}
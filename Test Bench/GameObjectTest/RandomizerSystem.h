#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

using namespace bloom;
class RandomPositionSystem : bloom::System {
public:
	using bloom::System::DefaultSystem;
public:
	void bloom::System::update(std::optional<double> dt = std::nullopt)
	{
		m_registry.view<Position>().each(
			[this](auto entity, Position & pos) {
			if (!m_registry.has<NoRandomPos>(entity)) {
				pos.x = rand() % 672;
				pos.y = rand() % 472;
			}
		});
	}

	void update(int frameWidth, int frameHeight, std::optional<double> dt = std::nullopt)
	{
		m_registry.view<Position>().each(
			[this, frameWidth, frameHeight](auto entity, Position & pos) {
			if (!m_registry.has<NoRandomPos>(entity)) {
				pos.x = rand() % frameWidth;
				pos.y = rand() % frameHeight;
			}
		});
	}
};
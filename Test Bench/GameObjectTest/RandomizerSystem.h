#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

using namespace bloom;
class RandomPositionSystem : public bloom::System {
public:
	using bloom::System::DefaultSystem;
public:
	void System::update(std::optional<double> dt)
	{
		m_registry.view<Position>().each(
			[this](auto entity, Position & pos) {
			if (!m_registry.has<NoRandomPos>(entity)) {
				pos.x = rand() % 672;
				pos.y = rand() % 472;
			}
		});
	}
};
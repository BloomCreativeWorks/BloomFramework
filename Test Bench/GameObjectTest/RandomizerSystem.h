#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

using namespace bloom;
class RandomPositionSystem : bloom::System {
public:
	using bloom::System::DefaultSystem;
public:
	void bloom::System::update(std::optional<DeltaTime> dt = std::nullopt)
	{
		m_registry.view<Position>().each(
			[this](auto entity, Position & pos) {
			if (!m_registry.has<NoRandomPos>(entity)) {
				pos.x = static_cast<float>(rand() % 672);
				pos.y = static_cast<float>(rand() % 472);
			}
		});
	}
};
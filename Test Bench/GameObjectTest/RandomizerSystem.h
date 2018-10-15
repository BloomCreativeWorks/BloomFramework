#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

using namespace bloom::systems;
class RandomPositionSystem : public System {
	using System::DefaultSystem;
public:
	void Update(std::optional<double> delta_time = std::nullopt) override;
};

void RandomPositionSystem::Update(std::optional<double> delta_time) {
	registry_.view<Position>().each(
		[this](auto entity, Position & pos) {
		if (!registry_.has<NoRandomPos>(entity)) {
			pos.x = rand() % 672;
			pos.y = rand() % 472;
		}
	});
}
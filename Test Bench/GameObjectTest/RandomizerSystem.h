#ifndef TESTBENCH_RANDOMIZERSYSTEM_H_
#define TESTBENCH_RANDOMIZERSYSTEM_H_

#include "Framework.h"
#include "NoRandomComponent.h"

class RandomPositionSystem : public bloom::systems::System {
	using Position = bloom::components::Position;
	using bloom::systems::System::DefaultSystem;

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

#endif // !TESTBENCH_RANDOMIZERSYSTEM_H_
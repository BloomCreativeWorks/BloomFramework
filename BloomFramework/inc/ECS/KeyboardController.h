#pragma once
#include "../stdIncludes.h"
#include "../Game.h"
#include "Components.h"

namespace BloomFramework {
	class TransformComponent;
	class BLOOMFRAMEWORK_API KeyboardController : public Component {
	public:
		TransformComponent* transform;

		void init() override;

		void update() override;
	};
}

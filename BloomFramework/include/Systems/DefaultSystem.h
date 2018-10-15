#pragma once

#include "stdIncludes.h"
#include <optional>

namespace bloom::systems {
	class DefaultSystem {
	public:
		DefaultSystem(entt::DefaultRegistry & registry) : registry_(registry) {};

		virtual void update(std::optional<double> delta_time = std::nullopt) = 0;

	protected:
		entt::DefaultRegistry & registry_;
	};

	using System = DefaultSystem;
}
#pragma once

#include <optional>
#include "stdIncludes.h"

namespace bloom::systems {
	class DefaultSystem {
	public:
		DefaultSystem(entt::DefaultRegistry & registry) : m_registry(registry) {};

		virtual void update(std::optional<double> deltaTime = std::nullopt) = 0;

	protected:
		entt::DefaultRegistry & m_registry;
	};

	using System = DefaultSystem;
}
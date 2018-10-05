#pragma once

#include "stdIncludes.h"
#include <optional>

namespace bloom {
	class DefaultSystem {
	public:
		DefaultSystem(entt::DefaultRegistry & registry) : m_registry(registry) {};
		virtual void update(std::optional<double> deltaTime = std::nullopt) {};

	protected:
		entt::DefaultRegistry & m_registry;
	};
	using System = DefaultSystem;
}
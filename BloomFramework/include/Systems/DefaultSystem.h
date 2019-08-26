#pragma once

#include "stdIncludes.h"

namespace bloom::systems {
	class DefaultSystem {
	public:
		DefaultSystem(entt::registry& registry) : m_registry(registry) {}
		DefaultSystem(const DefaultSystem&) = default;
		DefaultSystem(DefaultSystem&&) = default;
		DefaultSystem& operator=(const DefaultSystem&) = delete;
		DefaultSystem& operator=(DefaultSystem&&) = delete;
		virtual ~DefaultSystem() = default;

		virtual void update(double deltaTime = 0) = 0;

	protected:
		entt::registry& m_registry;
	};

	using System = DefaultSystem;
}
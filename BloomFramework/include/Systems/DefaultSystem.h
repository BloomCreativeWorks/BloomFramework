#pragma once

#include "stdIncludes.h"

namespace bloom::systems {
	class DefaultSystem {
	public:
		DefaultSystem(entt::DefaultRegistry& registry) : m_registry(registry) {}
		DefaultSystem(const DefaultSystem&) = default;
		DefaultSystem(DefaultSystem&&) = default;
		DefaultSystem& operator=(const DefaultSystem&) = delete;
		DefaultSystem& operator=(DefaultSystem&&) = delete;
		virtual ~DefaultSystem() = default;

		virtual void update(uint64_t deltaTime = 0) = 0;

	protected:
		entt::DefaultRegistry& m_registry;
	};

	using System = DefaultSystem;
}
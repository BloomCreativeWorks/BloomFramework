#ifndef BLOOM_SYSTEMS_DEFAULTSYSTEM_H_
#define BLOOM_SYSTEMS_DEFAULTSYSTEM_H_

#include "stdIncludes.h"
#include <optional>

namespace bloom::systems {
	class DefaultSystem {
	public:
		DefaultSystem(entt::DefaultRegistry & registry) : registry_(registry) {};

		virtual void Update(std::optional<double> delta_time = std::nullopt) = 0;

	protected:
		entt::DefaultRegistry & registry_;
	};

	using System = DefaultSystem;
} // namespace bloom::systems

#endif // !BLOOM_SYSTEMS_DEFAULTSYSTEM_H_
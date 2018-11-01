#pragma once

#include <optional>
#include "stdIncludes.h"

namespace bloom {
	class Scene;
	namespace systems {
		class BLOOMFRAMEWORK_API DefaultSystem {
		public:
			DefaultSystem(bloom::Scene & screenObject);;

			virtual void update(std::optional<double> deltaTime = std::nullopt) = 0;

		protected:
			bloom::Scene & parentScreen;
			entt::DefaultRegistry & m_registry;
		};

		using System = DefaultSystem;
	}
}
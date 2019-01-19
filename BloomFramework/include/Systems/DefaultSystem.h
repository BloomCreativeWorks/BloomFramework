#pragma once

#include <optional>
#include "stdIncludes.h"

namespace bloom {
	class Scene;
	namespace systems {
		class BLOOMFRAMEWORK_API System {
		public:
			System(bloom::Scene & sceneObject);
			virtual ~System() = default;

			virtual void update(std::optional<double> deltaTime = std::nullopt) = 0;

			bool enabled = true;
		protected:
			bloom::Scene & parentScene;
			entt::Registry<size_t> & m_registry;
		};

		using DefaultSystem = System;
	}
}
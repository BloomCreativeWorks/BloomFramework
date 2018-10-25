#pragma once

#include <optional>
#include "stdIncludes.h"

namespace bloom {
	class Screen;
	namespace systems {
		class BLOOMFRAMEWORK_API DefaultSystem {
		public:
			DefaultSystem(bloom::Screen & screenObject);;

			virtual void update(std::optional<double> deltaTime = std::nullopt) = 0;

		protected:
			bloom::Screen & parentScreen;
			entt::DefaultRegistry & m_registry;
		};

		using System = DefaultSystem;
	}
}
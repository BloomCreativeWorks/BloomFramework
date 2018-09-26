#pragma once

#include "stdIncludes.h"
#include "Components/Components.h"

namespace bloom {
	class RenderSystem {
	public:
		void update(entt::DefaultRegistry & registry);
	};
}
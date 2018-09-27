#pragma once

#include "stdIncludes.h"
#include "Components/Components.h"

namespace bloom {
	class BLOOMFRAMEWORK_API RenderSystem {
	public:
		void update(entt::DefaultRegistry & registry);
	};
}
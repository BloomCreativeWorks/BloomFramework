#pragma once

#include "stdIncludes.h"

namespace BloomFramework {
	class BLOOMFRAMEWORK_API Collision {
	public:
		static bool AABB(const SDL_Rect& a, const SDL_Rect& b);
	};
}
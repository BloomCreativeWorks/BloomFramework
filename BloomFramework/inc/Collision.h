#pragma once

#include "stdIncludes.h"
#include "ECS\ColliderComponent.h"


namespace BloomFramework {
	class BLOOMFRAMEWORK_API Collision {
	public:
		static bool AABB(const SDL_Rect& a, const SDL_Rect& b);
		static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
	};
}
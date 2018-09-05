#pragma once

#include "../stdIncludes.h"
#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "../Game.h"

namespace BloomFramework {
	class BLOOMFRAMEWORK_API ColliderComponent : public Component {
	public:
		SDL_Rect collider;
		std::string tag;
		TransformComponent * transform;
		Game* gameObject;
		ColliderComponent(Game* gameObject,std::string t) : gameObject(gameObject), tag(t) {}

		void init() override;

		void update() override;
	};
}
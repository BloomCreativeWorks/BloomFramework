#pragma once

#include "stdIncludes.h"
#include "Components/Components.h"
#include "DefaultSystem.h"

namespace bloom::systems {
	class AnimationSystem : public System {
		using AnimationPtr = bloom::components::AnimationPtr;
		using Sprite = bloom::components::Sprite;
		using System::DefaultSystem;

	public:
		void update(std::optional<double> deltaTime = 0.0f) {
			m_registry.view<AnimationPtr>().each(
				[&](auto entity, AnimationPtr& anim) { // TODO: use reference instead of creating copy of object
					m_registry.replace<Sprite>(entity, anim->update(deltaTime.value()));
				}
			);
		}
	};
}
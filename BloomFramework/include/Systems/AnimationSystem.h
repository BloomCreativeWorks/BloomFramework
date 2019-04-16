#pragma once

#include "stdIncludes.h"
#include "Components/Components.h"
#include "DefaultSystem.h"

namespace bloom::systems {
	class AnimationSystem : public System {
		using AnimationPtr = bloom::components::AnimationPtr;
		using AnimationSet = bloom::components::AnimationSet;
		using Sprite = bloom::components::Sprite;
		using System::DefaultSystem;

	public:
		void update(uint64_t deltaTime = 0) override {
			m_registry.view<AnimationPtr>().each(
				[this, deltaTime](auto entity, AnimationPtr& animation) {
					if (m_registry.has<AnimationSet>(entity))
						if (auto currentAnimation = m_registry.get<AnimationSet>(entity).getCurrent(); currentAnimation)
							animation = currentAnimation;
					m_registry.replace<Sprite>(entity, animation->update(deltaTime));
				}
			);
		}
	};
}
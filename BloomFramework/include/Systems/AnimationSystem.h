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
		void update(std::optional<double> deltaTime = 0.0) override {
			m_registry.view<AnimationPtr>().each(
				[&](auto entity, AnimationPtr& anim) { 
					if (m_registry.has<AnimationSet>(entity)) {
						AnimationPtr newAnim = m_registry.get<AnimationSet>(entity).getCurrentAnimation();
						if (newAnim) 
							anim = newAnim;
					}
					m_registry.replace<Sprite>(entity, anim->update(deltaTime.value()));
				}
			);
		}
	};
}
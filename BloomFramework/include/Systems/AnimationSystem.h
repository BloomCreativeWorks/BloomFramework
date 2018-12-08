#pragma once

#include "stdIncludes.h"
#include "Components/Components.h"
#include "DefaultSystem.h"

namespace bloom::systems {
	class AnimationSystem : public System {
		using Animation = bloom::components::Animation;
		using Sprite = bloom::components::Sprite;
		using System::DefaultSystem;

	public:
		void update(std::optional<double> deltaTime = 0.0f) {
			m_registry.view<Animation>().each(
				[&](auto entity, Animation anim) {
					m_registry.replace<Sprite>(entity, anim.update(deltaTime.value()));
				}
			);
		}
	};

}
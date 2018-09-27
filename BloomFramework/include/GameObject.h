#pragma once

#include "stdIncludes.h"
#include "Components/Components.h"

namespace bloom {
	class BLOOMFRAMEWORK_API GameObject {
	public:
		GameObject(entt::DefaultRegistry & registry);
		~GameObject();

		template <typename Component, typename... Args>
		void assignComponent(Args &&... arguments) {
			m_registry.assign<Component>(m_entity, std::forward<Args>(arguments)...);
		}
		template <typename Component>
		void removeComponent() {
			m_registry.reset<Component>(m_entity);
		}

	protected:
		entt::DefaultRegistry & m_registry;
		uint32_t m_entity;
	};
}
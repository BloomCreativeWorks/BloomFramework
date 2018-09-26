#pragma once

#include "stdIncludes.h"

namespace bloom {
	class GameObject {
	public:
		GameObject(entt::DefaultRegistry & registry);
		~GameObject();

	protected:
		entt::DefaultRegistry & m_registry;
		uint32_t m_entity;
	};
}
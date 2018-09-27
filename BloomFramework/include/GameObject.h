#pragma once

#include "stdIncludes.h"
#include "Components/Components.h"
#include "Game.h"

namespace bloom {
	class BLOOMFRAMEWORK_API GameObject {
	public:
		GameObject(entt::DefaultRegistry & registry, Game *& gameInstance);

		virtual void init() {}

		~GameObject();

	protected:
		entt::DefaultRegistry & m_registry;
		Game *& m_gameInstance;
		uint32_t m_entity;
	};
}
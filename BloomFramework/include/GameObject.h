#pragma once

#include "stdIncludes.h"
#include "Components/Components.h"
#include "Game.h"

namespace bloom {
	/*
	* This class is used to make a sort of prefab object.
	*
	* This class by default will create an entity with the registry provided.
	* The entity will be assigned with bloom::Position since it is expected that an entity would have position.
	*
	* Use the init() function to assign/replace/reset any Components required.
	*
	* The destructor will automatically destroy the entity from the registry when GameObject gets out of scope.
	*/
	class GameObject {
	public:
		GameObject(entt::registry& registry, Game*& gameInstance) : m_registry(registry), c_gameInstance(gameInstance) {
			m_entity = m_registry.create();
			m_registry.assign<components::Position>(m_entity);
			m_registry.assign<components::Size>(m_entity);
		}

		virtual ~GameObject() {
			if (m_registry.valid(m_entity))
				m_registry.destroy(m_entity);
		}

		virtual void init() = 0;

		uint32_t getEntityID() const { return m_entity; }

	protected:
		entt::registry& m_registry;
		Game* const& c_gameInstance;
		uint32_t m_entity;
	};
}
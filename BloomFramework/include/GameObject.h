#pragma once

#include "stdIncludes.h"
#include "Components/Components.h"

namespace bloom {
	class Game;
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
	class BLOOMFRAMEWORK_API GameObject {
		using Transform = bloom::components::Transform;

	public:
		GameObject(entt::DefaultRegistry & registry, Game & gameInstance);
		~GameObject();

		// Implement an init() function pls...

		uint32_t getEntityID();

		entt::DefaultRegistry & m_registry;
		Game & m_gameInstance;
		entt::DefaultRegistry::entity_type m_entity;
	};
}
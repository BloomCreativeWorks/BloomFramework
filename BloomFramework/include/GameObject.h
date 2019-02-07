#pragma once

#include "stdIncludes.h"
#include "Components/Components.h"

namespace bloom {
	class Game;
	/*
	* This class is used to make a sort of prefab object.
	*
	* This class by default will create an entity with the registry provided.
	*
	* The destructor will automatically destroy the entity from the registry when GameObject gets out of scope.
	*/
	struct BLOOMFRAMEWORK_API GameObject {
		entt::DefaultRegistry& registry;
		Game& gameInstance;
		const entt::DefaultRegistry::entity_type entity;

		GameObject(entt::DefaultRegistry& registry, Game& gameInstance);
		~GameObject();
	};
}
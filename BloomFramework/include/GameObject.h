#pragma once

#include "stdIncludes.h"
#include "Components/Components.h"
#include "Game.h"

namespace bloom {
	using namespace components;
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
	public:
		GameObject(entt::DefaultRegistry & registry, Game *& game_instance);
		~GameObject();

		virtual void init() {}

		uint32_t getEntityID();

	protected:
		entt::DefaultRegistry & registry_;
		Game *& game_instance_;
		uint32_t entity_;
	};
}
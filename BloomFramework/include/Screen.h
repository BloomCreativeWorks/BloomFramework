#pragma once
#include "stdIncludes.h"
#include "Game.h"
#include "Systems/Systems.h"
#include "GameObject.h"
#include <unordered_map>
#include <map>
namespace bloom {
	class BLOOMFRAMEWORK_API Screen {
	public:
		Screen(Game& gameInstance);
		void update();

		//Game Object stuff
		template <typename T>
		void addGameObject(std::string tag) {
			static_assert (std::is_base_of<GameObject, T>::value, "Type T passed in is not a GameObject.");
			auto tmp = m_gameObjects.emplace(tag, T(m_registry, m_gameInstance));
			tmp.second.init();
		}

		void destroyGameObject(std::string tag);

		// System stuff
		template <typename T>
		void registerSystem() {
			static_assert (std::is_base_of<System, T>::value, "Type T passed in is not a System.");
		}
		template <typename T>
		void unregisterSystem() {
			static_assert (std::is_base_of<System, T>::value, "Type T passed in is not a System.");
		}

	private:
		std::map<std::string, System> m_systems; // We use map here because we want to iterate in order of insertion.
		std::unordered_map<std::string, GameObject> m_gameObjects;
		entt::DefaultRegistry m_registry;
		Game *& m_gameInstance;
	};
}
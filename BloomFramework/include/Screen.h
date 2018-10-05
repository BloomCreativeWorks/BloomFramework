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
			auto tmp = m_gameObjects.emplace(tag, new T(m_registry, m_gameInstance));
			tmp.second->init();
		}

		void destroyGameObject(std::string tag) {
			m_gameObjects.erase(tag);
		}

		// System stuff
		template <typename T>
		void registerSystem(int index) {
			static_assert (std::is_base_of<System, T>::value, "Type T passed in is not a System.");
			bool found = false;
			for (auto i : m_systems) {
				if (typeid(i) == typeid(T)) { // Need some kind of Type checking here.
					found = true;
					break;
				}
			}
			if (!found)
				m_systems.insert(m_systems.begin + index, new T(m_registry));
			else
				std::clog << "This system is already registered." << std::endl;
		}
		template <typename T>
		void unregisterSystem() {
			static_assert (std::is_base_of<System, T>::value, "Type T passed in is not a System.");
		}

	private:
		std::vector<std::unique_ptr<System>> m_systems;
		std::unordered_map<std::string, std::unique_ptr<GameObject>> m_gameObjects;
		entt::DefaultRegistry m_registry;
		Game *& m_gameInstance;
	};
}
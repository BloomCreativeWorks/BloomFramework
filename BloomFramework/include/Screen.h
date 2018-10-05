#pragma once
#include "stdIncludes.h"
#include "Game.h"
#include "Systems/Systems.h"
#include "GameObject.h"
#include <unordered_map>
#include <map>
#include <algorithm>
#include <typeinfo>

namespace bloom {
	class BLOOMFRAMEWORK_API Screen {
	public:
		Screen(Game *& gameInstance) : m_gameInstance(gameInstance) {}
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
		size_t registerSystem() {
			static_assert (std::is_base_of<System, T>::value, "Type T passed in is not a System.");
			//bool found = false;
			//for (auto i : m_systems) {
			//	if (type_info(i) == type_info(T)) { // Need some kind of Type checking here.
			//		found = true;
			//		break;
			//	}
			//}
			if (auto v = std::find_if(m_systems.begin(), m_systems.end(),
				[](auto & i) -> bool {if (typeid(*i).name() == typeid(T).name()) return true; return false; }); v == m_systems.end())
			{

				m_systems.emplace_back(std::unique_ptr<T>{new T(m_registry)});
				return (m_systems.size() - 1);
			}
			//if (!found)
			//	m_systems.insert(m_systems.begin + index, new T(m_registry));
			else {
				std::clog << "This system is already registered." << std::endl;
				return (v - m_systems.begin());
			}
		}
		template <typename T>
		void unregisterSystem() {
			static_assert (std::is_base_of<System, T>::value, "Type T passed in is not a System.");
		}

	private:
		template<typename T> struct Container : public std::unique_ptr<T> {
			using std::unique_ptr<T>::unique_ptr;
			operator T &() const { return **this; }
		};

		std::vector<Container<System>> m_systems;
		std::unordered_map<std::string, std::unique_ptr<GameObject>> m_gameObjects;
		entt::DefaultRegistry m_registry;
		Game *& m_gameInstance;
	};
}
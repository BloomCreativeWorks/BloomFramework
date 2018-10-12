#pragma once
#include "stdIncludes.h"
#include "Systems/Systems.h"
#include "GameObject.h"
#include <unordered_map>
#include <algorithm>
#include <typeinfo>
namespace bloom {

	class Game;
	/* This class serves as a container for GameObjects and Systems meant for a particular purpose.
	*
	*	 Add the GameObjects and Systems required in the init() function.
	*
	*/
	class BLOOMFRAMEWORK_API Screen {
	public:
		Screen(Game * gameInstance);
		~Screen();
		virtual void init() = 0;
		void update();

		//Game Object stuff
		template <typename T, typename... TArgs>
		void addGameObject(std::string tag, TArgs&&... initArgs) {
			static_assert (std::is_base_of<GameObject, T>::value, "Type T passed in is not a GameObject.");
			m_gameObjects.emplace(tag, new T(m_registry, m_gameInstance));

			auto & tmp = m_gameObjects[tag];
			T* derived = dynamic_cast<T*>(tmp.get());
			if (derived != nullptr)
				derived->init(std::forward<TArgs>(initArgs)...);
		}

		void destroyGameObject(std::string tag);

		// System stuff
		template <typename T>
		size_t registerSystem() {
			static_assert (std::is_base_of<System, T>::value, "Type T passed in is not a System.");
			if (auto v = std::find_if(m_systems.begin(), m_systems.end(),
				[](auto & i) -> bool {if (typeid(*i).name() == typeid(T).name()) return true; return false; }); v == m_systems.end())
			{

				m_systems.emplace_back(std::unique_ptr<T>{new T(m_registry)});
				return (m_systems.size() - 1);
			}
			else {
				std::clog << "This system is already registered." << std::endl;
				return (v - m_systems.begin());
			}
		}
		template <typename T>
		void unregisterSystem() {
			static_assert (std::is_base_of<System, T>::value, "Type T passed in is not a System.");
			if (auto v = std::find_if(m_systems.begin(), m_systems.end(),
				[](auto & i) -> bool {if (typeid(*i).name() == typeid(T).name()) return true; return false; }); v != m_systems.end())
			{
				m_systems.erase(v);
			}
			else {
				std::clog << "Can't unregister system that isn't registered." << std::endl;
			}
		}

		SDL_Texture *& getScreenTexture();

	private:
		template<class T> using SysPtr = std::unique_ptr<T>;
		void m_createTexture();
		std::vector<SysPtr<System>> m_systems;
		std::unordered_map<std::string, std::unique_ptr<GameObject>> m_gameObjects;
		entt::DefaultRegistry m_registry;
		Game * m_gameInstance;
		SDL_Texture * m_screenTexture;
	};

	using ScrPtr = std::shared_ptr<Screen>;
}
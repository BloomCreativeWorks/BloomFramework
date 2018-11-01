#pragma once

#include <unordered_map>
#include <algorithm>
#include <typeinfo>
#include "stdIncludes.h"
#include "Systems/Systems.h"
#include "GameObject.h"

namespace bloom {

	class Game;
	/* This class serves as a container for GameObjects and Systems meant for a particular purpose.
	*
	*	 Add the GameObjects and Systems required in the init() function.
	*
	*/
	class BLOOMFRAMEWORK_API Screen {
		using System = bloom::systems::System;
		//friend bloom::systems::DefaultSystem::DefaultSystem(bloom::Screen & screenObject);

	public:
		Screen(Game * gameInstance);
		~Screen();
		virtual void init() = 0;
		void update();
		SDL_Renderer * getGameRenderer();
		SDL_Texture * getScreenTexture();

		//Game Object stuff
		template <typename GO, typename... TArgs>
		void addGameObject(const std::string & tag, TArgs&&... initArgs);

		void destroyGameObject(const std::string & tag);

		// System stuff
		template <typename S>
		size_t registerSystem();

		template <typename S>
		void unregisterSystem();

	protected:
		std::vector<std::unique_ptr<System>> m_systems;
		std::unordered_map<std::string, std::unique_ptr<GameObject>> m_gameObjects;
		entt::DefaultRegistry m_registry;
		Game * m_gameInstance;
		SDL_Texture * m_screenTexture;
	};

	using ScrPtr = std::shared_ptr<Screen>;

	//Game Object stuff

	template<typename GO, typename ...TArgs>
	void Screen::addGameObject(const std::string & tag, TArgs && ...initArgs) {
		static_assert (std::is_base_of_v<GameObject, GO>, "Type GO passed in is not a GameObject.");

		GO* obj = new GO(m_registry, m_gameInstance);
		obj->init(std::forward<TArgs>(initArgs)...);;

		m_gameObjects.emplace(tag, std::unique_ptr(obj));

		//auto & tmp = m_gameObjects[tag];
		//GO* derived = dynamic_cast<GO*>(tmp.get());
		////if (derived != nullptr)
		//	derived->init(std::forward<TArgs>(initArgs)...);
	}

	// System stuff

	template<typename S>
	size_t Screen::registerSystem() {
		static_assert (std::is_base_of_v<System, S>, "Type S passed in is not a System.");
		if (auto v = std::find_if(m_systems.begin(), m_systems.end(),
			[](auto & i) -> bool {if (typeid(*i).name() == typeid(S).name()) return true; return false; }); v == m_systems.end())
		{

			m_systems.emplace_back(std::unique_ptr<S>{new S(*this)});
			return (m_systems.size() - 1);
		}
		else {
			std::clog << "This system is already registered." << std::endl;
			return (v - m_systems.begin());
		}
	}
	template<typename S>
	void Screen::unregisterSystem() {
		static_assert (std::is_base_of_v<System, S>, "Type S passed in is not a System.");
		if (auto v = std::find_if(m_systems.begin(), m_systems.end(),
			[](auto & i) -> bool {if (typeid(*i).name() == typeid(S).name()) return true; return false; }); v != m_systems.end())
		{
			m_systems.erase(v);
		}
		else {
			std::clog << "Can't unregister system that isn't registered." << std::endl;
		}
	}
}
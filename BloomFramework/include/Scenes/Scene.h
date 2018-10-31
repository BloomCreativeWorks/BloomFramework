#pragma once

#include "stdIncludes.h"
#include "Systems/DefaultSystem.h"
#include "GameObject.h"

namespace bloom {
	class SceneManager;
	class BLOOMFRAMEWORK_API Scene {
	public:
		Scene(SceneManager & sceneManager);
		virtual void update() = 0;
		virtual void draw() = 0; // May not need this since we use a render system on a Texture.
		virtual void load() = 0;
		virtual void unload() = 0;

		//Game Object stuff
		template <typename T, typename... TArgs> void addGameObject(std::string tag, TArgs&&... initArgs);
		void destroyGameObject(std::string tag);
		
		// System stuff
		template <typename T> size_t registerSystem();
		template <typename T> void unregisterSystem();

	protected:
		SceneManager & m_sceneManager;
		Game & m_gameInstance;
		entt::DefaultRegistry m_registry;
		SDL_Texture * m_sceneTexture;
	};

	using System = bloom::System;
	template<typename T, typename ...TArgs> void Scene::addGameObject(std::string tag, TArgs && ...initArgs) {
		static_assert (std::is_base_of<GameObject, T>::value, "Type T passed in is not a GameObject.");
		m_gameObjects.emplace(tag, new T(m_registry, m_gameInstance));

		auto & tmp = m_gameObjects[tag];
		T* derived = dynamic_cast<T*>(tmp.get());
		if (derived != nullptr)
			derived->init(std::forward<TArgs>(initArgs)...);
	}

	// System stuff
	template<typename T> size_t Scene::registerSystem() {
		static_assert (std::is_base_of<System, T>::value, "Type T passed in is not a System.");
		if (auto v = std::find_if(m_systems.begin(), m_systems.end(),
			[](auto & i) -> bool {if (typeid(*i).name() == typeid(T).name()) return true; return false; }); v == m_systems.end())
		{

			m_systems.emplace_back(std::unique_ptr<T>{new T(*this)});
			return (m_systems.size() - 1);
		}
		else {
			std::clog << "This system is already registered." << std::endl;
			return (v - m_systems.begin());
		}
	}
	template<typename T> void Scene::unregisterSystem() {
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
}


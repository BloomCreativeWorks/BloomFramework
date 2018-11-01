#pragma once

#include "stdIncludes.h"
#include "Systems/DefaultSystem.h"
#include "GameObject.h"

namespace bloom {
	class SceneManager;

	class BLOOMFRAMEWORK_API Scene {
		using System = bloom::systems::System;
		friend bloom::systems::DefaultSystem::DefaultSystem(bloom::Scene & screenObject);
		
	public:
		Scene(SceneManager & sceneManager);

		void update();
		virtual void draw() = 0; // May not need this since we use a render system on a Texture.
		virtual void load() = 0;
		virtual void unload() = 0;
		SDL_Texture * getSceneTexture() { return m_sceneTexture; }
		Game & getGameInstance() { return m_gameInstance; }

		//Game Object stuff
		template<typename GO, typename... TArgs> 
		void addGameObject(const std::string & tag, TArgs &&... initArgs);

		//void destroyGameObject(const std::string & tag);
		
		// System stuff
		template<typename S> 
		size_t registerSystem();

		template<typename S> 
		void unregisterSystem();

	protected:
		SceneManager & m_sceneManager;
		Game & m_gameInstance;
		entt::DefaultRegistry m_registry;
		std::vector<std::unique_ptr<System>> m_systems;
		std::unordered_map<std::string, std::unique_ptr<GameObject>> m_gameObjects;
		SDL_Texture * m_sceneTexture;
	};

	template<typename GO, typename... TArgs> void Scene::addGameObject(const std::string & tag, TArgs &&... initArgs) {
		static_assert(std::is_base_of_v<GameObject, GO>, "Type GO passed in is not a GameObject.");

		GO* obj = new GO(m_registry, m_gameInstance);
		obj->init(std::forward<TArgs>(initArgs)...);

		m_gameObjects.emplace(tag, std::unique_ptr<GO>(obj));

		//auto & tmp = m_gameObjects[tag];
		//GO* derived = dynamic_cast<GO*>(tmp.get());
		////if (derived != nullptr) // we just already emplaced object, nullptr will never be returned
		//	derived->init(std::forward<TArgs>(initArgs)...);
	}

	// System stuff
	template<typename S> size_t Scene::registerSystem() {
		static_assert (std::is_base_of_v<System, S>, "Type S passed in is not a System.");
		if (auto v = std::find_if(m_systems.begin(), m_systems.end(),
			[](auto & i) -> bool {if (typeid(*i).name() == typeid(S).name()) return true; return false; });
			v == m_systems.end())
		{
			m_systems.emplace_back(std::unique_ptr<S>(new S(*this)));
			return (m_systems.size() - 1);
		}
		else {
			std::clog << "This system is already registered." << std::endl;
			return (v - m_systems.begin());
		}
	}
	template<typename S> void Scene::unregisterSystem() {
		static_assert (std::is_base_of_v<System, S>, "Type S passed in is not a System.");
		if (auto v = std::find_if(m_systems.begin(), m_systems.end(),
			[](auto & i) -> bool {if (typeid(*i).name() == typeid(S).name()) return true; return false; });
			v != m_systems.end())
		{
			m_systems.erase(v);
		}
		else {
			std::clog << "Can't unregister system that isn't registered." << std::endl;
		}
	}
}


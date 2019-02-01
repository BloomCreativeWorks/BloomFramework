#pragma once

#include "stdIncludes.h"
#include "Systems/DefaultSystem.h"
#include "GameObject.h"
#include "Exception.h"
#include "Components/LayerGroup.h"
#include "StdStableSort.h"

namespace bloom {
	class BLOOMFRAMEWORK_API SceneManager;
	struct BLOOMFRAMEWORK_API Coord;
	
	class BLOOMFRAMEWORK_API Scene {
		using System = bloom::systems::DefaultSystem;
		friend bloom::systems::System::System(bloom::Scene & sceneObject);

	public:
		Scene(SceneManager & sceneManager);
		~Scene();

		void update(double deltaTime);
		void draw();
		void start();
		void restart();
		virtual void load() = 0;

		Game & getGameInstance() { return m_gameInstance; }

		//Game Object stuff
		template<typename GO, typename InitFunc, typename... TArgs>
		void addGameObject(const std::string & tag, InitFunc init, TArgs &&... initArgs);

		void destroyGameObject(const std::string & tag);

		void destroyAllGameObjects();

		// System stuff
		template<typename S>
		std::shared_ptr<S> registerSystem();

		template<typename S>
		void unregisterSystem();

		void unregisterAllSystems();
		
		template<typename S>
		std::shared_ptr<S> getSystemPtr();

		// Rotation stuff
		void setSceneRotation(double angle);
		void adjustSceneRotation(double adjustment);
		double getSceneRotation();
		void setSceneRotationCenter(Coord center);
		void setSceneRotationCenter(SDL_Point center);

		bool isLoaded() { return m_sceneLoaded; }

	protected:
		SceneManager & m_sceneManager;
		Game & m_gameInstance;
		entt::DefaultRegistry m_registry;
		std::vector<std::shared_ptr<System>> m_systems;
		std::unordered_map<std::string, std::unique_ptr<GameObject>> m_gameObjects;
		SDL_Texture * m_sceneTexture;

		double m_sceneRotateAngle = 0.0;
		SDL_Point m_sceneRotateCenter;

		bool m_sceneLoaded = false;
	};

	template<typename GO, typename InitFunc, typename... TArgs>
	void Scene::addGameObject(const std::string & tag, InitFunc init, TArgs &&... initArgs) {
		static_assert(std::is_base_of_v<GameObject, GO>, "Type GO passed in is not GameObject based");

		GO* obj = new GO(m_registry, m_gameInstance);
		if constexpr (std::is_member_function_pointer_v<InitFunc>)
			(obj->*init)(std::forward<TArgs>(initArgs)...);
		else
			init(obj, std::forward<TArgs>(initArgs)...); // std::mem_fn

		m_gameObjects.emplace(tag, std::unique_ptr<GO>(obj));

		m_registry.sort<components::LayerGroup, std::less<components::LayerGroup>, misc::StdStableSort>(std::less<components::LayerGroup>{});
	}

	// System stuff
	template<typename S> std::shared_ptr<S> Scene::registerSystem() {
		static_assert (std::is_base_of_v<System, S>, "Type S passed in is not System based");
		if (auto v = std::find_if(m_systems.begin(), m_systems.end(),
			[](auto & i) -> bool { return typeid(*i) == typeid(S); });
			v == m_systems.end())
		{
			return std::dynamic_pointer_cast<S>(m_systems.emplace_back(std::make_shared<S>(*this)));
		}
		else {
			std::clog << "This system is already registered." << std::endl;
			return std::dynamic_pointer_cast<S>(*v);
		}
	}

	template<typename S> void Scene::unregisterSystem() {
		static_assert (std::is_base_of_v<System, S>, "Type S passed in is not System based");
		if (auto v = std::find_if(m_systems.begin(), m_systems.end(),
			[](auto & i) -> bool { return typeid(*i) == typeid(S); });
			v != m_systems.end())
		{
			m_systems.erase(v);
		}
		else {
			std::clog << "Can't unregister system that isn't registered." << std::endl;
		}
	}

	template<typename S>
	std::shared_ptr<S> Scene::getSystemPtr()
	{
		static_assert (std::is_base_of_v<System, S>, "Type S passed in is not System based");
		if (auto v = std::find_if(m_systems.begin(), m_systems.end(),
			[](auto & i) -> bool { return typeid(*i) == typeid(S); });
			v != m_systems.end())
		{
			return std::dynamic_pointer_cast<S>(*v);
		}
		else {
			throw Exception("[Scene getSystemPtr] Unable to get System, it is not registered.");
		}
	}

}
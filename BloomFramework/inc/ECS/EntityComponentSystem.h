#pragma once

#include "../stdIncludes.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

namespace BloomFramework {
	class Component;
	class Entity;
	class Manager;

	using ComponentID = std::size_t;
	using Group = std::size_t;

	inline ComponentID getNewComponentTypeID() {
		static ComponentID lastID = 0u;
		return lastID++;
	}

	template <typename T> inline ComponentID getComponentTypeID() noexcept {
		static_assert (std::is_base_of<Component, T>::value, "");
		static ComponentID typeID = getNewComponentTypeID();
		return typeID;
	}

	constexpr std::size_t maxComponents = 32;
	constexpr std::size_t maxGroups = 32;

	using ComponentBitset = std::bitset<maxComponents>;
	using GroupBitset = std::bitset<maxGroups>;

	using ComponentArray = std::array<Component*, maxComponents>;

	class BLOOMFRAMEWORK_API Component {
	public:
		Entity* entity;
		virtual void init() {}
		virtual void update() {}
		virtual void draw() {}
	};

	class BLOOMFRAMEWORK_API Entity {
	public:
		Entity() = default;
		Entity(Manager& manager) : manager(manager) {};
		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;
		void update();
		void draw();
		bool isActive() const;
		void destory();
		bool hasGroup(Group mGroup);
		void addGroup(Group mGroup);
		void delGroup(Group mGroup);


		template <typename T> bool hasComponent() const { return componentBitset[getComponentTypeID<T>()]; }

		template <typename T, typename... TArgs>
		T& addComponent(TArgs&&... mArgs) {
			T* c(new T(std::forward<TArgs>(mArgs)...));
			c->entity = this;
			std::unique_ptr<Component> uPtr{ c };
			components.emplace_back(std::move(uPtr));

			componentArray[getComponentTypeID<T>()] = c;
			componentBitset[getComponentTypeID<T>()] = true;

			c->init();
			return *c;
		}

		template<typename T> T& getComponent() const {
			auto ptr(componentArray[getComponentTypeID<T>()]);
			return *static_cast<T*>(ptr);
		}

	private:
		Manager& manager;
		bool active = true;
		std::vector<std::unique_ptr<Component>> components;
		ComponentArray componentArray;
		ComponentBitset componentBitset;
		GroupBitset groupBitset;
	};

	class BLOOMFRAMEWORK_API Manager {
	public:
		Manager() = default;
		Manager(const Manager&) = delete;
		Manager& operator=(const Manager&) = delete;
		void update();
		void draw();
		void refresh();
		void addToGroup(Entity* mEntity, Group mGroup);
		std::vector<Entity*>& getGroup(Group mGroup);
		Entity& addEntity();

	private:
		std::vector<std::unique_ptr<Entity>> entities;
		std::array<std::vector<Entity*>, maxGroups> groupedEntities;
	};
}
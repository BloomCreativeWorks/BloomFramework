#pragma once

#include "../stdIncludes.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

namespace BloomFramework {
	class BLOOMFRAMEWORK_API Component;
	class BLOOMFRAMEWORK_API Entity;

	using ComponentID = std::size_t;

	inline ComponentID getComponentTypeID() {
		static ComponentID lastID = 0;
		return lastID++;
	}

	template <typename T> inline ComponentID getComponentTypeID() noexcept {
		static ComponentID typeID = getComponentTypeID();
		return typeID;
	}

	constexpr std::size_t maxComponents = 32;

	using ComponentBitSet = std::bitset<maxComponents>;
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
		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;
		void update();
		void draw();
		bool isActive() const;
		void destory();

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
		bool active = true;
		std::vector<std::unique_ptr<Component>> components;
		ComponentArray componentArray;
		ComponentBitSet componentBitset;
	};

	class BLOOMFRAMEWORK_API Manager {
	public:
		Manager() = default;
		Manager(const Manager&) = delete;
		Manager& operator=(const Manager&) = delete;
		void update();
		void draw();
		void refresh();
		Entity& addEntity();

	private:
		std::vector<std::unique_ptr<Entity>> entities;
	};
}
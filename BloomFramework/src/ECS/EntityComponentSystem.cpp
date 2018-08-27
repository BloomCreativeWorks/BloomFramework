#include "../../inc/ECS/EntityComponentSystem.h"

inline void BloomFramework::Entity::update() { for(auto& c : components) c->update(); }

inline void BloomFramework::Entity::draw() { for(auto& c : components) c->draw(); }

inline bool BloomFramework::Entity::isActive() const { return active; }

inline void BloomFramework::Entity::destory() { active = false; }

inline void BloomFramework::Manager::update() {
	for(auto& e : entities) e->update();
}

inline void BloomFramework::Manager::draw() {
	for(auto& e : entities) e->draw();
}

inline void BloomFramework::Manager::refresh() {
	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
																[](const std::unique_ptr<Entity> &mEntity) {return !mEntity->isActive(); }),
								 std::end(entities));
}

inline BloomFramework::Entity & BloomFramework::Manager::addEntity() {
	Entity* e = new Entity();
	std::unique_ptr<Entity> uPtr{ e };
	entities.emplace_back(std::move(uPtr));

	return *e;
}

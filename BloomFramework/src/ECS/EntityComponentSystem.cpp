#include "../../inc/ECS/EntityComponentSystem.h"

inline void BloomFramework::Entity::update() { for(auto& c : components) c->update(); }

inline void BloomFramework::Entity::draw() { for(auto& c : components) c->draw(); }

inline bool BloomFramework::Entity::isActive() const { return active; }

inline void BloomFramework::Entity::destory() { active = false; }

inline bool BloomFramework::Entity::hasGroup(Group mGroup) {
	return groupBitset[mGroup];
}

inline void BloomFramework::Entity::addGroup(Group mGroup) {
	groupBitset[mGroup] = true;
	manager.addToGroup(this, mGroup);
}

inline void BloomFramework::Entity::delGroup(Group mGroup) { groupBitset[mGroup] = false; }

inline void BloomFramework::Manager::update() {
	for(auto& e : entities) e->update();
}

inline void BloomFramework::Manager::draw() {
	for(auto& e : entities) e->draw();
}

inline void BloomFramework::Manager::refresh() {
	for(auto i(0u); i < maxGroups; i++) {
		auto& v(groupedEntities[i]);
		v.erase(std::remove_if(std::begin(v), std::end(v),
													 [i](Entity* mEntity) {return !mEntity->isActive() || mEntity->hasGroup(i); }),
						std::end(v));
	}

	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
																[](const std::unique_ptr<Entity> &mEntity) {return !mEntity->isActive(); }),
								 std::end(entities));
}

inline void BloomFramework::Manager::addToGroup(Entity * mEntity, Group mGroup) {
	groupedEntities[mGroup].emplace_back(mEntity);
}

inline std::vector<BloomFramework::Entity*>& BloomFramework::Manager::getGroup(Group mGroup) {
	return groupedEntities[mGroup];
}

inline BloomFramework::Entity & BloomFramework::Manager::addEntity() {
	Entity* e = new Entity(*this);
	std::unique_ptr<Entity> uPtr{ e };
	entities.emplace_back(std::move(uPtr));

	return *e;
}

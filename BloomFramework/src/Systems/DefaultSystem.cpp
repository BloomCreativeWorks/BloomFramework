#include "Systems/DefaultSystem.h"
#include "Scenes/Scene.h"

namespace bloom::systems {
	DefaultSystem::DefaultSystem(bloom::Scene & sceneObject) : parentScene(sceneObject), m_registry(sceneObject.m_registry) {}
}
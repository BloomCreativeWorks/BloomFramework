#include "Systems/DefaultSystem.h"
#include "Scenes/Scene.h"

namespace bloom::systems {
	DefaultSystem::DefaultSystem(bloom::Scene & screenObject) : parentScreen(screenObject), m_registry(screenObject.m_registry) {}
}
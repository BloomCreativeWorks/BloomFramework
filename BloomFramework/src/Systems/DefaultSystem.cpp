#include "Systems/DefaultSystem.h"
#include "Scenes/Scene.h"

namespace bloom::systems {
	System::System(bloom::Scene & sceneObject) : parentScene(sceneObject), m_registry(sceneObject.m_registry) {}
}
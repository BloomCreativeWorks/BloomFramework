#include "Systems/DefaultSystem.h"
#include "Screen.h"

namespace bloom::systems {
	DefaultSystem::DefaultSystem(bloom::Screen & screenObject) : parentScreen(screenObject), m_registry(screenObject.m_registry) {}
}
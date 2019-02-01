#pragma once
#include "Scenes/Scene.h"
#include "GameObjectTest/TestGameObject.h"
#include "GameObjectTest/SceneRotateSystem.h"
#include "GameObjectTest/SpriteRotatorSystem.h"
#include "GameObjectTest/RandomizerSystem.h"
#include "GameObjectTest/TestAnimatedGameObject.h"
#include "GameObjectTest/AnimationChangerSystem.h"

class TestScene : public bloom::Scene {
	using RenderSystem = bloom::systems::RenderSystem;
	using Position = bloom::components::Position;
	using Size = bloom::components::Size;
	using AnimationSystem = bloom::systems::AnimationSystem;

public:
	using bloom::Scene::Scene;

	void load() override {
		namespace fs = std::filesystem;
		fs::path workingDir = fs::path(getExePath());
		fs::path assetsDir = L"data\\Assets";
		fs::path spriteSheetPath = workingDir / assetsDir / "OverworldTestSpritesheet.png";
		fs::path testCharPath = workingDir / assetsDir / "TestChar.png";

		addGameObject<TestChar>("testSprite", &TestChar::init, Position(10, 10), Size{ 128, 128 }, spriteSheetPath, SDL_Rect{ 0, 0, 32, 32 }, 0);
		addGameObject<TestChar>("testSprite2", std::mem_fn(&TestChar::init), Position(0, 0, bloom::relative), Size{ 128, 128 }, testCharPath, SDL_Rect{ 0, 0, 32, 32 }, 2);
		addGameObject<TestChar>("testGO", &TestChar::init, Position(50, 50, bloom::relative, (bloom::middle | bloom::right)), Size{ 256, 256 }, testCharPath, SDL_Rect{ 64, 96, 32, 32 }, 3);
		addGameObject<TestAnimChar>("testAnimatedSprite", &TestAnimChar::init, testCharPath);

		registerSystem<RandomPositionSystem>()->enabled = false; // Still wonky because of Coord change. We also don't want to start it immediately.
		registerSystem<RenderSystem>();
		registerSystem<SceneRotateSystem>(); // Do barrel rolls!!!
		registerSystem<SpriteRotatorSystem>();
		registerSystem<AnimationChangerSystem>();
		registerSystem<AnimationSystem>();
	}
};
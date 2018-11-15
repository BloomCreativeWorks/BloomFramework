#pragma once
#include "Scenes/Scene.h"
#include "GameObjectTest/TestGameObject.h"
#include "GameObjectTest/SceneRotateSystem.h"
#include "GameObjectTest/SpriteRotatorSystem.h"
#include "GameObjectTest/RandomizerSystem.h"

class TestScene : public bloom::Scene {
	using RenderSystem = bloom::systems::RenderSystem;
	using Position = bloom::components::Position;
	using Size = bloom::components::Size;

public:
	using bloom::Scene::Scene;

	~TestScene() {
		unload();
	}

	void load() override {
		namespace fs = std::filesystem;
		fs::path workingDir = fs::path(getExePath());
		fs::path assetsDir = L"data\\Assets";
		fs::path spriteSheetPath = workingDir / assetsDir / "OverworldTestSpritesheet.png";
		fs::path testCharPath = workingDir / assetsDir / "TestChar.png";

		addGameObject<TestChar>("testSprite", Position(10, 10), Size(128, 128), spriteSheetPath, SDL_Rect{ 0, 0, 32, 32 });
		addGameObject<TestChar>("testSprite2", Position(0, 0, bloom::relative), Size(128, 128), testCharPath, SDL_Rect{ 0, 0, 32, 32 }, 2);
		addGameObject<TestChar>("testGO", Position(50, 50, bloom::relative, (bloom::middle | bloom::right)), Size(256, 256), testCharPath, SDL_Rect{ 64, 96, 32, 32 }, 3);

		registerSystem<RandomPositionSystem>(); // Still wonky because of Coord change.
		registerSystem<RenderSystem>();
		registerSystem<SceneRotateSystem>(); // Do barrel rolls!!!
		registerSystem<SpriteRotatorSystem>();
	}

	void unload() override {
		destroyGameObject("testSprite");
		destroyGameObject("testSprite2");
		destroyGameObject("testGO");

		unregisterSystem<RenderSystem>();
		unregisterSystem<SceneRotateSystem>();
		unregisterSystem<RandomPositionSystem>();
		unregisterSystem<SpriteRotatorSystem>();
	}
};
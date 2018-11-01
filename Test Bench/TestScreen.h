#pragma once
#include "Scenes/Scene.h"
#include "GameObjectTest/TestGameObject.h"

class TestScreen : public bloom::Scene {
	using RenderSystem = bloom::systems::RenderSystem;
	using Position = bloom::components::Position;
	using Size = bloom::components::Size;
public:
	using bloom::Scene::Scene;

	void draw() override {}

	void load() override {
		addGameObject<TestChar>("testSprite", Position( 10,10 ), Size( 128,128 ), "Assets/OverworldTestSpritesheet.png", SDL_Rect{ 0,0,32,32 });
		addGameObject<TestChar>("testSprite2", Position(0, 0, relative), Size(128, 128), "Assets/TestChar.png", SDL_Rect{ 0, 0, 32, 32 },2);
		addGameObject<TestChar>("testGO", Position(50, 50, relative, (middle|right)), Size(256, 256), "Assets/TestChar.png", SDL_Rect{ 64, 96, 32, 32 },3);

		//registerSystem<RandomPositionSystem>();
		registerSystem<RenderSystem>();
	}

	void unload() override {}
};
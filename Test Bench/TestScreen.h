#pragma once
#include "Screen.h"
#include "GameObjectTest/TestGameObject.h"
class TestScreen : public bloom::Screen {
public:
	using bloom::Screen::Screen;

	void Screen::init() {
		addGameObject<TestChar>("testSprite", SDL_Rect{ 0,0,128,128 }, "Assets/OverworldTestSpritesheet.png", SDL_Rect{ 0,0,32,32 });
		addGameObject<TestChar>("testSprite2", SDL_Rect{ 128,0,128,128 }, "Assets/TestChar.png", SDL_Rect{ 0, 0, 32, 32 });
		addGameObject<TestChar>("testGO", SDL_Rect{ 50,50,256,256 }, "Assets/TestChar.png", SDL_Rect{ 64, 96, 32, 32 });

		registerSystem<RandomPositionSystem>();
		registerSystem<RenderSystem>();
	}
};
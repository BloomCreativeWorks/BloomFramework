#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

class TestChar : public bloom::GameObject {
	using bloom::GameObject::GameObject;
public:
	void Init(SDL_Rect pos_and_size = SDL_Rect{ 50,50, 256, 256 }, const std::string & texture_path = "Assets/TestChar.png", std::optional<SDL_Rect> src_rect = std::nullopt);
	void DisableRandomPos();
	void EnableRandomPos();
};

void TestChar::Init(SDL_Rect pos_and_size, const std::string & texture_path, std::optional<SDL_Rect> src_rect) {
	registry_.replace<bloom::Position>(entity_, pos_and_size.x, pos_and_size.y);
	registry_.assign<bloom::Size>(entity_, pos_and_size.w, pos_and_size.h);
	auto tmp = game_instance_->textures.Load(texture_path);

	registry_.assign<bloom::Sprite>(entity_, tmp, src_rect);
}

void TestChar::DisableRandomPos() {
	registry_.assign<NoRandomPos>(entity_);
}

void TestChar::EnableRandomPos() {
	registry_.reset<NoRandomPos>(entity_);
}
#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

class TestAnimChar : public bloom::GameObject {
	using Position = bloom::components::Position;
	using Size = bloom::components::Size;
	using Sprite = bloom::components::Sprite;
	using Animation = bloom::components::Animation;
	using bloom::GameObject::GameObject;

public:
	void init() override {}

	void init(const std::filesystem::path texturePath = "Assets/TestChar.png") {
		m_registry.replace<Position>(m_entity, 50, 50);
		m_registry.assign<Size>(m_entity, 256, 256);
		auto tmp = m_gameInstance->textures.load(texturePath);

		m_registry.assign<Sprite>(m_entity, tmp, SDL_Rect{ 0,32,32,32 });

		Animation anim;
		
		anim.animationFrames.emplace_back(Sprite(tmp, SDL_Rect{ 0,32,32,32 }));
		anim.animationFrames.emplace_back(Sprite(tmp, SDL_Rect{ 32,32,32,32 }));
		anim.animationFrames.emplace_back(Sprite(tmp, SDL_Rect{ 0,32,32,32 }));
		anim.animationFrames.emplace_back(Sprite(tmp, SDL_Rect{ 64,32,32,32 }));

		anim.setFrameTime(250);

		m_registry.assign<Animation>(m_entity, anim);
		m_registry.assign<NoRandomPos>(m_entity);

	}
};
#pragma once

#include "Framework.h"
#include "RandomComponent.h"

class TestAnimChar : public bloom::GameObject {
	using Position = bloom::components::Position;
	using Size = bloom::components::Size;
	using Sprite = bloom::components::Sprite;
	using AnimationPtr = bloom::components::AnimationPtr;
	using Animation = bloom::components::Animation;
	using AnimationSet = bloom::components::AnimationSet;
	using bloom::GameObject::GameObject;

public:
	void init() override {}

	void init(const std::filesystem::path& texturePath = "Assets/TestChar.png") {
		m_registry.replace<Position>(m_entity, 50, 50);
		m_registry.replace<Size>(m_entity, 256, 256);
		auto tmp = c_gameInstance->textures.load(texturePath);

		m_registry.assign<Sprite>(m_entity, tmp, SDL_Rect{ 0,32,32,32 });


		// Seriously not the best way to initialize object animation.
		AnimationPtr down{ std::make_shared<Animation>() };
		down->animationFrames = {
			Sprite(tmp, SDL_Rect{ 0,32,32,32 }),
			Sprite(tmp, SDL_Rect{ 32,32,32,32 }),
			Sprite(tmp, SDL_Rect{ 0,32,32,32 }),
			Sprite(tmp, SDL_Rect{ 64,32,32,32 })
		};


		AnimationPtr up{ std::make_shared<Animation>() };
		up->animationFrames = {
			Sprite(tmp, SDL_Rect{ 0,0,32,32 }),
			Sprite(tmp, SDL_Rect{ 32,0,32,32 }),
			Sprite(tmp, SDL_Rect{ 0,0,32,32 }),
			Sprite(tmp, SDL_Rect{ 64,0,32,32 })
		};

		AnimationPtr left{ std::make_shared<Animation>() };
		left->animationFrames = {
			Sprite(tmp, SDL_Rect{ 0,64,32,32 }),
			Sprite(tmp, SDL_Rect{ 32,64,32,32 }),
			Sprite(tmp, SDL_Rect{ 0,64,32,32 }),
			Sprite(tmp, SDL_Rect{ 64,64,32,32 })
		};

		AnimationPtr right{ std::make_shared<Animation>() };
		right->animationFrames = {
			Sprite(tmp, SDL_Rect{ 0,96,32,32 }),
			Sprite(tmp, SDL_Rect{ 32,96,32,32 }),
			Sprite(tmp, SDL_Rect{ 0,96,32,32 }),
			Sprite(tmp, SDL_Rect{ 64,96,32,32 })
		};

		up->setFrameTime(250);
		down->setFrameTime(250);
		left->setFrameTime(250);
		right->setFrameTime(250);

		AnimationSet animSet;
		animSet.add("up", up);
		animSet.add("down", down);
		animSet.add("left", left);
		animSet.add("right", right);

		m_registry.assign<AnimationSet>(m_entity, animSet);
		m_registry.assign<AnimationPtr>(m_entity, up);
	}
};
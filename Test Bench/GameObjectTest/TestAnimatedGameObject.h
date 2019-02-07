#pragma once

#include "Framework.h"
#include "NoRandomComponent.h"

class TestAnimChar : public bloom::GameObject {
	using Position = bloom::components::Position;
	using Size = bloom::components::Size;
	using Sprite = bloom::components::Sprite;
	using AnimationPtr = bloom::components::AnimationPtr;
	using Animation = bloom::components::Animation;
	using AnimationSet = bloom::components::AnimationSet;
	using Transform = bloom::components::Transform;
	using GameObject::GameObject;

public:
	void init(const std::filesystem::path& texturePath) {
		Transform trans = { Position(0,0,bloom::relative), 0.0f, Size{256, 256} };
		registry.assign<Transform>(entity, trans);

		auto tmp = gameInstance.textures.load(texturePath);

		registry.assign<Sprite>(entity, tmp, SDL_Rect{ 0,32,32,32 });


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

		registry.assign<AnimationSet>(entity, animSet);
		registry.assign<AnimationPtr>(entity, up);
		registry.assign<NoRandomPos>(entity);
	}
};
#pragma once
#include "../stdIncludes.h"
#include "../Game.h"
#include "Components.h"

namespace BloomFramework {
	class TransformComponent;
	class BLOOMFRAMEWORK_API KeyboardController : public Component {
	public:
		KeyboardController(Game* gameObject) : gameObject(gameObject) {}
		TransformComponent* transform;
		SpriteComponent* sprite;
		void init() override;

		void update() override;

	private:
		Game* gameObject;
	};
}
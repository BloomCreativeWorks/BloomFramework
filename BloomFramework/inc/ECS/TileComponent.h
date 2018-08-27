#pragma once

#include "../stdIncludes.h"
#include <string.h>
#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

namespace BloomFramework {
	class BLOOMFRAMEWORK_API TileComponent : public Component {
	public:
		TileComponent() = default;
		TileComponent(int x, int y, int w, int h, int id);

		void init() override;

		TransformComponent * transform;
		SpriteComponent * sprite;

		SDL_Rect tileRect;
		int tileID;
		char* path;




	};
}
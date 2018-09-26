#pragma once

#include "stdIncludes.h"

namespace bloom {
	struct Position {
		Position(float xPos = 0.0f, float yPos = 0.0f) : x(xPos), y(yPos) {}

		float x, y;
	};
}
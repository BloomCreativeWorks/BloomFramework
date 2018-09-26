#pragma once

#include "stdIncludes.h"

namespace bloom {
	struct Size {
		Size(float w = 1.0f, float h = 1.0f) : w(w), h(h) {}

		float w, h;
	};
}
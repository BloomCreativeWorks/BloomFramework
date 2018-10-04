#pragma once

#include "stdIncludes.h"

namespace bloom {
	struct Size {
		Size(int w = 1, int h = 1) : w(w), h(h) {}

		int w, h;
	};
}
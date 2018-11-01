#pragma once

namespace bloom::components {
	struct Size {
		Size(const Size & other) = default;
		Size(int w = 1, int h = 1) : w(w), h(h) {}

		int w, h;
	};
}
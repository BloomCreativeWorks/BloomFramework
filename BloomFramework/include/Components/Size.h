#pragma once

namespace bloom::components {
	struct Size {
		Size() : w(0), h(0) {}
		Size(int w, int h) : w(w), h(h) {}

		int w, h;
	};
}

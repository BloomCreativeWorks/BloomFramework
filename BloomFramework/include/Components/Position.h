#pragma once

namespace bloom::components {
	struct Position {
		Position(int x = 0, int y = 0) : x(x), y(y) {}

		int x, y;
	};
}
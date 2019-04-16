#pragma once

namespace bloom::components {
	struct Position {
		Position() : x(0), y(0) {}
		Position(int x, int y) : x(x), y(y) {}

		int x, y;
	};
}
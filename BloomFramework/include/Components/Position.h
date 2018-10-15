#pragma once

namespace bloom::components {
	struct Position {
		Position(int x_pos = 0, int y_pos = 0) : x(x_pos), y(y_pos) {}

		int x, y;
	};
} // namespace bloom::components
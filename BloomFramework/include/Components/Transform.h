#pragma once

#include "Coord.h"

namespace bloom::components {
	using Position = bloom::Coord;
	struct Size {
		int w, h;
	};

	struct Transform {
		Position position;

		double rotation;

		Size size;
	};
}
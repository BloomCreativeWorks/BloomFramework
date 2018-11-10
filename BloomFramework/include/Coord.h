#pragma once

#include "stdIncludes.h"

enum CoordType {
	absolute,
	relative
};

enum VerticalPosition {
	top = 1,
	middle = 2,
	bottom = 4,
};

enum HorizontalPosition {
	left = 8,
	center = 16,
	right = 32
};


namespace bloom {
	struct BLOOMFRAMEWORK_API Coord {
	public:
		int x, y;
		int relativeTo;

		Coord();
		Coord(const Coord & other) = default;
		Coord(int x, int y, CoordType type = absolute, int direction = top | left);

		Coord getSDLPos(SDL_Renderer * targetRenderer, int width, int height);
		SDL_Point toSDLPoint(SDL_Renderer * targetRenderer);
	};
}
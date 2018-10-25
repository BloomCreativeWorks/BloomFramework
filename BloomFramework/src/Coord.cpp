#include "Coord.h"

namespace bloom {
	Coord::Coord() : x(0), y(0), relativeTo(middle | center) {}
	Coord::Coord(int x, int y, CoordType type, int direction) : x(x), y(y), relativeTo(direction) {
		if (type == absolute) 
			this->relativeTo = (middle | center);
	}
	Coord Coord::getSDLPos(SDL_Renderer * targetRenderer, int width, int height) {
		int rendererWidth, rendererHeight;
		SDL_RenderGetLogicalSize(targetRenderer, &rendererWidth, &rendererHeight);
		Coord result;

		// Get SDL style X position, factoring object width as well.
		if ((relativeTo & left) == left) 
			result.x = x;
		else if ((relativeTo & center) == center) 
			result.x = rendererWidth / 2 - width / 2 + x;
		else if ((relativeTo & right) == right) 
			result.x = rendererWidth - width - x;
		else 
			result.x = x;

		// Get SDL style Y position, factoring object height as well.
		if ((relativeTo & top) == top)
			result.y = y;
		else if ((relativeTo & middle) == middle) 
			result.y = rendererHeight / 2 - height / 2 - y;
		else if ((relativeTo & bottom) == bottom) 
			result.y = rendererHeight - height - y;

		return result;
	}
}
#pragma once

#include "Components.h"

namespace BloomFramework {
	class BLOOMFRAMEWORK_API PositionComponent : public Component {
	public:
		PositionComponent() : xpos(0), ypos(0) {}
		PositionComponent(int x, int y) : xpos(x), ypos(y) {}
		int x() {
			return xpos;
		}
		int y() {
			return ypos;
		}
		void init() override {}
		void update() override {
			xpos++;
			ypos++;
		}

		void setPos(int x, int y) {
			xpos = x;
			ypos = y;
		}
	private:
		int xpos = 0, ypos = 0;
	};
}

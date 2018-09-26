#pragma once
#include "stdIncludes.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Timer {
	public:
		Timer() : m_startTicks(SDL_GetPerformanceCounter()) {}

		void start();
		void restart();
		Uint64 split();
		Uint64 lap();
		Uint64 totalTime();

	private:
		Uint64 m_startTicks = 0;
	};
}
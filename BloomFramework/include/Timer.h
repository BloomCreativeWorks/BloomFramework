#pragma once

#include "stdIncludes.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Timer {
	public:
		Timer() : start_ticks_(SDL_GetPerformanceCounter()), timer_ticks_(start_ticks_) {}

		static Uint32 totalLifetime();

		void start();
		void restart();
		double split();
		double lap();
		double objectLifetime();

	private:
		Uint64	start_ticks_, timer_ticks_;
	};
}
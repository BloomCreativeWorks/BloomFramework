#pragma once

#include "stdIncludes.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Timer {
	public:
		Timer() : start_ticks_(SDL_GetPerformanceCounter()), timer_ticks_(start_ticks_) {}

		static Uint32 TotalLifetime();

		void Start();
		void Restart();
		double Split();
		double Lap();
		double ObjectLifetime();

	private:
		Uint64	start_ticks_, timer_ticks_;
	};
} // namespace bloom
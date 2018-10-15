#include "Timer.h"

namespace bloom {
	Uint32 Timer::totalLifetime() {
		return SDL_GetTicks();
	}

	void Timer::start() {
		timer_ticks_ = SDL_GetPerformanceCounter();
	}

	void Timer::restart() {
		start();
	}

	double Timer::split() {
		return (static_cast<double>(SDL_GetPerformanceCounter() - timer_ticks_) * 1000.0 / static_cast<double>(SDL_GetPerformanceFrequency()));
	}

	double Timer::lap() {
		Uint64 old_ticks = timer_ticks_;
		timer_ticks_ = SDL_GetPerformanceCounter();
		return (static_cast<double>(timer_ticks_ - old_ticks) * 1000.0 / static_cast<double>(SDL_GetPerformanceFrequency()));
	}

	double Timer::objectLifetime() {
		return (static_cast<double>(SDL_GetPerformanceCounter() - start_ticks_) * 1000.0 / SDL_GetPerformanceFrequency());
	}
}
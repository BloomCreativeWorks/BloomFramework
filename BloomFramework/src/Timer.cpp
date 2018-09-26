#include "Timer.h"

namespace bloom {
	void Timer::start() {
		m_startTicks = SDL_GetPerformanceCounter();
	}

	double Timer::split() {
		return (static_cast<double>(SDL_GetPerformanceCounter() - m_startTicks) / static_cast<double>(SDL_GetPerformanceFrequency()));
	}

	void Timer::restart() {
		m_startTicks = SDL_GetPerformanceCounter(); //this is faster then using start() method
	}

	double Timer::totalTime() {
		return (static_cast<double>(SDL_GetPerformanceCounter()) / static_cast<double>(SDL_GetPerformanceFrequency()));
	}

	double Timer::lap() {
		Uint64 oldTicks = m_startTicks;
		m_startTicks = SDL_GetPerformanceCounter();
		return (static_cast<double>(SDL_GetPerformanceCounter() - oldTicks) / static_cast<double>(SDL_GetPerformanceFrequency()));
	}
}
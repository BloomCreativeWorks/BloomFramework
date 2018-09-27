#include "Timer.h"

namespace bloom {
	void Timer::start() {
		m_timerTicks = SDL_GetPerformanceCounter();
	}

	void Timer::restart() {
		start();
	}

	Uint64 Timer::split() {
		return ((SDL_GetPerformanceCounter() - m_timerTicks) * 1000 / SDL_GetPerformanceFrequency());
	}

	Uint64 Timer::lap() {
		Uint64 oldTicks = m_timerTicks;
		m_timerTicks = SDL_GetPerformanceCounter();
		return ((m_timerTicks - oldTicks) * 1000 / SDL_GetPerformanceFrequency());
	}

	Uint64 Timer::objectLifetime() {
		return ((SDL_GetPerformanceCounter() - m_startTicks) * 1000 / SDL_GetPerformanceFrequency());
	}

	Uint32 Timer::totalLifetime() {
		return SDL_GetTicks();
	}
}
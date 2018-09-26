#include "Timer.h"

namespace bloom {
	void Timer::start() {
		m_startTicks = SDL_GetPerformanceCounter();
	}

	void Timer::restart() {
		m_startTicks = SDL_GetPerformanceCounter(); //this is faster then using start() method
	}

	Uint64 Timer::split() {
		return ((SDL_GetPerformanceCounter() - m_startTicks) * 1000 / SDL_GetPerformanceFrequency());
	}

	Uint64 Timer::lap() {
		Uint64 oldTicks = m_startTicks;
		m_startTicks = SDL_GetPerformanceCounter();
		return ((m_startTicks - oldTicks) * 1000 / SDL_GetPerformanceFrequency());
	}

	Uint64 Timer::totalTime() {
		return (SDL_GetPerformanceCounter() * 1000 / SDL_GetPerformanceFrequency());
	}
}
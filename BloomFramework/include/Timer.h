#pragma once

#include "export.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Timer {
	public:
		Timer() noexcept;

		static Uint32 totalLifetime() noexcept;

		void start() noexcept;
		void restart() noexcept;
		double split() const noexcept;
		double lap() noexcept;
		double objectLifetime() const noexcept;

	private:
		Uint64	m_startTicks, m_timerTicks;
	};
}
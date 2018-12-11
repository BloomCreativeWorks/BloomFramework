#pragma once

#include "export.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Timer {
	public:
		Timer() noexcept;

		[[nodiscard]] static Uint32 totalLifetime() noexcept;

		void start() noexcept;
		void restart() noexcept;
		[[nodiscard]] double split() const noexcept;
		double lap() noexcept;
		[[nodiscard]] double objectLifetime() const noexcept;

	private:
		Uint64	m_startTicks, m_timerTicks;
	};
}
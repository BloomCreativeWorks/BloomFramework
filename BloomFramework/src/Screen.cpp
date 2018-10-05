#include "Screen.h"

void bloom::Screen::update()
{
	for (auto& sys : m_systems)
		sys.second.update(m_gameInstance->timer.lap());
}

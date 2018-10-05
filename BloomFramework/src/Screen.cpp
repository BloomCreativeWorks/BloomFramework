#include "Screen.h"

void bloom::Screen::update()
{
	for (auto& sys : m_systems)
		sys->update(m_gameInstance->timer.lap());
}

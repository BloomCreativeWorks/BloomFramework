#include "Graphics/AnimationSet.h"
#include "Exception.h"

namespace bloom::graphics {
	AnimationPtr AnimationSet::changeCurrent(const std::string& setName) {
		const auto setIt = m_sets.find(setName);
		if (setIt == m_sets.end())
			throw Exception{ "AnimationSet::changeCurrent", "Set doesn't exist" };

		if (m_current != setIt->second) {
			if (m_current)
				m_current->stop();
			m_current = setIt->second;
		}
		return m_current;
	}
}
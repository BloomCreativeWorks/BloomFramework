#include "Graphics/AnimationSet.h"

namespace bloom::graphics {
	AnimationPtr AnimationSet::changeCurrent(const std::string & setName) {
		auto it = m_sets.find(setName);
		if (it == m_sets.end())
			throw Exception("[AnimationSet::changeAnimation] Set doesn't exist");

		if (m_current != it->second) {
			if (m_current)
				m_current->stop();
			m_current = it->second;
		}
		return m_current;
	}

	inline void AnimationSet::add(const std::string & setName, const Animation & animation) {
		m_sets.try_emplace(setName, std::make_shared<Animation>(animation));
	}

	inline void AnimationSet::add(const std::string & setName, AnimationPtr animationPtr) {
		m_sets.try_emplace(setName, animationPtr);
	}
}
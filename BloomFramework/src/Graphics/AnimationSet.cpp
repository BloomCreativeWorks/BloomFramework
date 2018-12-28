#include "Graphics/AnimationSet.h"

namespace bloom::graphics {
	AnimationPtr AnimationSet::changeCurrent(const std::string & setName) {
		auto it = set.find(setName);
		if (it == set.end())
			throw Exception("[AnimationSet::changeAnimation] Set doesn't exist");

		if (m_current != it->second) {
			if (m_current)
				m_current->stop();
			m_current = it->second;
		}
		return m_current;
	}

	void AnimationSet::add(const std::string & setName, const Animation & animation) {
		set.try_emplace(setName, std::make_shared<Animation>(animation));
	}

	void AnimationSet::add(const std::string & setName, AnimationPtr animationPtr) {
		set.try_emplace(setName, animationPtr);
	}
	
	void AnimationSet::remove(const std::string & setName) {
		set.erase(setName);
	}
	
	void AnimationSet::clear() { set.clear(); }
}
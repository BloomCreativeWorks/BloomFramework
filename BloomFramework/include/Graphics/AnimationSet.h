#pragma once
#include "stdIncludes.h"
#include "Animation.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API AnimationSet {
	public:
		AnimationPtr changeCurrent(const std::string& setName);

		void add(const std::string& setName, const Animation& animation) {
			m_sets.try_emplace(setName, std::make_shared<Animation>(animation));
		}

		void add(const std::string& setName, AnimationPtr animationPtr) {
			m_sets.try_emplace(setName, animationPtr);
		}

		void remove(const std::string& setName) {
			m_sets.erase(setName);
		}

		void clear() {
			m_sets.clear();
		}

		AnimationPtr getCurrent() const {
			return m_current;
		}

	private:
		std::unordered_map<std::string, AnimationPtr> m_sets;
		AnimationPtr m_current{ nullptr };
	};
}
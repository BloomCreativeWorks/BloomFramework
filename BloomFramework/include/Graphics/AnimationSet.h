#pragma once
#include <random>
#include "stdIncludes.h"
#include "Animation.h"
#include "Exception.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API AnimationSet {
	public:
		AnimationPtr changeCurrent(const std::string & setName);

		inline void add(const std::string & setName, const Animation & animation);
		inline void add(const std::string & setName, AnimationPtr animation);

		void remove(const std::string & setName) { m_sets.erase(setName); }

		void clear() { m_sets.clear(); }

		AnimationPtr getCurrent() const { return m_current; }

	private:
		std::unordered_map<std::string, AnimationPtr> m_sets; 
		AnimationPtr m_current = nullptr;
	};
}
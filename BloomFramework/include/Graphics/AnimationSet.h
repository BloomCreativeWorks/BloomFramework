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

		void remove(const std::string & setName) { set.erase(setName); }

		void clear() { set.clear(); }

		std::unordered_map<std::string, AnimationPtr> set; // hm, do we need public set and add/remove/clear funcs?

		AnimationPtr getCurrent() const { return m_current; }

	private:
		AnimationPtr m_current = nullptr;
	};
}
#pragma once
#include <random>
#include "stdIncludes.h"
#include "Animation.h"
#include "Exception.h"

namespace bloom::graphics {
	class BLOOMFRAMEWORK_API AnimationSet {
	public:
		AnimationPtr changeCurrent(const std::string & setName);

		void add(const std::string & setName, const Animation & animation);
		void add(const std::string & setName, AnimationPtr animation);

		void remove(const std::string & setName);

		void clear();

		std::unordered_map<std::string, AnimationPtr> set;

		AnimationPtr getCurrent() const { return m_current; }

	private:
		AnimationPtr m_current = nullptr;
	};
}
#pragma once
#include <unordered_map>
#include "stdIncludes.h"
#include "Music.h"

namespace bloom {
	class BLOOMFRAMEWORK_API MusicStore {
	public:
		TrackPtr load(const std::string & filePath);
		TrackPtr find(const std::string & filePath);
		TrackPtr find(std::nothrow_t, const std::string & filePath) noexcept;
		void unload(const std::string & filePath);
		void unload_all();

	private:
		std::unordered_map<std::string, TrackPtr> m_store;
	};
}
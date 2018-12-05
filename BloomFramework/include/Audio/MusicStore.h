#pragma once

#include <unordered_map>
#include "stdIncludes.h"
#include "MusicTrack.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API MusicStore {
	public:
		TrackPtr load(const std::filesystem::path & filePath);
		TrackPtr find(const std::filesystem::path & filePath);
		TrackPtr find(std::nothrow_t, const std::filesystem::path & filePath) noexcept;
		void unload(const std::filesystem::path & filePath);
		void unloadAll();

	private:
		std::unordered_map<std::string, TrackPtr> m_store;
	};
}
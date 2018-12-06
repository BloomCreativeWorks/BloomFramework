#pragma once

#include "stdIncludes.h"

#include <unordered_map>
#include "MusicTrack.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API MusicStore {
	public:
		TrackPtr load(const std::filesystem::path & filePath);
		TrackPtr at(const std::filesystem::path & filePath) const;
		TrackPtr find(const std::filesystem::path & filePath) const noexcept;
		void unload(const std::filesystem::path & filePath);
		void unloadAll();

		TrackPtr operator[](const std::filesystem::path & key) const noexcept;

	private:
		std::unordered_map<std::string, TrackPtr> m_store;
	};
}
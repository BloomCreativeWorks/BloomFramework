#pragma once

#include "stdIncludes.h"

#include <unordered_map>
#include "HashPath.h"
#include "MusicTrack.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API MusicStore {
	public:
		static MusicStore& store();

		TrackPtr load(const std::filesystem::path& filePath);
		TrackPtr at(const std::filesystem::path& filePath) const;
		TrackPtr find(const std::filesystem::path& filePath) const noexcept;
		void unload(const std::filesystem::path& filePath);
		void unloadAll() noexcept;

		TrackPtr operator[](const std::filesystem::path& key) const noexcept;

	private:
		MusicStore() = default;
		MusicStore(const MusicStore&) = delete;
		MusicStore(MusicStore&&) = delete;
		MusicStore& operator=(const MusicStore&) = delete;
		MusicStore& operator=(MusicStore&&) = delete;
		~MusicStore() = default;

		std::unordered_map<std::filesystem::path, TrackPtr, HashPath> m_store;
	};
}
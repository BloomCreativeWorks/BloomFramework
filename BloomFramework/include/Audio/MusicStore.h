#pragma once

#include "stdIncludes.h"

#include "BasicStore.h"
#include "MusicTrack.h"

namespace bloom::audio {
	class MusicStore : public BasicStore<TrackPtr> {
	public:
		using Type = MusicStore;
		using ValueType = TrackPtr;

		TrackPtr load(const std::filesystem::path& filePath) override {
			return m_store.try_emplace(filePath, std::make_shared<MusicTrack>(filePath)).first->second;
		}
	};
}
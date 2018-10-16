#pragma once
#include <unordered_map>
#include "stdIncludes.h"
#include "Music.h"

namespace bloom::audio {
	class BLOOMFRAMEWORK_API MusicStore {
	public:
		MusicStore();
		~MusicStore();

		TrackPtr load(const std::string & filePath);
		TrackPtr find(const std::string & filePath);
		TrackPtr find(std::nothrow_t, const std::string & filePath) noexcept;
		void unload(const std::string & filePath);
		void unloadAll();

	private:
		std::unordered_map<std::string, TrackPtr> m_store;

		inline static size_t obj_qnt = 0;
	};
}
#pragma once
#include <unordered_map>
#include "stdIncludes.h"
#include "SoundFX.h"

namespace bloom {
	class BLOOMFRAMEWORK_API SoundFXStore {
	public:
		SoundFXStore() : m_def_channels4sound(3) {}
		SoundFXStore(int channels4sound) : m_def_channels4sound(channels4sound) {}

		SoundFXPtr load(const std::string & filePath);
		SoundFXPtr find(const std::string & filePath);
		SoundFXPtr find(std::nothrow_t, const std::string & filePath) noexcept;
		void unload(const std::string & filePath);

		void _extraChannels(int extraChannels);

	private:
		std::unordered_map<std::string, SoundFXPtr> m_store;
		inline static int m_channels = 0;
		inline static int m_extraChannels = 0;
		const int m_def_channels4sound;
	};
}
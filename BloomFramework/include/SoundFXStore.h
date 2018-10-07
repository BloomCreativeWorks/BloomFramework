#pragma once
#include <unordered_map>
#include "stdIncludes.h"
#include "SoundFX.h"

namespace bloom {
	class BLOOMFRAMEWORK_API SoundFXStore {
	public:
		SoundFXPtr load(const std::string & filePath);
		SoundFXPtr find(const std::string & filePath);
		SoundFXPtr find(std::nothrow_t, const std::string & filePath) noexcept;
		void unload(const std::string & filePath);

		static void disableAutoChannels(bool state);
		static void manageExtraChannels(int qnt);

	private:
		std::unordered_map<std::string, SoundFXPtr> m_store;
		inline static unsigned m_autochannels = true;
		inline static int m_extraChannels = 500;
	};
}
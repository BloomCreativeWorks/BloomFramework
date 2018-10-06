#pragma once
#include <unordered_map>
#include "stdIncludes.h"
#include "SoundFX.h"

namespace bloom {
	//class SoundFX;

	class BLOOMFRAMEWORK_API SoundFXStore {
	public:
		SoundFXPtr load(const std::string & filePath);
		SoundFXPtr find(const std::string & filePath);
		SoundFXPtr find(std::nothrow_t, const std::string & filePath) noexcept;
		void unload(const std::string & filePath);

	private:
		std::unordered_map<std::string, SoundFXPtr> m_store;

		//static void _channel_stop_func(int);
		//static void _add_channel();
		////inline static int _channels = 1;
	};
}
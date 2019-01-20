#pragma once

#include "stdIncludes.h"

#include "BasicStore.h"
#include "SoundChunk.h"

namespace bloom::audio {
	class SoundStore : public BasicStore<ChunkPtr> {
	public:
		using Type = SoundStore;
		using ValueType = ChunkPtr;

		ChunkPtr load(const std::filesystem::path& filePath) override {
			return m_store.try_emplace(filePath, std::make_shared<SoundChunk>(filePath)).first->second;
		}
	};

	//class BLOOMFRAMEWORK_API SoundStore {
	//public:
	//	static SoundStore& store();

	//	ChunkPtr load(const std::filesystem::path& filePath);
	//	ChunkPtr at(const std::filesystem::path& filePath) const;
	//	ChunkPtr find(const std::filesystem::path& filePath) const noexcept;
	//	void unload(const std::filesystem::path& filePath);
	//	void unloadAll() noexcept;

	//	ChunkPtr operator[](const std::filesystem::path& key) const noexcept;

	//private:
	//	SoundStore() = default;
	//	SoundStore(const SoundStore&) = delete;
	//	SoundStore(SoundStore&&) = delete;
	//	SoundStore& operator=(const SoundStore&) = delete;
	//	SoundStore& operator=(SoundStore&&) = delete;
	//	~SoundStore() = default;

	//	std::unordered_map<std::filesystem::path, ChunkPtr, HashPath> m_store;
	//};
}
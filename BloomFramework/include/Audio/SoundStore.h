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
}
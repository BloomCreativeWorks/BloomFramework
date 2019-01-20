#pragma once

#include <unordered_map>
#include <filesystem>
#include "HashPath.h"

namespace bloom {
	template<typename VType>
	class BasicStore {
	public:
		using Type = BasicStore<VType>;
		using ValueType = VType;

		virtual VType load(const std::filesystem::path& filePath) = 0;
		VType at(const std::filesystem::path& filePath) const;
		VType find(const std::filesystem::path& filePath) const noexcept;
		void unload(const std::filesystem::path& filePath);
		void unloadAll() noexcept;

		VType operator[](const std::filesystem::path& key) const noexcept;

	protected:
		std::unordered_map<std::filesystem::path, VType, HashPath> m_store;
	};

	template<typename VType>
	VType BasicStore<VType>::at(const std::filesystem::path& filePath) const {
		auto trackIt{ m_store.find(filePath) };
		if (trackIt != m_store.end())
			return trackIt->second;
		else
			throw Exception("[Store] Element \"" + filePath.u8string() + "\" not loaded");
	}

	template<typename VType>
	VType BasicStore<VType>::find(const std::filesystem::path& filePath) const noexcept {
		auto trackIt{ m_store.find(filePath) };
		if (trackIt != m_store.end())
			return trackIt->second;
		else
			return nullptr;
	}

	template<typename VType>
	void BasicStore<VType>::unload(const std::filesystem::path& filePath) {
		m_store.erase(filePath);
	}

	template<typename VType>
	void BasicStore<VType>::unloadAll() noexcept {
		m_store.clear();
	}

	template<typename VType>
	VType BasicStore<VType>::operator[](const std::filesystem::path& key) const noexcept {
		return find(key);
	}
}
#include "Graphics/TextureStore.h"
#include "Exception.h"
#include "Game.h"

namespace bloom::graphics {
	TextureStore::TextureStore(SDL_Renderer*& renderer) : m_renderer(renderer) {}

	TextureStore::TextureStore(Game& object) : m_renderer(object.m_renderer) {}

	TexturePtr TextureStore::load(const std::filesystem::path& filePath, std::optional<SDL_Color> colorKey) {
		auto res = m_store.try_emplace(filePath.u8string(), std::make_shared<Texture>(m_renderer, filePath, colorKey));
		return res.first->second;
	}

	TexturePtr TextureStore::at(const std::filesystem::path& filePath) const {
		if (auto textureIt = m_store.find(filePath.u8string()); textureIt != m_store.end())
			return textureIt->second;
		else
			throw Exception("[Texture Store::at] Can't get texture \"" + filePath.u8string() + "\".\nIs it loaded?");
	}

	TexturePtr TextureStore::find(const std::filesystem::path& filePath) const noexcept {
		if (auto textureIt = m_store.find(filePath.u8string()); textureIt != m_store.end())
			return textureIt->second;
		else
			return nullptr;
	}

	void TextureStore::unload(const std::filesystem::path& filePath) {
		m_store.erase(filePath.u8string());
	}

	void TextureStore::unloadAll() noexcept {
		m_store.clear();
	}

	TexturePtr TextureStore::operator[](const std::filesystem::path& key) const noexcept {
		return find(key);
	}
}

#include "Graphics/TextureStore.h"
#include "Exception.h"
#include "Game.h"

namespace bloom::graphics {
	TextureStore::TextureStore(SDL_Renderer *& renderer) : m_renderer(renderer) {}

	TextureStore::TextureStore(Game & object) : m_renderer(object.m_renderer) {}

	TexturePtr TextureStore::load(const std::string & filePath, std::optional<SDL_Color> colorKey) {
		// Check if texture of the same path is loaded. If so, return shared_ptr of texture.
		auto textureIt = m_store.find(filePath);
		if (textureIt != m_store.end())
			return textureIt->second;
    
		TexturePtr ptr = std::make_shared<Texture>(m_renderer, filePath, colorKey);
		m_store.emplace(filePath, ptr);
		return ptr;
	}

	TexturePtr TextureStore::find(const std::string & filePath) {
		auto texIterator = m_store.find(filePath);
		if (texIterator != m_store.end())
			return texIterator->second;
		else {
			throw Exception("[Texture Store] Can't get texture \"" + filePath + "\".\nIs it loaded?");
		}
	}

	TexturePtr TextureStore::find(std::nothrow_t, const std::string & filePath) {
		auto texIterator = m_store.find(filePath);
		if (texIterator != m_store.end())
			return texIterator->second;
		else {
			return nullptr;
		}
	}

	void TextureStore::unload(const std::string & filePath) {
		auto texIterator = m_store.find(filePath);
		if (texIterator != m_store.end())
			m_store.erase(texIterator); // We can't dispose the actual Texture since other's may still be using it.
	}
}

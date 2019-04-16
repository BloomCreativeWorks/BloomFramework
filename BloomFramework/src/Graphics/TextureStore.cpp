#include "Graphics/TextureStore.h"
#include "Exception.h"
#include "Game.h"

namespace bloom::graphics {
	TextureStore::TextureStore(SDL_Renderer*& renderer) : c_renderer(renderer) {}

	TextureStore::TextureStore(Game& object) : c_renderer(object._getRenderer()) {}

	TexturePtr TextureStore::load(const std::filesystem::path& filePath, std::optional<SDL_Color> colorKey) {
		if (!std::filesystem::exists(filePath))
			throw Exception{ "TextureStore::load", "File \"" + filePath.u8string() + "\" not exists" };

		// Check if texture of the same path is loaded. If so, return shared_ptr of texture.
		if (const auto textureIt = m_store.find(filePath.u8string()); textureIt != m_store.end())
			return textureIt->second;

		TexturePtr ptr = std::make_shared<Texture>(c_renderer, filePath, colorKey);
		m_store.emplace(filePath.u8string(), ptr);
		return ptr;
	}
}
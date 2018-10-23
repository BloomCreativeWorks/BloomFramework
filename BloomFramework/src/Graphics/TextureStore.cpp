#include "Graphics/TextureStore.h"
#include "Exception.h"
#include "Game.h"

namespace bloom::graphics {
	TextureStore::TextureStore(SDL_Renderer *& renderer) : m_renderer(renderer) {}

	TextureStore::TextureStore(Game & object) : m_renderer(object.m_renderer) {}

	TexturePtr TextureStore::load(const std::filesystem::path & filePath, std::optional<SDL_Color> colorKey) {
		if (!std::filesystem::exists(filePath)) {
			throw Exception("[TextureStore::load] texture file not exists");
		}

		// Check if texture of the same path is loaded. If so, return shared_ptr of texture.
		auto textureIt = m_store.find(filePath.u8string());
		if (textureIt != m_store.end())
			return textureIt->second;

		//Load image at specified path
		SDL_Surface * loadedSurface = IMG_Load(filePath.u8string().c_str());
		if (loadedSurface == nullptr)
		{
			throw Exception("[SDL_IMG] " + std::string(SDL_GetError()));
		}
		else
		{
			if (colorKey != std::nullopt) {
				SDL_SetColorKey(loadedSurface, true, SDL_MapRGB(loadedSurface->format, colorKey->r, colorKey->g, colorKey->b));
			}
			//Create texture from surface pixels
			SDL_Texture * texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
			if (texture == nullptr)
			{
				throw Exception("[SDL_Texture] " + std::string(SDL_GetError()));
			}
			else {
				TexturePtr ptr = std::make_shared<Texture>(texture, m_renderer);
				m_store.emplace(filePath.u8string(), ptr);
				SDL_FreeSurface(loadedSurface);
				return ptr;
			}
		}
	}

	TexturePtr TextureStore::find(const std::filesystem::path & filePath) {
		auto texIterator = m_store.find(filePath.u8string());
		if (texIterator != m_store.end())
			return texIterator->second;
		else {
			throw Exception("[Texture Store] Can't get texture \"" + filePath.string() +"\".\nIs it loaded?");
		}
	}

	TexturePtr TextureStore::find(std::nothrow_t, const std::filesystem::path & filePath) {
		auto texIterator = m_store.find(filePath.u8string());
		if (texIterator != m_store.end())
			return texIterator->second;
		else {
			return nullptr;
		}
	}

	void TextureStore::unload(const std::filesystem::path & filePath) {
		auto texIterator = m_store.find(filePath.u8string());
		if (texIterator != m_store.end())
			m_store.erase(texIterator); // We can't dispose the actual Texture since other's may still be using it.
	}
}

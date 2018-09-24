#include "Exception.h"
#include "Game.h"

namespace bloom {
	TextureStore::TextureStore(SDL_Renderer *& renderer) : m_renderer(renderer) {}

	TextureStore::TextureStore(Game & object) : m_renderer(object.m_renderer) {}

	TexturePtr TextureStore::load(const std::string & filePath, std::optional<SDL_Color> colorKey) {
		// Check if texture of the same path is loaded. If so, return shared_ptr of texture.
		auto texture = findTexture(filePath);
		if (texture != nullptr)
			return texture;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
		if (loadedSurface == NULL)
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
				m_store.emplace(filePath, ptr);
				SDL_FreeSurface(loadedSurface);
				return ptr;
			}
		}
	}

	TexturePtr TextureStore::getTexture(const std::string & filePath) {
		auto texIterator = m_store.find(filePath);
		if (texIterator != m_store.end())
			return texIterator->second;
		else {
			throw Exception("[Texture Store] Can't get texture \"" + filePath + "\".\nIs it loaded?");
		}
	}

	void TextureStore::unload(const std::string & filePath) {
		auto texIterator = m_store.find(filePath);
		if (texIterator != m_store.end())
			m_store.erase(texIterator);
		// We can't dispose the actual Texture since other's may still be using it.
	}

	TexturePtr TextureStore::findTexture(const std::string & filePath) {
		try {
			auto temp = getTexture(filePath);
			return temp;
		}
		catch (...) {
			return nullptr;
		}
	}
}

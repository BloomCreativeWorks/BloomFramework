#include "..\include\TextureStore.h"

namespace bloom {
	TextureStore::TextureStore(SDL_Renderer ** renderer) : m_renderer(renderer)
	{
	}
	TexturePtr TextureStore::load(const std::string & filePath, std::optional<SDL_Color> colorKey)
	{
		// Check if texture of the same path is loaded. If so, return shared_ptr of texture.
		auto texture =  getTexture(filePath);
		if (texture != nullptr)
			return texture;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());
		if (loadedSurface == NULL)
		{
			std::cerr << "[SDL_IMG] " << IMG_GetError() << std::endl;
		}
		else
		{	
			if (colorKey == std::nullopt) {
				SDL_SetColorKey(loadedSurface, true, SDL_MapRGB(loadedSurface->format, colorKey->r, colorKey->g, colorKey->b));
			}
			//Create texture from surface pixels
			SDL_Texture * texture = SDL_CreateTextureFromSurface(*m_renderer, loadedSurface);
			if (texture == nullptr)
			{
				std::cerr << "[SDL_Texture] " << SDL_GetError() << std::endl;
			}
			else {
				TexturePtr ptr = std::make_shared<Texture>(texture, m_renderer);
				m_store.emplace(filePath, ptr);
				SDL_FreeSurface(loadedSurface);
				return ptr;
			}
		}
		
	}
	TexturePtr TextureStore::getTexture(const std::string & filePath)
	{
		auto texIterator = m_store.find(filePath);
		if (texIterator != m_store.end())
			return texIterator->second;
		else {
			// throw some sort of exception here.
			return nullptr;
		}
	}
	void TextureStore::destroyTexture(const std::string & filePath)
	{
		auto texIterator = m_store.find(filePath);
		if (texIterator != m_store.end())
			m_store.erase(texIterator);
			// We can't dispose the actual Texture since other's may still be using it.
	}
}

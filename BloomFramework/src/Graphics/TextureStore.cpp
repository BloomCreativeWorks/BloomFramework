#include "Graphics/TextureStore.h"
#include "Exception.h"
#include "Game.h"

namespace bloom::graphics {
	TextureStore::TextureStore(SDL_Renderer *& renderer) : renderer_(renderer) {}

	TextureStore::TextureStore(Game & object) : renderer_(object.renderer_) {}

	TexturePtr TextureStore::Load(const std::string & file_path, std::optional<SDL_Color> color_key) {
		// Check if texture of the same path is loaded. If so, return shared_ptr of texture.
		auto texture_it = store_.find(file_path);
		if (texture_it != store_.end())
			return texture_it->second;

		//Load image at specified path
		SDL_Surface* loaded_surface = IMG_Load(file_path.c_str());
		if (loaded_surface == nullptr)
		{
			throw Exception("[SDL_IMG] " + std::string(SDL_GetError()));
		}
		else
		{
			if (color_key != std::nullopt) {
				SDL_SetColorKey(loaded_surface, true, SDL_MapRGB(loaded_surface->format, color_key->r, color_key->g, color_key->b));
			}
			//Create texture from surface pixels
			SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer_, loaded_surface);
			if (texture == nullptr)
			{
				throw Exception("[SDL_Texture] " + std::string(SDL_GetError()));
			}
			else {
				TexturePtr ptr = std::make_shared<Texture>(texture, renderer_);
				store_.emplace(file_path, ptr);
				SDL_FreeSurface(loaded_surface);
				return ptr;
			}
		}
	}

	TexturePtr TextureStore::Find(const std::string & file_path) {
		auto texture_it = store_.find(file_path);
		if (texture_it != store_.end())
			return texture_it->second;
		else {
			throw Exception("[Texture Store] Can't get texture \"" + file_path + "\".\nIs it loaded?");
		}
	}

	TexturePtr TextureStore::Find(std::nothrow_t, const std::string & file_path) {
		auto texture_it = store_.find(file_path);
		if (texture_it != store_.end())
			return texture_it->second;
		else {
			return nullptr;
		}
	}

	void TextureStore::Unload(const std::string & file_path) {
		auto texture_it = store_.find(file_path);
		if (texture_it != store_.end())
			store_.erase(texture_it); // We can't dispose the actual Texture since other's may still be using it.
	}
}

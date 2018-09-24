#pragma once
#pragma warning(disable:4251) //Ignore warnings about templates in dll

#include <unordered_map>
#include <optional>
#include "Texture.h"

namespace bloom {
	class Game;

	typedef std::shared_ptr<Texture> TexturePtr;

	//template class BLOOMFRAMEWORK_API std::unordered_map<std::string, TexturePtr>;

	class BLOOMFRAMEWORK_API TextureStore {
	public:
		TextureStore(SDL_Renderer *& renderer);
		TextureStore(Game & renderer);

		TexturePtr load(const std::string & filePath, std::optional<SDL_Color> colorKey = std::nullopt);
		TexturePtr getTexture(const std::string & filePath);
		void unload(const std::string & filePath);
 

	private:
		TexturePtr findTexture(const std::string & filePath);

		SDL_Renderer *& m_renderer;
		std::unordered_map<std::string, TexturePtr> m_store;
	};
}
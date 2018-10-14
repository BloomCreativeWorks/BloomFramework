#pragma once
#pragma warning(disable:4251) //Ignore warnings about templates in dll

#include <unordered_map>
#include <optional>
#include "Texture.h"

namespace bloom {
	class Game;
	namespace graphics {
		//template class BLOOMFRAMEWORK_API std::unordered_map<std::string, TexturePtr>;

		class BLOOMFRAMEWORK_API TextureStore {
		public:
			TextureStore(SDL_Renderer *& renderer);
			TextureStore(Game & renderer);

			TexturePtr load(const std::string & filePath, std::optional<SDL_Color> colorKey = std::nullopt);
			TexturePtr find(const std::string & filePath);
			TexturePtr find(std::nothrow_t, const std::string & filePath);
			void unload(const std::string & filePath);

		private:
			SDL_Renderer *&	m_renderer;
			std::unordered_map<std::string, TexturePtr>	m_store;
		};
	}
}
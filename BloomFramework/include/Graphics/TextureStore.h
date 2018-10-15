#pragma once

#include "stdIncludes.h"
#include <unordered_map>
#include <optional>
#include "Texture.h"

namespace bloom {
	class Game;

	namespace graphics {
		class BLOOMFRAMEWORK_API TextureStore {
		public:
			TextureStore(SDL_Renderer *& renderer);
			TextureStore(Game & renderer);

			TexturePtr load(const std::string & file_path, std::optional<SDL_Color> color_key = std::nullopt);
			TexturePtr find(const std::string & file_path);
			TexturePtr find(std::nothrow_t, const std::string & file_path);
			void unload(const std::string & file_path);

		private:
			SDL_Renderer *&	renderer_;
			std::unordered_map<std::string, TexturePtr>	store_;
		};
	}
}
#ifndef BLOOM_GRAPHICS_TEXTURESTORE_H_
#define BLOOM_GRAPHICS_TEXTURESTORE_H_

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

			TexturePtr Load(const std::string & file_path, std::optional<SDL_Color> color_key = std::nullopt);
			TexturePtr Find(const std::string & file_path);
			TexturePtr Find(std::nothrow_t, const std::string & file_path);
			void Unload(const std::string & file_path);

		private:
			SDL_Renderer *&	renderer_;
			std::unordered_map<std::string, TexturePtr>	store_;
		};
} // namespace bloom::graphics
} // namespace bloom

#endif // !BLOOM_GRAPHICS_TEXTURESTORE_H_
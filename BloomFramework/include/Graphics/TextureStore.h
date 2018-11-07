#pragma once

#include <unordered_map>
#include <optional>
#include "stdIncludes.h"
#include "Texture.h"

namespace bloom {
	class BLOOMFRAMEWORK_API Game;

	namespace graphics {
		class BLOOMFRAMEWORK_API TextureStore {
		public:
			TextureStore(SDL_Renderer *& renderer);
			TextureStore(Game & renderer);

			TexturePtr load(const std::filesystem::path & filePath, std::optional<SDL_Color> colorKey = std::nullopt);
			TexturePtr find(const std::filesystem::path & filePath);
			TexturePtr find(std::nothrow_t, const std::filesystem::path & filePath) noexcept;
			void unload(const std::filesystem::path & filePath);

		private:
			SDL_Renderer *&	m_renderer;
			std::unordered_map<std::string, TexturePtr>	m_store;
		};
	}
}
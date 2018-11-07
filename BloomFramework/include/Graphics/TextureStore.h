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
			TexturePtr at(const std::filesystem::path & filePath) const;
			TexturePtr find(const std::filesystem::path & filePath) const noexcept;
			void unload(const std::filesystem::path & filePath);

			TexturePtr operator[](const std::filesystem::path & key) const noexcept;

		private:
			SDL_Renderer *&	m_renderer;
			std::unordered_map<std::string, TexturePtr>	m_store;
		};
	}
}
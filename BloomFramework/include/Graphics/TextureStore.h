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
			TextureStore(SDL_Renderer*& renderer);
			TextureStore(Game& object);

			TexturePtr load(const std::filesystem::path& filePath, std::optional<SDL_Color> colorKey = std::nullopt);

			TexturePtr find(const std::filesystem::path& filePath) const noexcept {
				const auto textureIt = m_store.find(filePath.u8string());
				return textureIt != m_store.end() ? textureIt->second : TexturePtr{};
			}

			void unload(const std::filesystem::path& filePath) {
				if (const auto textureIt = m_store.find(filePath.u8string()); textureIt != m_store.end())
					m_store.erase(textureIt); // We can't dispose the actual Texture since others may still be using it.
			}

			TexturePtr operator[](const std::filesystem::path& key) const noexcept {
				return find(key);
			}

		private:
			SDL_Renderer* const& c_renderer;
			std::unordered_map<std::string, TexturePtr>	m_store;
		};
	}
}
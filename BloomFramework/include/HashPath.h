#pragma once
#include <filesystem>

namespace bloom {
	struct HashPath {
		// hash functor for std::filesystem::path
		using argument_type = std::filesystem::path;
		using result_type = size_t;
		[[nodiscard]] size_t operator()(const std::filesystem::path& key) const noexcept {
			return (std::filesystem::hash_value(key));
		}
	};
}
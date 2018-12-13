#pragma once
#pragma warning(disable:4251) //Ignore warnings about templates in dll

#include <filesystem>
#include <optional>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#undef main // undef it because SDL_main function assumed not to throw exceptions

#include "entt/entt.hpp"

#include "export.h"

template<>
struct std::hash<std::filesystem::path> {
	// hash functor for std::filesystem::path
	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef std::filesystem::path argument_type;
	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef size_t result_type;
	[[nodiscard]] size_t operator()(const std::filesystem::path& _Keyval) const noexcept {
		return (std::filesystem::hash_value(_Keyval));
	}
};
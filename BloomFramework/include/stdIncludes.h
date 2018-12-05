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
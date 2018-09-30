#pragma once

#ifdef BLOOMFRAMEWORK_EXPORT
#define BLOOMFRAMEWORK_API __declspec(dllexport) 
#else 
#define BLOOMFRAMEWORK_API __declspec(dllimport) 
#endif


#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#undef main

#include "entt/entt.hpp"

#include <memory>
#include <string>
#include <iostream>

typedef double DeltaTime; // Remove this before merging.
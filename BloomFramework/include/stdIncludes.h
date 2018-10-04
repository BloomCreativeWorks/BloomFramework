#pragma once
#pragma warning(disable:4251) //Ignore warnings about templates in dll

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
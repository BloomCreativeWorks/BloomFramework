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

#include <memory>
#include <string>
#include <iostream>
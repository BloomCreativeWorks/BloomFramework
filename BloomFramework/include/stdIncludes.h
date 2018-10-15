#ifndef BLOOM_STDINCLUDES_H_
#define BLOOM_STDINCLUDES_H_

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

#endif // !BLOOM_STDINCLUDES_H_
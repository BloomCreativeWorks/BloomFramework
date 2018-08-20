#pragma once
#ifdef BLOOMFRAMEWORK_EXPORT
#define BLOOMFRAMEWORK_API __declspec(dllexport)
#else
#define BLOOMFRAMEWORK_API __declspec(dllimport)
#endif

#include "BloomFramework/stdIncludes.h"
#include "BloomFramework/GraphicsWindow.h"
#include "BloomFramework/EventHandler.h"
#include "BloomFramework/TextureStore.h"
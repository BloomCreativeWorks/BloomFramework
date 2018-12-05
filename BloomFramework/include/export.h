#pragma once

#ifdef BLOOMFRAMEWORK_EXPORT
#define BLOOMFRAMEWORK_API __declspec(dllexport)
#else 
#define BLOOMFRAMEWORK_API __declspec(dllimport)
#endif
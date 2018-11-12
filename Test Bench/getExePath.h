#pragma once

#include <Windows.h>
#include <string>

std::string getExePathA(uint32_t pathLength = MAX_PATH);
std::wstring getExePathW(uint32_t pathLength = MAX_PATH);

#ifdef UNICODE
#define getExePath  getExePathW
#else
#define getExePath  getExePathA
#endif // !UNICODE
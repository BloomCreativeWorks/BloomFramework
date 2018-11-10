#include "getExePath.h"

std::string getExePathA(uint32_t pathLength) {
	std::string path(pathLength, '\0');
	GetModuleFileNameA(nullptr, path.data(), pathLength);
	path.resize(path.rfind('\\'));
	path.shrink_to_fit();
	return path;
}

std::wstring getExePathW(uint32_t pathLength) {
	std::wstring path(pathLength, L'\0');
	GetModuleFileNameW(nullptr, path.data(), pathLength);
	path.resize(path.rfind('\\'));
	path.shrink_to_fit();
	return path;
}
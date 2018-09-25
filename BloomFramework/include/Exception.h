#pragma once
#include <exception>
#include <string>

namespace bloom {
	class Exception : public std::exception {
	public:
		Exception(std::string && _Message) noexcept;
		Exception(std::string && _Message, int _ErrNo) noexcept;
		Exception(char const * const _Message) noexcept;
		Exception(char const * const _Message, int _ErrNo) noexcept;
	};
}
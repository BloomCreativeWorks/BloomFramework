// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Exception.h"

namespace bloom {
	Exception::Exception(std::string && _Message) noexcept :
		exception(_Message.c_str()) {}
	Exception::Exception(std::string && _Message, int _ErrNo) noexcept :
		exception(_Message.c_str(), _ErrNo) {}
	Exception::Exception(char const * const _Message) noexcept :
		exception(_Message) {}
	Exception::Exception(char const * const _Message, int _ErrNo) noexcept :
		exception(_Message, _ErrNo) {}
}
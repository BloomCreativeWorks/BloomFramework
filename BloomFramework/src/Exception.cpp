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
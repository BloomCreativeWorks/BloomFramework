#include "Exception.h"

namespace bloom {
	Exception::Exception(std::string && message) noexcept :
		exception(message.c_str()) {}

	Exception::Exception(std::string && message, int err_no) noexcept :
		exception(message.c_str(), err_no) {}

	Exception::Exception(char const * const message) noexcept :
		exception(message) {}

	Exception::Exception(char const * const message, int err_no) noexcept :
		exception(message, err_no) {}
}
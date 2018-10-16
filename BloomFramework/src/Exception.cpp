#include "Exception.h"

namespace bloom {
	Exception::Exception(std::string && message) noexcept :
		exception(message.c_str()) {}

	Exception::Exception(std::string && message, int errr_no) noexcept :
		exception(message.c_str(), errr_no) {}

	Exception::Exception(char const * const message) noexcept :
		exception(message) {}

	Exception::Exception(char const * const message, int errr_no) noexcept :
		exception(message, errr_no) {}
}
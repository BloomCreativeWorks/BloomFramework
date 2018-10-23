#pragma once

#include <exception>
#include <string>
#include "stdIncludes.h"

namespace bloom {
	class BLOOMFRAMEWORK_API std::exception;

	class BLOOMFRAMEWORK_API Exception : public std::exception {
	public:
		Exception(std::string && message) noexcept;
		Exception(std::string && message, int err_no) noexcept;
		Exception(char const * const message) noexcept;
		Exception(char const * const message, int err_no) noexcept;
	};
}
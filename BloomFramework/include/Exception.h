#pragma once

#include <exception>
#include <string>
#include "export.h"

namespace bloom {
	class BLOOMFRAMEWORK_API std::exception;

	class BLOOMFRAMEWORK_API Exception : public std::exception {
	public:
		Exception(std::string&& message) noexcept;
		Exception(std::string&& message, int err_no) noexcept;
		Exception(const char* const message) noexcept;
		Exception(const char* const message, int err_no) noexcept;
	};
}
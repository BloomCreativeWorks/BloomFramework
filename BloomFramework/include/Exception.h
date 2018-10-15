#ifndef BLOOM_EXCEPTION_H_
#define BLOOM_EXCEPTION_H_

#include <exception>
#include <string>

namespace bloom {
	class Exception : public std::exception {
	public:
		Exception(std::string && message) noexcept;
		Exception(std::string && message, int err_no) noexcept;
		Exception(char const * const message) noexcept;
		Exception(char const * const message, int err_no) noexcept;
	};
} // namespace bloom

#endif // !BLOOM_EXCEPTION_H_
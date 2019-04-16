#pragma once

#include <exception>
#include <string_view>

namespace bloom {
	class Exception : public std::exception {
	public:
		Exception(std::string_view message) noexcept :
			exception(message.data()), m_where(nullptr) {}

		Exception(const char* const where, std::string_view message) noexcept :
			exception(message.data()), m_where(where) {}

		Exception(const Exception&) = default;
		Exception& operator=(const Exception&) = default;
		~Exception() = default;

		virtual const char* where() const {
			return m_where ? m_where : "";
		}

	private:
		const char* m_where;
	};

	inline std::ostream& operator<<(std::ostream& os, const bloom::Exception& e) {
		return os << "Exception \"" << e.what() << "\" was thrown by [" << e.where() << ']' << std::endl;
	}
}
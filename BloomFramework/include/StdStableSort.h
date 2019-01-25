#pragma once

#include <functional>
#include <algorithm>
#include <utility>

namespace bloom::misc {
	// Keep docs from entity ;)

	/**
	 * @brief Function object to wrap `std::stable_sort` in a class type.
	 *
	 * Unfortunately, `std::stable_sort` cannot be passed as template argument to a class
	 * template or a function template.<br/>
	 * This class fills the gap by wrapping some flavors of `std::stable_sort` in a
	 * function object.
	 */
	struct StdStableSort final {
		/**
		 * @brief Sorts the elements in a range.
		 *
		 * Sorts the elements in a range using the given binary comparison function.
		 * The order of equivalent elements is guaranteed to be preserved.
		 *
		 * @tparam It Type of random access iterator.
		 * @tparam Compare Type of comparison function object.
		 * @tparam Args Types of arguments to forward to the sort function.
		 * @param first An iterator to the first element of the range to sort.
		 * @param last An iterator past the last element of the range to sort.
		 * @param compare A valid comparison function object.
		 * @param args Arguments to forward to the sort function, if any.
		 */
		template<typename It, typename Compare = std::less<>, typename... Args>
		void operator()(It first, It last, Compare compare = Compare{}, Args &&... args) const {
			std::stable_sort(std::forward<Args>(args)..., std::move(first), std::move(last), std::move(compare));
		}
	};
}
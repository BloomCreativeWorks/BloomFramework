#pragma once
#include <string>
#include "entt/entt.hpp"

namespace bloom::components {
	template<uint64_t Value>
	using Label = entt::label<Value>;

}

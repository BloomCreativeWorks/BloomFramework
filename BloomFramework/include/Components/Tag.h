#pragma once
#include <string>
#include "entt/entt.hpp"

namespace bloom::components {
	template<entt::HashedString::hash_type Value>
	using Label = entt::label<Value>;

}

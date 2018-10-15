#ifndef BLOOM_COMPONENTS_SIZE_H_
#define BLOOM_COMPONENTS_SIZE_H

namespace bloom::components {
	struct Size {
		Size(int w = 1, int h = 1) : w(w), h(h) {}

		int w, h;
	};
} // namespace bloom::components

#endif // !BLOOM_COMPONENTS_SIZE_H_
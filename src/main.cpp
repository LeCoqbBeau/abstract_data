

#include <memory>

#include "utils.h"

int main() {
	std::allocator<str> allocator;
	str *gay = allocator.allocate(10);

	for (int i = 0; i < 10; ++i) {
		allocator.construct(&gay[i], "");
	}

	for (int i = 0; i < 10; ++i) {
		gay[i] = (TOSTR(i + 1));
	}

	for (int i = 0; i < 10; ++i) {
		SHOWL(gay[i]);
	}

	// allocator.destroy(gay);
	allocator.deallocate(gay, 10);
	return 0;
}

#include <iostream>
#include "common.h"

int main() {
	Cell test('H');

	std::cout << test.get_char() << "\n";
	std::cout << test.is_visited() << "\n";

	return 0;
}

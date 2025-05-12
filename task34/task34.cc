#include <iostream>
#include "common.h"

int main() {
	Cell test('H');

	std::cout << test.get_char() << "\n";
	std::cout << test.is_visited() << "\n";

	Grid test_grid;

	test_grid.display_grid();

	return 0;
}

#include <iostream>
#include <string>
#include "common.h"

int main() {
	Cell test('H');

	std::cout << test.get_char() << "\n";
	std::cout << test.is_visited() << "\n";

	Grid test_grid(10);
	std::string filename = "grid.txt";
	if(test_grid.load_from_file(filename)) {
		test_grid.display_grid();
	}
	else {
		std::cerr << "Виникла помилка при відкритті grid.txt\n";
		return 1;
	}

	return 0;
}

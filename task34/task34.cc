#include <iostream>
#include <string>
#include <vector>

#include "common.h"

int main() {
	Cell test('H');

	std::cout << test.get_char() << "\n";
	std::cout << test.is_visited() << "\n";

	Grid test_grid(10);
  TextUI test_ui;

	std::string filename = test_ui.ask_filename();
	if(test_grid.load_from_file(filename)) {
		test_grid.display_grid();
	}
	else {
		std::cerr << "Виникла помилка при відкритті grid.txt\n";
		return 1;
	}

	std::vector<Pair> pairs = test_grid.extract_pairs();
	
	std::vector<Pair>::iterator it;
	for (it = pairs.begin(); it != pairs.end(); it++) {
		std::cout << ((*it).get_start())->get_char() << ": " << (*it).get_start() << " - " << (*it).get_end() << "\n";
	}
	
	Solver solver(&test_grid);

	if (solver.solve()) {
		std::cout << "Рішення знайдено:\n";
		test_grid.display_grid();
	} else {
		test_grid.display_grid();
		std::cout << "Рішення не знайдено\n";
	}

	return 0;
}

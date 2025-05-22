/* grid.cc - сітка з клітинок (реалізація) */
#include <iostream>

#include <string>
#include <fstream>

#include <map>

#include <cstdlib>
#include <ctime>

#include "grid.h"
#include "direction.h"
#include "pair.h"

Grid::Grid(int n_size) : n(n_size) {
	initialize_grid();
	connect_all_cells();
}

void Grid::initialize_grid() {

	cells.resize(n);

	for(int y = 0; y < n; y++) {
		cells[y].resize(n);
		for(int x = 0; x < n; x++) {
			cells[y][x] = new Cell('.');
		}
	}
}

void Grid::display_grid() {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			std::cout << cells[y][x]->get_char() << ' ';
		}	
		std::cout << '\n';
	}
}

void Grid::connect_all_cells() {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {

			if (y > 0 && cells[y][x] && cells[y - 1][x]) {
				cells[y][x]->connect_to(*cells[y - 1][x], NORTH);
			}

			if (x > 0 && cells[y][x] && cells[y][x-1]) {
				cells[y][x]->connect_to(*cells[y][x - 1], WEST);
			}

		}
	}
}

bool Grid::load_from_file(std::string &filename) {

	for(int y = 0; y < n; y++) {
		for(int x = 0; x < n; x++) {
			delete cells[y][x];
		}
	}
	cells.clear();

	std::ifstream fin(filename.c_str());
	if (!fin) return false;

	char ch;
	std::vector<Cell*> current_row;

	while(fin.get(ch)) {
		if (ch == '\n') {
			cells.push_back(current_row);
			current_row.clear();
		} else {
			current_row.push_back(new Cell(ch));
		}
	}

	if(!current_row.empty()) cells.push_back(current_row);

  n = cells.size();

	connect_all_cells();

	return true;

}

void Grid::reset_all_visited() {
	for(int y = 0; y < n; y++) {
		for(int x = 0; x < n; x++) {
			cells[y][x]->set_visited(false);
		}
	}
}

std::vector<Pair> Grid::extract_pairs() {
	std::vector<Pair> result;
	std::map<char, std::vector<Cell*> > m;

	for (int y = 0; y < n; y++)
		for (int x = 0; x < n; x++) {
			Cell *cell = cells[y][x];
			char ch = cell->get_char();
			if (ch != '.' && std::isalnum(ch)) m[ch].push_back(cell);
		}

	std::map<char, std::vector<Cell*> >::iterator it;
	for (it = m.begin(); it != m.end(); it++) {
		if (it->second.size() == 2) result.push_back(Pair(it->second[0], it->second[1]));
	}

	return result;
}

std::pair<int, int> Grid::get_coords_of(Cell *cell) {
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			if (cells[y][x] == cell) {
				return std::make_pair(x, y);
			}
		}
	}
	return std::make_pair(-1, -1);
}

void Grid::random_fill(int num_pairs) {

	std::srand(std::time(0));

	char ch = 'A';
	for (int i = 0; i < num_pairs; ++i) {
		if (ch > 'Z') break;

		int x1, y1, x2, y2;

		/* перша клітинка */
		do {
			x1 = std::rand() % n;
			y1 = std::rand() % n;
		} while (cells[y1][x1]->get_char() != '.');

		cells[y1][x1]->set_char(ch);

		/* друга клітинка */
		do {
			x2 = std::rand() % n;
			y2 = std::rand() % n;
		} while ((x1 == x2 && y1 == y2) || cells[y2][x2]->get_char() != '.');

		cells[y2][x2]->set_char(ch);

		ch++;
	}

}

Grid::~Grid() {
	for(int y = 0; y < n; y++) {
		for(int x = 0; x < n; x++) {
			delete cells[y][x];
		}
	}
}

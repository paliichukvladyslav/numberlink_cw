/* pair.cc - пара клітинок (реалізація) */
#include <vector>
#include <iostream>

#include "pair.h"

Pair::Pair(Cell *start_cell, Cell *end_cell)
	: start(start_cell),
		end(end_cell)
{}

void Pair::set_start(Cell *start_cell) {
	start = start_cell;
}

void Pair::set_end(Cell *end_cell) {
	end = end_cell;
}

Cell* Pair::get_start() {
	return start;
}

Cell* Pair::get_end() {
	return end;
}

std::vector<Cell*> &Pair::get_path() {
	return path;
}

void Pair::clear_path() {

	std::vector<Cell*>::iterator it;
	for (it = path.begin(); it != path.end(); it++) {
		if (*it != start && *it != end) {
			(*it)->set_char('.');
		}
		(*it)->set_visited(false);
	}

	path.clear();
}

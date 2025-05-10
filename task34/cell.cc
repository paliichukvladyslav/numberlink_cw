/* cell.cc - клітинка (реалізація) */
#include <iostream>
#include <cctype>
#include "cell.h"
#include "direction.h"

Cell::Cell(char char_to_set)
	: ch(char_to_set),
		visited (false),
		north   (NULL),
		south   (NULL),
		west    (NULL),
		east    (NULL)
{}

char Cell::get_char() {
	return ch;
}

void Cell::set_char(char char_to_set) {

	if (!std::isalnum(char_to_set) && char_to_set != '.') {
		std::cerr << "На вхід було подано некоректний символ, вик-но крапку як fallback";
		ch = '.';
		return;
	}

	ch = char_to_set; 
}

bool Cell::is_visited() {
	return visited;
}

void Cell::set_visited(bool v) {
	visited = v;
}

void Cell::connect_to(Cell &targetCell, Direction dir) {

	switch(dir) {
		case NORTH:
			north = &targetCell;
			targetCell.south = this;
			break;
		case SOUTH:
			south = &targetCell;
			targetCell.north = this;
			break;
		case WEST:
			west = &targetCell;
			targetCell.east = this;
			break;
		case EAST:
			east = &targetCell;
			targetCell.west = this;
			break;
	}

	return;

}


Cell* Cell::cell_in_direction(Direction dir) {

	switch(dir) {
		case NORTH:
			return north;
		case SOUTH:
			return south;
		case WEST:
			return west;
		case EAST:
			return east;
	}

	return NULL;
}

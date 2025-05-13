/* pair.h - пара клітинок */
#ifndef PAIR_H
#define PAIR_H

#include <vector>

#include "cell.h"

/*
 * Pair представляє пару з двох клітинок (див. клас Cell).
 */
class Pair {
private:

	/* 2 клітинки */
	Cell *start, *end;

	/* знайдений шлях між двома клітинками */
	std::vector<Cell*> path;

public:

	Pair(Cell *start_cell, Cell *end_cell);

	void set_start(Cell *start_cell);
	void set_end(Cell *end_cell);

	Cell *get_start();
	Cell *get_end();

	std::vector<Cell*> &get_path();
	void clear_path();

};

#endif

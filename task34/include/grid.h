/* grid.h - сітка з клітинок */
#ifndef GRID_H
#define GRID_H 

#include <vector>

#include "cell.h"
#include "util.h"

/*
 * Grid представляє сітку з клітинок (клас Cell, див. cell.h).
 */
class Grid {
private:
	
	/* int n - розмір сітки n*n */
	int n;

	/* 2D вектор, що зберігає інф. про клітинки */
	std::vector< std::vector<Cell*> > cells;

	void connect_all_cells();
public:

	Grid(int n_size = DEFAULT_GRID_SIZE);
	~Grid();

	void initialize_grid();

	void reset_all_visited();

	void display_grid();

};

#endif

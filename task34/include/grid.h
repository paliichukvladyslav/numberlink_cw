/* grid.h - сітка з клітинок */
#ifndef GRID_H
#define GRID_H 

#include <vector>
#include <string>

#include "cell.h"
#include "pair.h"
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
	bool load_from_file(std::string &filename);

	void reset_all_visited();

	std::vector<Pair> extract_pairs();

	void display_grid();

};

#endif

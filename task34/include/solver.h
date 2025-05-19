/* solver.h - вирішувач задачі */
#ifndef SOLVER_H
#define SOLVER_H

#include <vector>

#include "cell.h"
#include "grid.h"
#include "pair.h"

/*
 * Solver - вирішувач задачі
 */
class Solver {
private:

	Grid *grid;
	std::vector<Pair> pairs;
	
	/* Depth First Search */
	bool dfs(Cell *cur, Cell *end, Pair &pair);

	bool solve_recursive(int i);

public:
	
	Solver(Grid *grid_to_solve);
	
	bool solve();

	void reset_all_paths();
	
};

/*
 * Компаратори для порівняння за Менгеттенською відстанню
 */
struct CellDistanceComparator {
	Grid *grid;
	Cell *end;

	CellDistanceComparator(Grid *compgrid, Cell *end_cell);

	bool operator()(Cell *a, Cell *b);
};

struct PairDistanceComparator {
	Grid *grid;

	PairDistanceComparator(Grid *compgrid);

	bool operator()(Pair &a, Pair &b);
};

#endif

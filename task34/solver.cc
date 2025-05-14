/* solver.cc - вирішувач (реалізація) */
#include <vector>
#include <iostream>
#include <algorithm>

#include "solver.h"
#include "direction.h"

Solver::Solver(Grid *grid_to_solve)
	: grid(grid_to_solve),
		pairs(grid_to_solve->extract_pairs())
{}

bool Solver::solve() {
	return solve_recursive(0);
}

bool Solver::solve_recursive(int i) {
	if (i >= (int)pairs.size() ) return true;

	Pair &cur_pair = pairs[i];
	grid->reset_all_visited();

	if (dfs(cur_pair.get_start(), cur_pair.get_end(), cur_pair)) {
		if (solve_recursive(i + 1)) {
			return true;
		}
		cur_pair.clear_path();
		return false;
	} else {
		cur_pair.clear_path();
		return false;
	}
}

bool Solver::dfs(Cell *cur, Cell *end, Pair &pair) {
	if (cur == NULL) return false;
	if (cur->is_visited() == true) return false;

	if (cur->get_char() != '.' && cur != pair.get_start() && cur != pair.get_end()) return false;

	pair.get_path().push_back(cur);
	cur->set_visited(true);

	if (cur != pair.get_start() && cur != pair.get_end()) {
		std::cout << "Marking: " << cur << " as " << pair.get_start()->get_char() << '\n';
		cur->set_char(pair.get_start()->get_char());
	}

	std::cout << "DFS at: " << cur << " char=" << cur->get_char() << '\n';

	/* шлях знайдено */
	if (cur == end) return true;

	if (dfs(cur->cell_in_direction(NORTH), end, pair)) return true;
	if (dfs(cur->cell_in_direction(SOUTH), end, pair)) return true;
	if (dfs(cur->cell_in_direction(WEST), end, pair)) return true;
	if (dfs(cur->cell_in_direction(EAST), end, pair)) return true;

	if (cur != pair.get_start() && cur != pair.get_end()) cur->set_char('.');

	cur->set_visited(false);
	pair.get_path().pop_back();

	return false;
}

void Solver::reset_all_paths() {
	for (size_t i = 0; i < pairs.size(); i++) {
		pairs[i].clear_path();
	}
}



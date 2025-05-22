/* solver.cc - вирішувач (реалізація) */
#include <vector>
#include <iostream>
#include <algorithm>

#include "solver.h"
#include "direction.h"

Solver::Solver(Grid *grid_to_solve)
	: grid(grid_to_solve),
	pairs(grid_to_solve->extract_pairs())
{
	/* 
	 * сортуємо пари за мангеттенською відстанню між їхніми клітинками
	 * щоб вирішення задачі починалося з тих пар, відстань між якими найменша
	 */
	std::sort(pairs.begin(), pairs.end(), PairDistanceComparator(grid_to_solve));
}

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
	if (cur->is_visited()) return false;

	if (cur->get_char() != '.' && cur != pair.get_start() && cur != pair.get_end()) return false;

	pair.get_path().push_back(cur);
	cur->set_visited(true);

	bool marked = false;
	if (cur != pair.get_start() && cur != pair.get_end()) {
		cur->set_char(pair.get_start()->get_char());
		marked = true;
	}

	/* шлях знайдено */
	if (cur == end) return true;

	std::vector<Cell*> neighbors;
	neighbors.push_back(cur->cell_in_direction(NORTH));
	neighbors.push_back(cur->cell_in_direction(SOUTH));
	neighbors.push_back(cur->cell_in_direction(WEST));
	neighbors.push_back(cur->cell_in_direction(EAST));

	/* сортуємо сусідні клітинки за мангеттенською відстанню до кінця */
	std::sort(neighbors.begin(), neighbors.end(), CellDistanceComparator(grid, end));

	bool found = false;
	for (std::vector<Cell*>::iterator it = neighbors.begin(); it != neighbors.end(); it++) {
		if (dfs(*it, end, pair)) {
			found = true;
			break;
		}
	}

	/* backtracking */
	if (!found) {
		if (marked) {
			cur->set_char('.');
		}
		cur->set_visited(false);
		pair.get_path().pop_back();
	}

	return found;
}

CellDistanceComparator::CellDistanceComparator(Grid *compgrid, Cell *end_cell) 
	: grid(compgrid),
	end(end_cell)
{}

PairDistanceComparator::PairDistanceComparator(Grid *compgrid) : grid(compgrid) {}

bool CellDistanceComparator::operator()(Cell *a, Cell *b) {
	std::pair<int, int> a_coords = grid->get_coords_of(a);
	std::pair<int, int> b_coords = grid->get_coords_of(b);

	std::pair<int, int> end_coords = grid->get_coords_of(end);

	int dist_a = std::abs(a_coords.first - end_coords.first) + std::abs(a_coords.second - end_coords.second);
	int dist_b = std::abs(b_coords.first - end_coords.first) + std::abs(b_coords.second - end_coords.second);

	return dist_a < dist_b;
}

bool PairDistanceComparator::operator()(Pair &a, Pair &b) {
	std::pair<int, int> a_start = grid->get_coords_of(a.get_start());
	std::pair<int, int> a_end = grid->get_coords_of(a.get_end());

	std::pair<int, int> b_start = grid->get_coords_of(b.get_start());
	std::pair<int, int> b_end = grid->get_coords_of(b.get_end());

	int dist_a = std::abs(a_start.first - a_end.first) + std::abs(a_start.second - a_end.second);
	int dist_b = std::abs(b_start.first - b_end.first) + std::abs(b_start.second - b_end.second);

	return dist_a < dist_b;
}

void Solver::reset_all_paths() {
	for (size_t i = 0; i < pairs.size(); i++) {
		pairs[i].clear_path();
	}
}


